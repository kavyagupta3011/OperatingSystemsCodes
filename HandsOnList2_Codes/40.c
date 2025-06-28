/*    Program Number: 40 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will print the maximum number of files that can be opened within a process and the size of a pipe (circular buffer).
*/


#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int pd[2];

    // Create pipe
    if (pipe(pd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Get pipe size
    int pipe_size = fcntl(pd[0], F_GETPIPE_SZ);
    printf("Pipe buffer size = %d bytes\n", pipe_size);

    // Get max open file descriptors
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Max open file descriptors per process: %ld\n", limit.rlim_cur);

    close(pd[0]);
    close(pd[1]);
    return 0;
}

