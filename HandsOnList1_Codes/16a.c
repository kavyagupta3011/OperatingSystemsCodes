/*    Program Number: 16a  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program implements mandatory locking by applying a write lock  
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
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    // Try to set a write lock
    if (fcntl(f1, F_SETLKW, &lock) == -1) {
        perror("Locking unsuccessful");
        close(f1);
        return 1;
    }

    printf("Process %d has locked the file.\n", lock.l_pid);

    // Hold the lock for 20 seconds
    sleep(20);

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



/*
touch testfile
chmod 660 testfile         # rw-rw----
chmod g+s testfile         # Set SGID
ls -l testfile
Enable mandatory locking in kernel (if needed)
cat /proc/sys/fs/mandatory_locking
*/
