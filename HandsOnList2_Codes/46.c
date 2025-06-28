/*    Program Number: 46 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will remove the message queue.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() 
{ 
    key_t k;
    int mid; 

    // Generate unique key for the message queue using ftok
    k = ftok(".", 'm');

    // Create the message queue with permission 0744 (read/write for owner, read for others)
    mid = msgget(k, IPC_CREAT | 0744); 

    if (mid == -1) {
        perror("msgget failed");
        return 1;
    }

    printf("Message Queue Created with ID: %d\n", mid);

    // Now, remove the message queue
    if (msgctl(mid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        return 1;
    }

    printf("Message Queue Removed Successfully\n");

    // Verify message queue removal using ipcs
    execlp("ipcs", "ipcs", "-q", NULL);

    return 0;
}

