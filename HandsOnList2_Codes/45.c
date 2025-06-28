/*    Program Number: 45 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will change the existing message queue permissions using the msqid_ds structure.
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t k;
    int mid;
    
    // Generate the key for the message queue using ftok
    k = ftok(".", 'm');
    
    // Create the message queue with permission 0744 (owner read/write, others read)
    mid = msgget(k, 0744 | IPC_CREAT);
    if (mid == -1) {
        perror("msgget failed");
        return 1;
    }

    // Declare msqid_ds structure to hold message queue information
    struct msqid_ds ms_info;
    
    // Get current information about the message queue
    if (msgctl(mid, IPC_STAT, &ms_info) == -1) {
        perror("msgctl IPC_STAT failed");
        return 1;
    }

    // Print current permissions
    struct ipc_perm* permissions = &ms_info.msg_perm;
    printf("Current Permissions : %o\n", permissions->mode);

    // Change the permissions of the message queue (e.g., to 511, which is rwx--x--x)
    permissions->mode = 511; // 511 in octal (rwx--x--x)

    // Set the updated permissions using msgctl with IPC_SET
    if (msgctl(mid, IPC_SET, &ms_info) == -1) {
        perror("msgctl IPC_SET failed");
        return 1;
    }

    // Print the updated permissions
    if (msgctl(mid, IPC_STAT, &ms_info) == -1) {
        perror("msgctl IPC_STAT failed");
        return 1;
    }
    printf("Updated Permissions : %o\n", permissions->mode);

    return 0;
}

