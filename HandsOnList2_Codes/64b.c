/*    Program Number: 64(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will send the SIGSTOP signal using the kill system call to the first program.
*/

// 64_2.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pid;
    printf("Enter PID to send SIGSTOP: ");
    scanf("%d", &pid);

    if (kill(pid, SIGSTOP) == 0) {
        printf("SIGSTOP sent to process %d\n", pid);
    } else {
        perror("Failed to send SIGSTOP");
    }

    return 0;
}

