/*    Program Number: 5  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program continuously generates five new files in an infinite loop. It is executed in the background, allowing inspection of the file descriptor table at /proc/pid/fd.  
*/  

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd1 = open("f5_file1", O_CREAT | O_WRONLY, 0666);
    int fd2 = open("f5_file2", O_CREAT | O_WRONLY, 0666);
    int fd3 = open("f5_file3", O_CREAT | O_WRONLY, 0666);
    int fd4 = open("f5_file4", O_CREAT | O_WRONLY, 0666);
    int fd5 = open("f5_file5", O_CREAT | O_WRONLY, 0666);

    if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1) {
        perror("Error creating files");
        return 1;
    }

    printf("Files created successfully. File descriptors: %d, %d, %d, %d, %d\n", 
           fd1, fd2, fd3, fd4, fd5);

    // Infinite loop to keep process running
    while (1) {
        sleep(1);  // Prevents high CPU usage
    }

    return 0;
}

