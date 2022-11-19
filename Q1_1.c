#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>
#include<sys/resource.h>
struct timespec t1, t2, t3, t4, t5, t6;
void countA(){
    clock_gettime(CLOCK_REALTIME, &t1);
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
    clock_gettime(CLOCK_REALTIME, &t2);
}

void* countB(){
    clock_gettime(CLOCK_REALTIME, &t3);
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
    clock_gettime(CLOCK_REALTIME, &t4);
}

void* countC(){
    clock_gettime(CLOCK_REALTIME, &t5);
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
    clock_gettime(CLOCK_REALTIME, &t6);
}
void *ThrA(){
    struct timespec t1, t2;
    struct sched_param parameter_other;
    pthread_t id = pthread_self();
    setpriority(PRIO_PROCESS, 0, 19);
    parameter_other.sched_priority=0; 
    if(pthread_setschedparam(id ,SCHED_OTHER, &parameter_other)!=0){
        printf("Error A\n");
    }
    countA();
}

int main(){
    pthread_t Thr_A;
    pthread_t Thr_B;
    pthread_t Thr_C;
    struct sched_param parameter_rr, parameter_fifo;
    pthread_create(&Thr_A,NULL,ThrA,NULL);
    pthread_create(&Thr_B,NULL,countB,NULL);
    pthread_create(&Thr_C,NULL,countC,NULL);
    parameter_rr.sched_priority=1;
    parameter_fifo.sched_priority=2;
    pthread_setschedparam(Thr_B ,SCHED_RR, &parameter_rr);
    pthread_setschedparam(Thr_C ,SCHED_FIFO, &parameter_fifo)
    pthread_join(Thr_A,NULL);
    pthread_join(Thr_B,NULL);
    pthread_join(Thr_C,NULL);
    printf("SCHED_OTHER SCHEDULING POLICY >>>>");
    printf("Time Taken: %f\n",(double)((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec-t1.tv_nsec))/(double)1000000000L));
    printf("SCHED_FIFO SCHEDULING POLICY >>>>");
    printf("Time Taken: %f\n",(double)((t6.tv_sec-t5.tv_sec)+((double)(t6.tv_nsec-t5.tv_nsec))/(double)1000000000L));
    printf("SCHED_RR SCHEDULING POLICY >>>>");
    printf("Time Taken: %f\n",(double)((t4.tv_sec-t3.tv_sec)+((double)(t4.tv_nsec-t3.tv_nsec))/(double)1000000000L));
    return 0;
}
