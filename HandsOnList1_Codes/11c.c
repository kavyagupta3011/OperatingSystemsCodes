/*    Program Number: 11c  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program opens a file, duplicates the file descriptor using fcntl,  appends data to the file using both descriptors, and verifies  whether the file is updated correctly.  
*/  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char f_name[] = "f13_fcntl_test.txt";  // Predefined filename

    // Create the file first to ensure it exists
    int create_fd = open(f_name, O_CREAT | O_WRONLY, 0777);
    if (create_fd < 0) {
        perror("File creation failed");
        return 1;
    }
    close(create_fd); // Close after creation

    // Open file in append mode
    int f1 = open(f_name, O_WRONLY | O_APPEND);
    if (f1 < 0) {
        perror("File opening failed");
        return 1;
    }

    // Duplicate file descriptor using fcntl
    int f2 = fcntl(f1, F_DUPFD, 0);  // Duplicates f1 using lowest available fd
    if (f2 < 0) {
        perror("fcntl failed");
        close(f1);
        return 1;
    }

    // Writing using both descriptors (appending to the file)
    write(f1, "Original File descriptor\n", sizeof("Original File descriptor\n") - 1);
    write(f2, "Duplicate File descriptor\n", sizeof("Duplicate File descriptor\n") - 1);

    // Close descriptors
    close(f1);
    close(f2);

    // Verification step: Open the file in read mode and print its contents
    int read_fd = open(f_name, O_RDONLY);
    if (read_fd < 0) {
        perror("File verification failed");
        return 1;
    }

    char buffer[256] = {'\0'};
    int bytes_read = read(read_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        printf("File contents after writing:\n%s", buffer);
    }

    close(read_fd);
    return 0;
}
