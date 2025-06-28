/*    Program Number: 37_reader
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will enable communication through FIFO using one-way communication (reader).
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define FIFO_PATH "myfifo37"

int main() {
    int fd;
    char buf[100];

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(1);
    }

    // Read the message from the FIFO
    read(fd, buf, sizeof(buf));

    // Print the message
    printf("Message received: %s\n", buf);

    // Close the FIFO after reading
    close(fd);

    return 0;
}

