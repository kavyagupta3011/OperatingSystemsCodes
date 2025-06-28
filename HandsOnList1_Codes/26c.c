/*    Program Number: 26c  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program executes the `ls -Rl` command using the execle system call.  
*/  

#include <stdio.h>
#include <unistd.h>

int main() {
    extern char **environ;  // Environment variables

    printf("execle:\n");
    execle("/bin/ls", "ls", "-Rl", NULL, environ);

    perror("execle failed");  // This will only print if execle fails
    return 1;
}

