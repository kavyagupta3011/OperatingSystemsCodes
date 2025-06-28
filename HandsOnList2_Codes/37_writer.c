/*    Program Number: 37_writer
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will enable communication through FIFO using one-way communication (writer).
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>  // Add this header to include mkfifo()

#define FIFO_PATH "myfifo37"

int main() {
    int fd;
    char buf[100] = {0};

    // Create the FIFO if it doesn't exist
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(1);
    }

    // Get user input to send
    printf("Enter message to be sent: ");
    fgets(buf, sizeof(buf), stdin);

    // Remove the trailing newline from fgets
    buf[strlen(buf) - 1] = '\0';

    // Write the message to the FIFO
    write(fd, buf, strlen(buf));

    // Close the FIFO after writing
    close(fd);

    return 0;
}

