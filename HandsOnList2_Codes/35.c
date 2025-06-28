/*    Program Number: 35 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will find the total number of directories in the present working directory using ls -l | grep ^d | wc, implemented using dup2 system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    // Step 1: Create some directories
    mkdir("dir1", 0755);
    mkdir("dir2", 0755);
    mkdir("dir3", 0755);

    int pipefd_ls_grep[2]; // ls -> grep
    int pipefd_grep_wc[2]; // grep -> wc

    if(pipe(pipefd_ls_grep) == -1 || pipe(pipefd_grep_wc) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t ls_pid = fork();
    if(ls_pid == 0) {
        dup2(pipefd_ls_grep[1], STDOUT_FILENO);  // ls stdout -> pipe1 write
        close(pipefd_ls_grep[0]);
        close(pipefd_ls_grep[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("exec ls failed");
        exit(EXIT_FAILURE);
    }

    pid_t grep_pid = fork();
    if(grep_pid == 0) {
        dup2(pipefd_ls_grep[0], STDIN_FILENO);   // grep stdin <- pipe1 read
        dup2(pipefd_grep_wc[1], STDOUT_FILENO);  // grep stdout -> pipe2 write
        close(pipefd_ls_grep[0]);
        close(pipefd_ls_grep[1]);
        close(pipefd_grep_wc[0]);
        close(pipefd_grep_wc[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("exec grep failed");
        exit(EXIT_FAILURE);
    }

    // Parent process runs wc -l
    close(pipefd_ls_grep[0]);
    close(pipefd_ls_grep[1]);
    close(pipefd_grep_wc[1]);

    dup2(pipefd_grep_wc[0], STDIN_FILENO);  // wc stdin <- pipe2 read
    close(pipefd_grep_wc[0]);

    execlp("wc", "wc", "-l", NULL);
    perror("exec wc failed");
    exit(EXIT_FAILURE);

    return 0;
}

