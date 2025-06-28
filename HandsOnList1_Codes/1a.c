/*    Program Number: 1a 
Student Name:  Kavya Gupta; Register Number: IMT2023016
Date:  04-04-2025 
Description: This program creates a soft link (symbolic link) to a file using the symlink system call.  
*/ 

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char f1a_sourceFile[100];
    char f1a_softLink[100];

    printf("Enter the name of the original file: \n");
    scanf("%s",f1a_sourceFile);
    printf("Enter the name for the symbolic link: \n");
    scanf("%s",f1a_softLink);

    int status=symlink(f1a_sourceFile, f1a_softLink);  // Creates a symbolic link, returns 0 on success, -1 on failure

    if (status==0) {
        printf("Symbolic link created successfully.\n");
    } else {
        printf("Error: Unable to create symbolic link.\n");
    }
    return 0;
}
