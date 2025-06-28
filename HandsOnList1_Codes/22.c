/*    Program Number: 22  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a child process using fork(). The child process  
             exits immediately, while the parent process continues running, creating  
             a zombie state for the child until the parent terminates or waits.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int process_id = fork();

    if (process_id == 0) {  // Child process
        printf("Child process entering zombie state.\n");
        exit(0);  // Child exits, becoming a zombie until the parent reaps it
    } 
    else {  // Parent process
        sleep(20);  // Give enough time to observe the zombie state
        printf("Parent process running.\n");
    }
}
