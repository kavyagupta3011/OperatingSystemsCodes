/*    Program Number: 31 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a pipe, write to the pipe, read from the pipe, and display the content on the monitor*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    write(fd[1], "TestTest\n", 9); // write 9 bytes
    char ans[9] = {0};             // initialize buffer
    read(fd[0], ans, 9);           // read 9 bytes

    write(1, ans, 9);              // write 9 bytes to stdout
    return 0;
}

