/*    Program Number: 23  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a child process that continues running even after  
             the parent process exits, making the child process an orphan. The child  
             is then adopted by the init process (PID 1).  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {  // Fork failed
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        sleep(5);  // Ensure parent exits first
        printf("Orphan process detected!\n");
        printf("Child PID: %d, New Parent PID (should be init/systemd): %d\n", getpid(), getppid());
        exit(0);
    } 
    else {  // Parent process
        printf("Parent process (PID: %d) terminating now.\n", getpid());
        exit(0);
    }
}

