/*    Program Number: 9  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program prints various details about a given file, including:  
             a. Inode  
             b. Number of hard links  
             c. UID  
             d. GID  
             e. Size  
             f. Block size  
             g. Number of blocks  
             h. Time of last access  
             i. Time of last modification  
             j. Time of last change  
*/  

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

int main() {
    // Step 1: Create the file first
    char *file_name = "f9_file.txt";
    int file_create = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (file_create < 0) {
        perror("Error creating file");
        return 1;
    }
    write(file_create, "Sample content in file.\n", 24);
    close(file_create);

    // Step 2: Fetch and display file information
    struct stat info;
    if (stat(file_name, &info) < 0) {
        perror("Error retrieving file info");
        return 1;
    }

    printf("Details of file '%s' are as follows:\n", file_name);
    printf("Inode value              : %d\n", (int)info.st_ino);
    printf("Number of hard links     : %d\n", (int)info.st_nlink);
    printf("User ID                  : %d\n", (int)info.st_uid);
    printf("Group ID                 : %d\n", (int)info.st_gid);
    printf("File size (bytes)        : %ld\n", info.st_size);
    printf("Size of block            : %ld\n", info.st_blksize);
    printf("Number of blocks         : %ld\n", info.st_blocks);
    printf("Time of last access      : %s", ctime(&info.st_atime));
    printf("Time of last modification: %s", ctime(&info.st_mtime));
    printf("Time of last change      : %s", ctime(&info.st_ctime));

    return 0;
}
