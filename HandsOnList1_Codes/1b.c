/*    Program Number: 1b 
Student Name:  Kavya Gupta; Register Number: IMT2023016
Date:  04-04-2025 
Description: This program creates a hard link to a file using the link system call.  
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>  // For error handling

int main() {
    char f1b_sourceFile[100];
    char f1b_hardLink[100];

    printf("Enter the name of the original file:\n");
    scanf("%s", f1b_sourceFile);

    printf("Enter the name for the hard link:\n");
    scanf("%s", f1b_hardLink);

    // Check if the file exists; if not, create it
    int fd = open(f1b_sourceFile, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating source file");
        return 1;  // Exit if the file cannot be created
    }
    close(fd);  // Close the file after creating it

    // Now, create the hard link
    int status = link(f1b_sourceFile, f1b_hardLink);

    if (status == 0) {
        printf("Hard link has been created successfully.\n");
    } else {
        perror("Error creating hard link");
    }

    return 0;
}

