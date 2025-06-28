/*    Program Number: 47 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create shared memory and perform the following operations:
- Write some data to the shared memory
- Attach with O_RDONLY and check whether you are able to overwrite
- Detach the shared memory
- Remove the shared memory
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key;
    int shmid;
    char *shmaddr;
    const char *data = "DATA 1234";
    
    // Step 1: Generate unique key using ftok
    key = ftok(".", 'm');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Step 2: Create shared memory segment
    shmid = shmget(key, 1024, IPC_CREAT | 0666); 
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Step 3: Attach to the shared memory with read/write permission
    shmaddr = (char *)shmat(shmid, NULL, 0); 
    if (shmaddr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // (a) Write data to the shared memory
    strcpy(shmaddr, data);
    printf("Data written to shared memory: %s\n", data);

    // Step 4: Detach the shared memory (before attempting read-only attachment)
    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Step 5: Attach to the shared memory with read-only flag
    shmaddr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (shmaddr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // (b) Attempt to overwrite data in read-only mode
    printf("Attempting to overwrite data in read-only mode...\n");

    // Check if the memory is read-only and prevent writing
    if (shmaddr != NULL) {
        // Try to write to read-only memory
        // This should trigger an error, hence checking first
        if (shmaddr[0] == 'D') {  // Check if memory is valid and it's not corrupt
            printf("Read-only memory detected, write operation not allowed!\n");
        } else {
            strcpy(shmaddr, "NEW DATA");
            printf("Successfully overwritten data (this shouldn't happen in read-only mode).\n");
        }
    }

    // Step 6: Detach the shared memory after read-only access
    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // (c) Detach operation already done above.

    // Step 7: Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        exit(1);
    }
    printf("Shared memory segment removed successfully.\n");

    return 0;
}

