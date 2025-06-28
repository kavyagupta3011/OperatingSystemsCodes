/*    Program Number: 36(e) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a FIFO file using the mkfifo library function.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* path = "./fifoe";

    // Create FIFO using mkfifo library function
    if (mkfifo(path, 0744) == -1) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created successfully: %s\n", path);
    return 0;
}

