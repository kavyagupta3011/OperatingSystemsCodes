/*    Program Number: 49(c)
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will implement a semaphore to protect any critical section by:
- Protecting multiple pseudo resources (maybe two) using a counting semaphore
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define SHM_K 121
#define SHM_SIZE 1024

int file_write(int k, int fd)
{
    struct sembuf buf = {0, -1, 0};
    int sid = semget(k, 1, 0); // Get semaphore ID
    semop(sid, &buf, 1); // Lock semaphore

    printf("In Semaphore.\n");
    printf("Value of Semaphore: %d\n", semctl(sid, 0, GETVAL)); // Get semaphore value

    fd = open("49c.txt", O_RDWR | O_CREAT, 0777);
    write(fd, "data", sizeof("data"));
    sleep(10); // Simulate some delay

    buf.sem_op = 1; // Unlock semaphore
    semop(sid, &buf, 1);

    close(fd); // Close file after writing
}

int main()
{
    int k = ftok(".", 'k'); // Create a unique key for semaphore
    int arg = 2;
    int sid = semget(k, 1, IPC_CREAT | 0644); // Create semaphore
    semctl(sid, 0, SETVAL, arg); // Initialize semaphore value to 2 (counting semaphore)

    int fd = open("49c.txt", O_RDWR | O_CREAT, 0777); // Open file for writing
    write(fd, "TestTest", sizeof("TestTest"));
    close(fd); // Close the file after initial write

    int shmid;
    char *shmaddr;
    struct shmid_ds shminfo;

    shmid = shmget(SHM_K, SHM_SIZE, IPC_CREAT | 0644); // Create shared memory
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT CREATED.\n");

    shmaddr = shmat(shmid, NULL, 0); // Attach shared memory
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    printf("SHARED MEMORY SEGMENT ATTACHED.\n");

    strcpy(shmaddr, "TestTest"); // Write data into shared memory

    int frk = fork();
    if (frk == 0) {
        if (fork() == 0) {
            file_write(k, fd); // Call file write function in child
        } else {
            file_write(k, fd); // Call file write function in another child
        }
    } else {
        file_write(k, fd); // Parent also writes to file
    }
    return 0;
}

