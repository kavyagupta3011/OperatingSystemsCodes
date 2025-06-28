/*    Program Number: 16b  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program implements mandatory locking by applying a read lock  
             on a file using the fcntl system call.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int f1 = open(argv[1], O_RDWR);
    if (f1 == -1) {
        perror("Error opening file");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    // Try to set a read lock
    if (fcntl(f1, F_SETLKW, &lock) == -1) {
        perror("Locking unsuccessful");
        close(f1);
        return 1;
    }

    printf("Process %d has acquired a read lock on the file.\n", lock.l_pid);

    // Hold the lock for 10 seconds
    sleep(10);

    // Unlock
    lock.l_type = F_UNLCK;
    if (fcntl(f1, F_SETLKW, &lock) == -1) {
        perror("Unlocking failed");
    } else {
        printf("File unlocked.\n");
    }

    close(f1);
    return 0;
}
