/*    Program Number: 64(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will await the SIGSTOP signal and attempt to catch it.
*/

// 64_1.c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID of this process: %d\n", getpid());
    printf("Send SIGSTOP using: kill -SIGSTOP %d\n", getpid());
    printf("Then send SIGCONT to resume it.\n\n");

    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}

