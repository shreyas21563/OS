#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<sched.h>
int main(){
    pid_t pid1, pid2, pid3;
    struct timespec t1, t2, t3, t4, t5, t6;
    pid1 = fork();
    clock_gettime(CLOCK_REALTIME, &t1);
    if(pid1==0){
        pid2 = fork();
        clock_gettime(CLOCK_REALTIME, &t3);
        if(pid2==0){
            pid3 = fork();
            clock_gettime(CLOCK_REALTIME, &t5);
            if(pid3==0){
                execl("/bin/sh", "sh", "bash.sh", NULL);
            }else{
                waitpid(pid3, NULL, NULL);
                clock_gettime(CLOCK_REALTIME, &t6);
                
            }
            execl("/bin/sh", "sh", "bash.sh", NULL);
        }else{
            waitpid(pid2, NULL, NULL);
            clock_gettime(CLOCK_REALTIME, &t4);
        }
        execl("/bin/sh", "sh", "bash.sh", NULL);
    }else{
        waitpid(pid1, NULL, NULL);
        clock_gettime(CLOCK_REALTIME, &t2);
        printf("TIME3: %f\n", ((t6.tv_sec-t5.tv_sec)+((double)(t6.tv_nsec-t5.tv_nsec))/(double)1000000000L));
        printf("TIME2: %f\n", ((t4.tv_sec-t3.tv_sec)+((double)(t4.tv_nsec-t3.tv_nsec))/(double)1000000000L));
        printf("TIME1: %f\n", ((t2.tv_sec-t1.tv_sec)+((double)(t2.tv_nsec-t1.tv_nsec))/(double)1000000000L));
    }
}
