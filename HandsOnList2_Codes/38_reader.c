/*    Program Number: 38_reader
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will establish two-way communication through FIFO (reader).
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

    // Open FIFO files
    fd_receive = open(FIFO_SEND, O_RDONLY);
    if (fd_receive == -1) {
        perror("Error opening fifo1 for reading");
        exit(1);
    }
    fd_send = open(FIFO_RECEIVE, O_WRONLY);
    if (fd_send == -1) {
        perror("Error opening fifo2 for writing");
        exit(1);
    }

    // Receive message
    read(fd_receive, receive_msg, sizeof(receive_msg));
    printf("Reader: Received message: %s\n", receive_msg);

    // Send response message
    printf("Reader: Enter response message: ");
    scanf("%[^\n]", send_msg);
    write(fd_send, send_msg, strlen(send_msg) + 1);

    // Close FIFO files
    close(fd_send);
    close(fd_receive);

    return 0;
}

