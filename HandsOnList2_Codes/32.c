/*    Program Number: 32 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will send data from the parent process to the child process using inter-process communication mechanisms. 
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);

    int id = fork();
    if (id == 0) {  // Child
        close(fd[1]);  // Close write end
        char buff[100] = {0};
        read(fd[0], buff, 100);
        printf("Child received: %s", buff);
        close(fd[0]);
    } else {  // Parent
        close(fd[0]);  // Close read end
        char msg[] = "TestTest\n";
        write(fd[1], msg, strlen(msg));  // Write 9 bytes
        close(fd[1]);
    }

    return 0;
}

