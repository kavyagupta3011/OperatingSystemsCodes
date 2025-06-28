/*    Program Number: 59(f) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGVTALRM signal using the setitimer system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>

void handler(int s)
{
    if (s == SIGVTALRM)
    {
        printf("CAPTURED SIGVTALRM\n");
        exit(0);
    }
}

int main()
{
    if (signal(SIGVTALRM, &handler) == SIG_ERR)
    {
        perror("No Virtual Alarm");
        return 1;
    }
    struct itimerval t;
    t.it_interval.tv_sec = 2;
    t.it_interval.tv_usec = 0;
    t.it_value.tv_sec = 6;
    t.it_value.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &t, NULL);  // Set virtual timer
    while(1);  // Infinite loop waiting for SIGVTALRM
    return 0;
}

