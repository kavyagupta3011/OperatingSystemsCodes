/*    Program Number: 49(b)
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will implement a semaphore to protect any critical section by:
- Protecting shared memory from concurrent write access
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>

#define SHM_K 112
#define SHM_SIZE 1024

int main()
{
    int k = ftok(".",'k');
    int para = 1;
    int sid = semget(k,1,IPC_CREAT | 0644);
    semctl(sid,0,SETVAL,para);

    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    shmid = shmget(SHM_K, SHM_SIZE, IPC_CREAT | 0644);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT CREATED.\n");
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT ATTACHED.\n");
    printf("--------------------------------\n");
    printf("Please enter the number of tickets you want:\n");
    scanf("%s", shmaddr);  // This writes the user input into shared memory

    // Now, we use the semaphore to synchronize
    struct sembuf buf = {0, -1, 0};  // Wait (lock) operation
    sid = semget(k, 1, 0);  // Get the semaphore ID
    semop(sid, &buf, 1);  // Perform the semaphore operation to lock

    // Modify the shared memory (critical section)
    printf("Modifying shared memory...\n");
    strcpy(shmaddr, "101");  // Change the ticket number to 101

    printf("Shared memory updated. New ticket number: %s\n", shmaddr);

    sleep(2);  // Simulate some processing time

    // Release the semaphore (unlock)
    buf.sem_op = 1;  // Signal (release) operation
    semop(sid, &buf, 1);  // Perform the semaphore operation to unlock

    // Detach shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT DETACHED.\n");

    // Optionally remove the shared memory
    // if (shmctl(shmid, IPC_RMID, &shminfo) == -1) {
    //     perror("shmctl");
    //     exit(1);
    // }

    return 0;
}

