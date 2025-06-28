/*    Program Number: 44(b) sender
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program is the sender.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

struct msgbuf {
    long int type;
    char data[100];
} mBuff;

int main() {
    int mid;
    key_t k;
    
    // Generate unique key for the message queue
    k = ftok(".", 'm');
    
    // Create or access the message queue
    mid = msgget(k, IPC_CREAT | 0666);
    if (mid == -1) {
        perror("msgget failed");
        return 1;
    }
    
    // Set the type of the message
    mBuff.type = 10;  // Match this with the type in the receiver program
    printf("Enter message to send: ");
    fgets(mBuff.data, 100, stdin);

    // Send the message to the queue
    if (msgsnd(mid, &mBuff, sizeof(mBuff.data), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Message sent to the queue\n");

    return 0;
}

