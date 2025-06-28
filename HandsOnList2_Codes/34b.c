/*    Program Number: 34(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will execute ls -l | wc using dup2.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // Child: runs ls -l
        close(fd[0]);               // Close unused read end
        dup2(fd[1], 1);             // Redirect stdout to write end of pipe
        close(fd[1]);               // Close original write end
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    } else {
        // Parent: runs wc
        close(fd[1]);               // Close unused write end
        dup2(fd[0], 0);             // Redirect stdin to read end of pipe
        close(fd[0]);               // Close original read end
        wait(NULL);                 // Wait for child to complete
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }

    return 0;
}
// ls -l | wc should print the same thing at that moment
