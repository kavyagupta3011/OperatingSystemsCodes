/*    Program Number: 1c  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a FIFO using the mkfifo library function
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char f1c_fifoName[100];

    printf("Enter the FIFO file name:\n");
    scanf("%s", f1c_fifoName);

    int result = mkfifo(f1c_fifoName, 0777);  // Creates a named pipe (FIFO), returns 0 on success, -1 on failure

    if (result == 0) {
        printf("FIFO successfully created.\n");
    } else {
        printf("Error: Could not create FIFO.\n");
    }

    return 0;
}
