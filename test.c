#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define HELLO_SYS_CALL 451

int main()
{
    long sys_call_status;

    sys_call_status = syscall(HELLO_SYS_CALL);

    if (!sys_call_status)
    {
        printf("Successfully invoked system call 451\n");
    }

    return 0;
}