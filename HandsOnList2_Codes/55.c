/*    Program Number: 55 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will set a system resource limit using the setrlimit system call.
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/resource.h>
#include<errno.h>
#include<fcntl.h>
#include <sys/types.h>
#include<string.h>

void status(int fd)
{
    if(fd < 0)
        perror("File Open Unsuccessful.\n");
    else
        write(1,"Success\n",8);
}

int main()
{
    struct rlimit lim, newLim;

    // Set soft limit to 10 and hard limit to 1000 for the number of open files
    lim.rlim_cur = 10;  // Soft limit increased to 10
    lim.rlim_max = 1000;  // Hard limit remains 1000

    // Set the resource limit
    if(setrlimit(RLIMIT_NOFILE, &lim) == -1) {
        write(1, "Could not change the limit on number of file descriptors.\n", 58);
        fprintf(stderr, "%s\n", strerror(errno));
        return 1; // Return failure if unable to set limit
    }

    // Check the current limits after setting them
    if(getrlimit(RLIMIT_NOFILE, &newLim) == 0)
        printf("New limits : Soft limit = %ld \t Hard limit = %ld \n", newLim.rlim_cur, newLim.rlim_max);
    else
        fprintf(stderr, "%s\n", strerror(errno));

    // Try to open two files
    int fd1 = open("file1.txt", O_RDONLY | O_CREAT, 0666);
    int fd2 = open("file2.txt", O_RDONLY | O_CREAT, 0666);

    // Check if file descriptors are successfully opened
    status(fd1);
    status(fd2);

    return 0;
}

