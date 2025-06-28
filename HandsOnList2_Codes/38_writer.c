/*    Program Number: 38_writer 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will establish two-way communication through FIFO (writer).
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define FIFO_SEND "fifo1"
#define FIFO_RECEIVE "fifo2"

int main(){
    int fd_send, fd_receive;
    char send_msg[100] = {0};
    char receive_msg[100] = {0};

    // Create the FIFO files if they don't exist
    if (mkfifo(FIFO_SEND, 0666) == -1) {
        perror("Error creating fifo1");
        exit(1);
    }
    if (mkfifo(FIFO_RECEIVE, 0666) == -1) {
        perror("Error creating fifo2");
        exit(1);
    }

    // Open FIFO files
    fd_send = open(FIFO_SEND, O_WRONLY);
    if (fd_send == -1) {
        perror("Error opening fifo1 for writing");
        exit(1);
    }
    fd_receive = open(FIFO_RECEIVE, O_RDONLY);
    if (fd_receive == -1) {
        perror("Error opening fifo2 for reading");
        exit(1);
    }

    // Send message
    printf("Writer: Enter message to send: ");
    scanf("%[^\n]", send_msg);
    write(fd_send, send_msg, strlen(send_msg) + 1);

    // Receive message
    read(fd_receive, receive_msg, sizeof(receive_msg));
    printf("Writer: Received message: %s\n", receive_msg);

    // Close and unlink FIFOs
    close(fd_send);
    close(fd_receive);
    unlink(FIFO_SEND);
    unlink(FIFO_RECEIVE);

    return 0;
}

