/*    Program Number: 26d  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program executes the `ls -Rl` command using the execv system call.  
*/  

#include <stdio.h>
#include <unistd.h>

int main(){
    char* arr[] = {"ls", "-Rl", NULL};  // Correct argument order and first entry

    printf("execv:\n");
    execv("/bin/ls", arr);

    perror("execv failed");  // This prints only if execv fails
    return 1;
}

