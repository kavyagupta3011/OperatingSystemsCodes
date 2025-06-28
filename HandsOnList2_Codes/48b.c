/*    Program Number: 48(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a counting semaphore and initialize its value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    const char *filename = "counting";
    
    // Step 1: Ensure the file exists for ftok()
    int fd = open(filename, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("Failed to create file for ftok");
        exit(1);
    }
    close(fd);

    // Step 2: Generate key and create semaphore
    key_t key = ftok(filename, 'q');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    int sid = semget(key, 1, IPC_CREAT | 0744);
    if (sid == -1) {
        perror("semget failed");
        exit(1);
    }

    printf("Semaphore ID: %d\n", sid);

    // Step 3: Initialize counting semaphore with value 2
    union semun val;
    val.val = 2;

    if (semctl(sid, 0, SETVAL, val) == -1) {
        perror("semctl SETVAL failed");
        exit(1);
    }

    printf("Counting semaphore initialized to 2.\n");

    return 0;
}


//ipcs -s
//ipcs -s -i <semid>
