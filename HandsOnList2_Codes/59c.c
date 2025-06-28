/*    Program Number: 59(c) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGFPE signal using the signal system call.
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

int main()
{
    if (signal(SIGFPE, &handler) == SIG_ERR)
    {
        perror("Floating Point Error");
        return 1;
    }
    float f = 1 / 0;  // This will cause a floating point exception (divide by zero)
    return 0;
}

