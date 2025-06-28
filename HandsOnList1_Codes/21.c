/*    Program Number: 21  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program opens a file, creates a child process using fork(),  
             and allows both the parent and child processes to write to the file.  
             The output is examined to observe how both processes write to the file.  
*/  

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    int file = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
    
    if (file < 0) {
        perror("Error opening file");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(file);
        return 1;
    }

    if (pid == 0) { // Child Process
        write(file, "Child process writing\n", 22);
    } else { // Parent Process
        // Using wait(NULL) here would ensure ordered execution, preventing mixed output.
        write(file, "Parent process writing\n", 24);
    }

    fsync(file);  
    close(file);  

    return 0;
}
