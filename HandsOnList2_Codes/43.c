/*    Program Number: 43 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will send messages to a message queue and verify using the $ipcs -q command.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

struct mbuf {
    long int type;
    char data[100];
} mBuff;

int main() {
    int mid;
    key_t k;

    // Generate key
    k = ftok(".", 'm');
    if (k == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Get existing message queue
    mid = msgget(k, 0); 
    if (mid == -1) {
        perror("msgget failed. Create the queue first.");
        exit(EXIT_FAILURE);
    }

    // Set message type and read message
    mBuff.type = 10;
    printf("Enter message to send: ");
    fgets(mBuff.data, sizeof(mBuff.data), stdin);
    mBuff.data[strcspn(mBuff.data, "\n")] = '\0';  // Remove newline

    // Send the message (excluding type field in size)
    if (msgsnd(mid, &mBuff.data, sizeof(mBuff.data), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    // Show message queues using ipcs
    execlp("ipcs", "ipcs", "-q", NULL);

    return 0;
}



//verify with ipcs -q
