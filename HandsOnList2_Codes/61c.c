/*    Program Number: 61(c) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGFPE signal using the sigaction system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(int s)
{
    if (s == SIGFPE)
    {
        printf("CAPTURED SIGFPE\n");
        exit(0);
    }
}

int main(void)
{
    struct sigaction new_action;
    new_action.sa_handler = &handler;
    sigemptyset(&new_action.sa_mask);  // Clear signal mask
    new_action.sa_flags = 0;  // No special flags

    if (sigaction(SIGFPE, &new_action, NULL) != 0)
    {
        perror("Floating Point Error");
        return 1;
    }

    float f = 1 / 0;  // This will cause a floating-point exception (division by zero)
    return 0;
}

