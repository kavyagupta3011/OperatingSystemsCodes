/*    Program Number: 41 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a message queue and print the key and message queue ID.
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int mid;
    key_t k;

    // Generate a unique key
    k = ftok(".", 'm');
    if (k == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    // Create the message queue
    mid = msgget(k, IPC_CREAT | 0744);
    if (mid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    printf("Key value: %d \nMessage queue id: %d \n", k, mid);

    return 0;
}
// use ipcs -q after running to see all message queue ids
