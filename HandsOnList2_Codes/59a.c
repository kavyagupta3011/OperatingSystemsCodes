/*    Program Number: 59(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will catch the SIGSEGV signal using the signal system call.
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
    if (signal(SIGSEGV, &handler) == SIG_ERR)
    {
        perror("Invalid Memory");
        return 1;
    }
    int* p = NULL;
    printf("%d\n", *p);  // This will cause a segmentation fault
    return 0;
}

