/*    Program Number: 20  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a child process using fork() and prints both  
             the parent and child process IDs.  
*/  

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t process_id = fork();  // Create child process

    if (process_id < 0) {
        perror("Fork failed");  // Handle error
        return 1;
    }
    
    if (process_id == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), process_id);
    }

    return 0;
}

