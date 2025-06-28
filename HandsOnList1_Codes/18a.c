/*    Program Number: 18a  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program implements record locking by applying a write lock  
             on a specific record within a file to ensure exclusive access  
             for writing operations.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int recNum;
    int fd = open(argv[1], O_WRONLY, 0777);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("Enter record number to lock: ");
    scanf("%d", &recNum);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (recNum - 1) * 100;
    lock.l_len = 100;
    lock.l_pid = getpid();

    printf("Attempting to lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) != -1) {
        printf("Locked record %d (PID: %d)\n", recNum, lock.l_pid);

        char userInput;
        char buffer[100] = "Updated data";
        lseek(fd, (recNum - 1) * 100, SEEK_SET);
        write(fd, buffer, 100);

        do {
            printf("Enter 'U' to unlock: ");
            scanf(" %c", &userInput);
        } while (userInput != 'U');

        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        printf("Unlocked record %d\n", recNum);
    } else {
        printf("Failed to acquire lock.\n");
    }

    close(fd);
    return 0;
}
