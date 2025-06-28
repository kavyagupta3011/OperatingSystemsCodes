/*    Program Number: 52(a) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a concurrent server using fork.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX_NUM_CLIENTS 5
#define PORT 3001

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int serv, cli;
    char buffer[256];

    if ((serv = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serv, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serv, MAX_NUM_CLIENTS) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        cli = accept(serv, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (cli < 0) {
            perror("Accept failed");
            continue;
        }

        if (!fork()) {
            close(serv);
            read(cli, buffer, sizeof(buffer));
            printf("Client Data : %s\n", buffer);
            const char *response = "Server Response.";
            write(cli, response, strlen(response));
            close(cli);
            exit(0);
        } else {
            close(cli);
        }
    }

    close(serv);
    return 0;
}

