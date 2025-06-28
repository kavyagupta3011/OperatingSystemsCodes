/*    Program Number: 51_rec 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will enable communication between two machines using sockets.
*/


#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>  // required for inet_addr

int main()
{
    struct sockaddr_in serv;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Error: ");
        return -1;
    }

    int portno = 5555;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");  // ✅ change to actual server IP for inter-machine
    serv.sin_port = htons(portno);

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) != -1) {
        char msg[] = "TestTest";
        write(sd, msg, strlen(msg) + 1);

        char buf[100] = {0};
        read(sd, buf, sizeof(buf));
        printf("Server Ack : %s\n", buf);
    } else {
        printf("Connection unsuccessful.\n");
        perror("");
    }

    close(sd);
}

