/*    Program Number: 49(a)
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will implement a semaphore to protect any critical section by:
- Rewriting the ticket number creation program using a semaphore
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_K 111
#define SHM_SIZE 1024

int main()
{
    int k = ftok(".", 'k'); // Create a unique key for semaphore
    int para = 1;
    int sid = semget(k, 1, IPC_CREAT | 0644); // Create a semaphore set with one semaphore
    semctl(sid, 0, SETVAL, para); // Initialize semaphore value to 1 (binary semaphore)

    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    shmid = shmget(SHM_K, SHM_SIZE, IPC_CREAT | 0644); // Create shared memory
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT CREATED.\n");

    shmaddr = shmat(shmid, NULL, 0); // Attach shared memory to process address space
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT ATTACHED.\n");

    printf("--------------------------------\n");
    printf("Please enter the number of tickets you want: \n");
    scanf("%s", shmaddr); // Read the ticket number into shared memory

    int frk = fork();
    if (frk == 0) {
        struct sembuf buf = {0, -1, 0};
        semop(sid, &buf, 1); // Lock the semaphore (decrement)
        printf("Child. Current ticket count: %s\n", shmaddr);
        printf("Child. Enter the new number of tickets: \n");
        getchar(); // Consume the newline character
        scanf("%s", shmaddr); // Update ticket number in shared memory
        buf.sem_op = 1; // Unlock the semaphore (increment)
        semop(sid, &buf, 1);
    }
    else {
        struct sembuf buf = {0, -1, 0};
        sleep(2); // Wait for child to update the ticket number
        semop(sid, &buf, 1); // Lock the semaphore (decrement)
        printf("Parent. Current ticket count: %s\n", shmaddr);
        buf.sem_op = 1; // Unlock the semaphore (increment)
        semop(sid, &buf, 1);
    }

    if (shmdt(shmaddr) == -1) { // Detach shared memory
        perror("shmdt");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT DETACHED.\n");
    return 0;
}

