/*    Program Number: 10  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program opens a file in read-write mode, writes 10 bytes, moves  
             the file pointer by 10 bytes using lseek, and then writes another 10 bytes.  
             a. Checks the return value of lseek.  
             b. Opens the file with od command to examine the empty spaces between the data.  
*/  

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
    char *file_name = "f10_data.txt"; // Fixed file name for reliability

    // Open file in read-write mode, create if not exists
    int f1 = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (f1 < 0) {
        perror("File opening failed");
        return 1;
    }

    char data[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Write first 10 bytes
    write(f1, data, 10);

    // Move file pointer by 10 bytes
    off_t position = lseek(f1, 10, SEEK_CUR);
    if (position == -1) {
        perror("lseek failed");
        close(f1);
        return 1;
    } else {
        printf("File pointer moved to position: %ld\n", (long)position);
    }

    // Write another 10 bytes
    write(f1, data, 10);

    close(f1);

    printf("File '%s' created. Use `od -c %s` to view gaps.\n", file_name, file_name);
    return 0;
}
