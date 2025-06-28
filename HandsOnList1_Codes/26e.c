/*    Program Number: 26e 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program executes the `ls -Rl` command using the execvp system call.  
*/  

#include <stdio.h>
#include <unistd.h>

int main(){
    char* arr[] = {"ls", "-Rl", NULL};  // First argument should be "ls"

    printf("execvp:\n");
    execvp(arr[0], arr);  // No need to use "/bin/ls", just "ls"

    perror("execvp failed");  // This prints only if execvp fails
    return 1;
}

