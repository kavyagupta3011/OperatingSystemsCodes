/*    Program Number: 12  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program determines the opening mode of a file  
             using the fcntl system call.  
*/  

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char f12_filename[100];
    printf("Enter file name: ");
    scanf("%s", f12_filename);

    int fd = open(f12_filename, O_RDONLY | O_CREAT, 0777);
    if (fd < 0) {
        perror("File open failed");
        return 1;
    }

    int mode = fcntl(fd, F_GETFL);
    if (mode < 0) {
        perror("fcntl failed");
        close(fd);
        return 1;
    }

    int access_mode = mode & O_ACCMODE;  // Masking to get access mode only

    if (access_mode == O_RDONLY)
        printf("File is opened in READ MODE.\n");
    else if (access_mode == O_WRONLY)
        printf("File is opened in WRITE MODE.\n");
    else if (access_mode == O_RDWR)
        printf("File is opened in READ & WRITE MODE.\n");
    else
        printf("Unknown access mode.\n");

    if (mode & O_APPEND)
        printf("File is also opened in APPEND mode.\n");

    close(fd);
    return 0;
}

