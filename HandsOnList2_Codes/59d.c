/*    Program Number: 59(d) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGALRM signal using the alarm system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

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
        printf("No Alarm");
        return 1;
    }
    alarm(3);  // Trigger SIGALRM after 3 seconds
    while(1);  // Infinite loop waiting for SIGALRM
    return 0;
}

