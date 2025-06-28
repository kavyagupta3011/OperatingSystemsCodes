/*    Program Number: 17part2 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program simulates an online ticket reservation system.  
             - One program opens a file, stores a ticket number, and exits.  
             - Another program opens the file, applies a write lock, reads the  
               ticket number, increments it, prints the new ticket number,  
               and then closes the file.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

struct ticket {
    char train[30];
    int t_number;
};

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
    lock.l_len = sizeof(struct ticket);  // Lock only the struct size
    lock.l_pid = getpid();

    if (fcntl(f1, F_SETLKW, &lock) == -1) {
        perror("Error acquiring lock");
        close(f1);
        return 1;
    }

    struct ticket ticket1;
    if (read(f1, &ticket1, sizeof(ticket1)) != sizeof(ticket1)) {
        perror("Read failed");
        close(f1);
        return 1;
    }

    printf("Current Ticket Number: %d\n", ticket1.t_number);
    
    ticket1.t_number++; // Increment ticket number

    lseek(f1, 0, SEEK_SET);
    if (write(f1, &ticket1, sizeof(ticket1)) != sizeof(ticket1)) {
        perror("Write failed");
        close(f1);
        return 1;
    }

    // Unlock the file
    lock.l_type = F_UNLCK;
    if (fcntl(f1, F_SETLKW, &lock) == -1) {
        perror("Error unlocking");
    } else {
        printf("New Ticket Number: %d\n", ticket1.t_number);
    }

    close(f1);
    return 0;
}
