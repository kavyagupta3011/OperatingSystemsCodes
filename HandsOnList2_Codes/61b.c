/*    Program Number: 61(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGINT signal using the sigaction system call.
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(int s)
{
    if (s == SIGINT)
    {
        printf("CAPTURED SIGINT\n");
        exit(0);
    }
}

int main()
{
    struct sigaction new_action;
    new_action.sa_handler = &handler;
    sigemptyset(&new_action.sa_mask);  // Clear signal mask
    new_action.sa_flags = 0;  // No special flags

    if (sigaction(SIGINT, &new_action, NULL) != 0)
    {
        perror("Error");
        return 1;
    }

    while(1);  // Infinite loop to keep the program running, waiting for SIGINT
    return 0;
}

