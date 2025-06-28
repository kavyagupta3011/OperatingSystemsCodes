/*    Program Number: 49(d)
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will implement a semaphore to protect any critical section by:
- Removing the created semaphore
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <stdlib.h>

int main()
{
    int k = ftok(".", 'k'); // Create a unique key for semaphore
    int sid = semget(k, 1, 0); // Get semaphore ID
    if (sid == -1) {
        perror("semget");
        exit(1);
    }

    if (semctl(sid, IPC_RMID, 0) == -1) { // Remove the semaphore
        perror("semctl");
        exit(1);
    }
    printf("Semaphore removed.\n");
    return 0;
}

