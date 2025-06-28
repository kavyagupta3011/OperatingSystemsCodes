/*    Program Number: 14  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program takes a file path as input from the command line  
             and identifies the type of file using system calls.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat data;
    if (stat(argv[1], &data) == -1) {
        perror("stat");
        return 1;
    }

    if ((data.st_mode & S_IFMT) == S_IFIFO)
        printf("FIFO/pipe.\n");
    else if ((data.st_mode & S_IFMT) == S_IFSOCK)
        printf("Socket.\n");
    else if ((data.st_mode & S_IFMT) == S_IFDIR)
        printf("Directory.\n");
    else if ((data.st_mode & S_IFMT) == S_IFBLK)
        printf("Block Device.\n");
    else if ((data.st_mode & S_IFMT) == S_IFLNK)
        printf("Symlink.\n");
    else if ((data.st_mode & S_IFMT) == S_IFCHR)
        printf("Character Device.\n");
    else if ((data.st_mode & S_IFMT) == S_IFREG)
        printf("Regular File.\n");
    else
        printf("Unknown file type.\n");

    return 0;
}


/* test like this :
   touch myfile.txt
   ./14 myfile.txt
*/

