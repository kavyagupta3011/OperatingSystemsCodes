/*    Program Number: 33 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will send and receive data between the parent and child processes using two-way communication. 
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd1[2]; // Parent to child
    int fd2[2]; // Child to parent

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    int id = fork();
    if (id < 0) {
        perror("fork");
        exit(1);
    }

    if (id == 0) {
        // Child Process
        close(fd1[1]); // Close write end of fd1
        close(fd2[0]); // Close read end of fd2

        char readbuff[100] = {0};
        read(fd1[0], readbuff, sizeof(readbuff));
        printf("Child received: %s", readbuff);

        char reply[] = "Hello parent\n";
        write(fd2[1], reply, strlen(reply));

        close(fd1[0]);
        close(fd2[1]);
    } else {
        // Parent Process
        close(fd1[0]); // Close read end of fd1
        close(fd2[1]); // Close write end of fd2

        char msg[] = "Hello Child\n";
        write(fd1[1], msg, strlen(msg));

        wait(NULL); // Wait for child

        char rbuff[100] = {0};
        read(fd2[0], rbuff, sizeof(rbuff));
        printf("Parent received: %s", rbuff);

        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}

