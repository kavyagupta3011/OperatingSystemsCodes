/*    Program Number: 17part1  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program simulates an online ticket reservation system by  
             implementing a write lock using the fcntl system call to ensure  
             exclusive access to the ticket number stored in a file.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct ticket {
    char train[30];
    int t_number;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int f1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (f1 == -1) {
        perror("Error opening file");
        return 1;
    }

    struct ticket Ticket;
    strcpy(Ticket.train, "Rajdhani_Express");
    Ticket.t_number = 1;

    if (write(f1, &Ticket, sizeof(Ticket)) != sizeof(Ticket)) {
        perror("Write failed");
        close(f1);
        return 1;
    }

    printf("Data written:\n");
    printf("Train Name: %s\n", Ticket.train);
    printf("Ticket Number: %d\n", Ticket.t_number);

    close(f1);
    return 0;
}
