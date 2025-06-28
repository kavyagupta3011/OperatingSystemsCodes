/*    Program Number: 61(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGSEGV signal using the sigaction system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(int s)
{
    if (s == SIGSEGV)
    {
        printf("CAPTURED SIGSEGV\n");
        exit(0);
    }
}

int main()
{
    struct sigaction new_action;
    new_action.sa_handler = &handler;
    sigemptyset(&new_action.sa_mask);  // Clear signal mask
    new_action.sa_flags = 0;  // No special flags

    if (sigaction(SIGSEGV, &new_action, NULL) != 0)
    {
        perror("Invalid Memory");
        return 1;
    }

    int* p = NULL;
    printf("%d\n", *p);  // This will cause a segmentation fault
    return 0;
}

