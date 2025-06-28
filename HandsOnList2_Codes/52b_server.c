/*    Program Number: 52(b) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create a concurrent server using pthread_create.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX_NUM_CLIENTS 5
#define PORT 3001

void* handle_client(void* arg) {
    int cli = *(int*)arg;
    free(arg);
    char buffer[500];
    ssize_t num_bytes = read(cli, buffer, sizeof(buffer) - 1);
    if (num_bytes > 0) {
        buffer[num_bytes] = '\0';
        printf("Client Data : %s\n", buffer);
        const char* response = "Server Response.";
        write(cli, response, strlen(response));
    }
    close(cli);
    pthread_exit(NULL);
}

int main() {
    int serv, cli;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((serv = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serv, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serv, MAX_NUM_CLIENTS) < 0) {
        perror("Listening Failed");
        exit(EXIT_FAILURE);
    }

    pthread_t client_threads[MAX_NUM_CLIENTS];
    int clients = 0;

    while (1) {
        cli = accept(serv, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (cli < 0) {
            perror("Accept Failed");
            continue;
        }

        int* new_cli = malloc(sizeof(int));
        *new_cli = cli;
        pthread_create(&client_threads[clients], NULL, handle_client, new_cli);
        clients++;

        if (clients >= MAX_NUM_CLIENTS) {
            for (int i = 0; i < clients; i++) {
                pthread_join(client_threads[i], NULL);
            }
            clients = 0;
        }
    }

    close(serv);
    return 0;
}

