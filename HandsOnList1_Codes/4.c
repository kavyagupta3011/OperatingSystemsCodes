/*    Program Number: 4  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program opens an existing file in read-write mode and experiments with the O_EXCL flag.  
*/  

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Create the file if it doesn't exist
    int create_flag = open("f4_file", O_CREAT | O_WRONLY, 0666);
    if (create_flag == -1) {
        perror("Error creating file");
        return 1;
    }
    close(create_flag);

    printf("File 'f4_file' has been created. Now attempting to open it with O_EXCL...\n");

    // Attempt to open the existing file in read-write mode with O_EXCL | O_CREAT
    int flag = open("f4_file", O_RDWR | O_CREAT | O_EXCL, 0666);

    if (flag == -1) {
        perror("Error opening file with O_EXCL");
    } else {
        printf("File opened successfully. File descriptor: %d\n", flag);
        close(flag);
    }

    return 0;
}

