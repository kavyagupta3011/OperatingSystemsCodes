/*    Program Number: 59(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGINT signal using the signal system call.
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
    if (signal(SIGINT, &handler) == SIG_ERR)
    {
        perror("Error");
        return 1;
    }
    while(1);  // Infinite loop waiting for SIGINT (Ctrl + C)
    return 0;
}

