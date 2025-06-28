/*    Program Number: 34(c) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will execute ls -l | wc using fcntl.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    int pid = fork();

    if (pid == 0) {
        // Child: executes "ls -l"
        close(fd[0]);                 // Close read end
        close(1);                     // Close stdout
        fcntl(fd[1], F_DUPFD, 1);     // Duplicate fd[1] to stdout (if available)
        close(fd[1]);                 // Close original write end
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    } else {
        // Parent: executes "wc"
        close(fd[1]);                 // Close write end
        close(0);                     // Close stdin
        fcntl(fd[0], F_DUPFD, 0);     // Duplicate fd[0] to stdin
        close(fd[0]);                 // Close original read end
        wait(NULL);                   // Wait for child
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }

    return 0;
}
// ls -l | wc should give the same thing at that moment
