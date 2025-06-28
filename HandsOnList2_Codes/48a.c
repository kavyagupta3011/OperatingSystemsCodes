/*    Program Number: 48(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a binary semaphore and initialize its value.
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Correct definition of semun
union semun {
    int val;                   // Used for SETVAL
    struct semid_ds *buf;      // For IPC_STAT, IPC_SET
    unsigned short *array;     // For GETALL, SETALL
};

int main() {
    key_t k = ftok(".", 'm');
    if (k == -1) {
        perror("ftok failed");
        exit(1);
    }

    int sid = semget(k, 1, IPC_CREAT | 0744);
    if (sid == -1) {
        perror("semget failed");
        exit(1);
    }

    printf("Semaphore ID: %d\n", sid);

    union semun val;
    val.val = 1; // Binary semaphore initialized to 1 (unlocked)

    if (semctl(sid, 0, SETVAL, val) == -1) {
        perror("semctl SETVAL failed");
        exit(1);
    }

    printf("Semaphore initialized successfully.\n");

    return 0;
}

//ipcs -s     # View semaphores
//ipcrm -s <semaphore_id>
//ipcs -s -i <semaphore_id>
