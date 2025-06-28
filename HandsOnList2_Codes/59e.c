/*    Program Number: 59(e) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGALRM signal using the setitimer system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>

void handler(int s)
{
    if (s == SIGALRM)
    {
        printf("CAPTURED SIGALRM\n");
        exit(0);
    }
}

int main()
{
    if (signal(SIGALRM, &handler) == SIG_ERR)
    {
        perror("No Alarm");
        return 1;
    }
    struct itimerval t;
    t.it_interval.tv_sec = 2;  // Interval between subsequent signals
    t.it_interval.tv_usec = 0;
    t.it_value.tv_sec = 6;  // Initial delay before the first signal
    t.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &t, NULL);  // Set real-time timer
    while(1);  // Infinite loop waiting for SIGALRM
    return 0;
}

