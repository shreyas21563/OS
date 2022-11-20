#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <pthread.h>
#include <ctype.h>
#include<sys/resource.h>
struct timespec t1, t2, t3, t4;
int priority_rr[] = {1, 2, 3, 4, 5};
int priority_fifo[] = {9, 10, 11, 12, 13};
int other[] = {-20, 10, 0, 10, 19};
int count = 0;
struct sched_param parameter_fifo, parameter_rr, parameter_other;
void countA(){
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
}

void* countB(){
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
}

void* countC(){
    for(long long int i = 1; i<=4294967296; i++){
        continue;
    }
}
void *ThrA(){
    struct timespec t1, t2;
    pthread_t pid = pthread_self();
    setpriority(PRIO_PROCESS, 0, other[count]);
    pthread_setschedparam(pid ,SCHED_OTHER, &parameter_other);
    clock_gettime(CLOCK_REALTIME, &t1);
    countA();
    clock_gettime(CLOCK_REALTIME, &t2);
    printf("SCHED_OTHER SCHEDULING POLICY >>>>");
    printf("Time Taken: %lf\n",(double)((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec-t1.tv_nsec))/(double)1000000000L));
}
void *ThrB(){
	struct timespec t3, t4;
	pthread_t pid = pthread_self();
	pthread_setschedparam(pid, SCHED_RR, &parameter_rr);
	clock_gettime(CLOCK_REALTIME, &t3);
	countB();
	clock_gettime(CLOCK_REALTIME, &t4);
	printf("SCHED_RR SCHEDULING POLICY >>>>");
	printf("Time Taken %lf\n", (double)((t4.tv_sec-t3.tv_sec)+((double)(t4.tv_nsec-t3.tv_nsec))/(double)1000000000L));
}
void *ThrC(){
	struct timespec t5, t6;
	pthread_t pid = pthread_self();
	pthread_setschedparam(pid, SCHED_FIFO, &parameter_fifo);
	clock_gettime(CLOCK_REALTIME, &t5);
	countC();
	clock_gettime(CLOCK_REALTIME, &t6);
	printf("SCHED_FIFO SCHEDULING POLICY >>>>");
	printf("Time Taken %lf\n", (double)((t6.tv_sec-t5.tv_sec)+((double)(t6.tv_nsec-t5.tv_nsec))/(double)1000000000L));

}
int main(){
    for(int i = 0; i<5; i++){
   	 pthread_t Thr_A;
 	 pthread_t Thr_B;
    	 pthread_t Thr_C;
         struct sched_param parameter_rr, parameter_fifo;
	 parameter_rr.sched_priority = priority_rr[count];
	 parameter_fifo.sched_priority = priority_fifo[count];
         pthread_create(&Thr_A,NULL,ThrA,NULL);
         pthread_create(&Thr_B,NULL,ThrB,NULL);
         pthread_create(&Thr_C,NULL,ThrC,NULL);
         pthread_join(Thr_A,NULL);
         pthread_join(Thr_B,NULL);
         pthread_join(Thr_C,NULL);
	 printf("\n\n");    
	 count++;
    } 
    return 0;
}
