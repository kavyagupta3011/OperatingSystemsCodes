/*    Program Number: 3  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a file using the creat() system call and prints its file descriptor value.  
*/  

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char f3_filename[100];

    printf("Enter the filename to create: ");
    scanf("%s", f3_filename);

    // Create the file with read & write permissions for owner, group, and others
    int fd = creat(f3_filename, 0666);  

    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    printf("File created successfully. File descriptor: %d\n", fd);
	
    /*to keep the process running so that we can check file descriptors in /proc, we can do this :
     printf("Process ID: %d\n", getpid());
    while (1) {
        sleep(10);
    }*/


    // Close the file
    close(fd);
    return 0;
}
