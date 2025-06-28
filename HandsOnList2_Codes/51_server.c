/*    Program Number: 51_server 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will enable communication between two machines using sockets.
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main()
{
    struct sockaddr_in serv, cli;
    int portno = 5555;
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Error: ");
        return -1;
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno);

    int opt = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error: ");
        return -1;
    }

    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1) {
        perror("Bind error:");
        return -1;
    }

    if (listen(sd, 100) == -1) {
        perror("Listen error:");
        return -1;
    }

    printf("Listening.\n");

    int nsd;
    char buf[100];
    socklen_t size = sizeof(cli);

    while (1) {
        printf("(1)Accept (2)Leave?\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 2) {
            close(sd);
            printf("Exiting\n");
            return 0;
        }

        nsd = accept(sd, (struct sockaddr *)&cli, &size);
        memset(buf, 0, sizeof(buf));
        read(nsd, buf, sizeof(buf));
        printf("Client Message : %s\n", buf);
        char *message = "Received";
        sleep(5);
        write(nsd, message, strlen(message) + 1);
        getchar();  // waits for Enter key
        close(nsd);
    }

    close(sd);
}

