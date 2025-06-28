/*    Program Number: 36(d) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a FIFO file using the mknod system call.
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* path = "./fifod";

    // Create FIFO using mknod system call
    if (mknod(path, S_IFIFO | 0744, 0) == -1) {
        perror("mknod failed");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created successfully: %s\n", path);
    return 0;
}

