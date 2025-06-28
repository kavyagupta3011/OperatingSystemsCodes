/*    Program Number: 19  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program demonstrates different process states by initiating  
             a process in running, sleeping, and stopped states. The state of  
             the process can be verified using relevant system commands.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) { // Child process
        printf("Child Running...\n");
        
        // Track real-time instead of CPU time
        time_t start = time(NULL);
        int cycles = 0;
        
        while (time(NULL) - start < 10) { // Run for 10 seconds
            cycles++;
        }
        
        printf("CPU Cycles Count: %d\n", cycles);
        
        printf("Child Sleeping...\n");
        sleep(10);

        printf("Child Stopping...\n");
        raise(SIGSTOP);  // Stop execution

        // After parent sends SIGCONT
        printf("Child Resumed, now terminating...\n");
        exit(0);  // Ensure proper termination
    } 
    else { // Parent process
        waitpid(pid, NULL, WUNTRACED);  // Wait until the child stops
        printf("Parent detected that child has stopped.\n");

        sleep(10);  // Wait before resuming the child
        printf("Resuming child process...\n");
        kill(pid, SIGCONT);  // Resume child process

        wait(NULL);  // Wait for the child to terminate
        printf("Child process has exited.\n");
    }

    return 0;
}
