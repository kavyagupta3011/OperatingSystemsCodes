/*    Program Number: 26a  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program executes the `ls -Rl` command using the execl system call.  
*/  

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("execl:\n");
    execl("/bin/ls", "ls", "-Rl", NULL); // First argument should be "ls"
    
    perror("execl failed"); // This will only execute if execl fails
    return 1;
}

