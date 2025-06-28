/*    Program Number: 44(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will receive messages from a message queue with IPC_NOWAIT as a flag.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>
struct msgbuf {
    long int type;
    char data[100];
} mBuff;

int main() {
    int mid;
    key_t k;
    
    // Generate unique key for the message queue
    k = ftok(".", 'm');
    
    // Access the message queue (do not create it)
    mid = msgget(k, 0);
    if (mid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Receive the message with type 10 (non-blocking with IPC_NOWAIT)
    if (msgrcv(mid, &mBuff, sizeof(mBuff.data), 10, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No messages available in the queue.\n");
        } else {
            perror("msgrcv failed");
        }
        return 1;
    }

    // Print the received message
    printf("Data Received: %s\n", mBuff.data);

    // Display message queue info using ipcs command
    execlp("ipcs", "ipcs", "-q", NULL);

    return 0;
}

