/*    Program Number: 26b  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program executes the `ls -Rl` command using the execlp system call.  
*/  

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("execlp:\n");
    execlp("ls", "ls", "-Rl", NULL);  // First argument must be the command itself

    perror("execlp failed");  // This executes only if execlp fails
    return 1;
}

