/*    Program Number: 42 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will print various details about a message queue using msqid_ds and ipc_perm structures, including:
- Access permission
- UID, GID
- Time of last message sent and received
- Time of last change in the message queue
- Size of the queue
- Number of messages in the queue
- Maximum number of bytes allowed
- PID of the msgsnd and msgrcv
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main() {
    key_t k;
    int mid;
    struct msqid_ds ms_info;

    // Generate unique key and get/create msg queue
    k = ftok(".", 'm');
    if (k == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    mid = msgget(k, 0744 | IPC_CREAT);
    if (mid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    // Get message queue information
    if (msgctl(mid, IPC_STAT, &ms_info) == -1) {
        perror("msgctl failed");
        exit(EXIT_FAILURE);
    }

    struct ipc_perm permissions = ms_info.msg_perm;

    printf("Access Permissions       = %o\n", permissions.mode);
    printf("UID                      = %d\n", permissions.uid);
    printf("GID                      = %d\n", permissions.gid);
    printf("Time of Last Msg Sent    = %ld\n", ms_info.msg_stime);
    printf("Time of Last Msg Received= %ld\n", ms_info.msg_rtime);
    printf("Time of Last Change      = %ld\n", ms_info.msg_ctime);
    printf("Current Bytes in Queue   = %lu\n", ms_info.msg_cbytes);
    printf("Number of Messages       = %lu\n", ms_info.msg_qnum);
    printf("Max Bytes Allowed        = %lu\n", ms_info.msg_qbytes);
    printf("PID of Last msgsnd       = %d\n", ms_info.msg_lspid);
    printf("PID of Last msgrcv       = %d\n", ms_info.msg_lrpid);

    return 0;
}

