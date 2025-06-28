/*    Program Number: 44(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will receive messages from a message queue with 0 as a flag.
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
    
    // Access the message queue (without creating it)
    mid = msgget(k, 0); 
    if (mid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Attempt to receive a message with flag 0 (blocking)
    if (msgrcv(mid, &mBuff, sizeof(mBuff.data), 10, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    // Print received data
    printf("Data Received: %s\n", mBuff.data);

    // Display message queue info
    execlp("ipcs", "ipcs", "-q", NULL);

    return 0;
}

