/*    Program Number: 24  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates three child processes. The parent process waits  
             for a specific child process to terminate using the waitpid system call.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int p1 = fork();

    if (p1 == 0) {  // First child
        sleep(10);
        printf("Child 1: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    } 
    else {
        int p2 = fork();
        if (p2 == 0) {  // Second child
            sleep(10);
            printf("Child 2: PID = %d, PPID = %d\n", getpid(), getppid());
            exit(0);
        } 
        else {
            int p3 = fork();
            if (p3 == 0) {  // Third child
                sleep(10);
                printf("Child 3: PID = %d, PPID = %d\n", getpid(), getppid());
                exit(0);
            } 
            else {  // Parent process
                printf("Parent waiting for PID: %d\n", p2);
                int waited_pid = waitpid(p2, NULL, 0);  // Wait only for p2
                printf("Parent finished waiting for: %d\n", waited_pid);
            }
        }
    }
    return 0;
}
