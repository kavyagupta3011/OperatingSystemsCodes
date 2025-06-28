/*    Program Number: 34(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will execute ls -l | wc using dup.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // Child: runs "ls -l"
        close(fd[0]);           // Close read end
        close(1);               // Close stdout
        dup(fd[1]);             // Duplicate write end to stdout
        close(fd[1]);           // Close original write end
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    } else {
        // Parent: runs "wc"
        close(fd[1]);           // Close write end
        wait(NULL);             // Wait for child to complete (optional but safe)
        close(0);               // Close stdin
        dup(fd[0]);             // Duplicate read end to stdin
        close(fd[0]);           // Close original read end
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }

    return 0;
}
// ls -l | wc should print the same thing at that moment

