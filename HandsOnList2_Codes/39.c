/*    Program Number: 39 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will wait for data to be written into a FIFO within 10 seconds, utilizing the select system call with the FIFO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define FIFO_PATH "myfifo39"

int main() {
    int fd;
    fd_set read_fds;
    struct timeval timeout;
    char buf[100];

    // Create FIFO if not exists
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open FIFO in non-blocking read-only mode
    fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set timeout to 10 seconds
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    printf("Waiting for data in FIFO for 10 seconds...\n");

    int retval = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("Timeout: No data written to FIFO within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &read_fds)) {
            int bytes = read(fd, buf, sizeof(buf));
            if (bytes > 0) {
                buf[bytes] = '\0';
                printf("Received: %s\n", buf);
            } else {
                printf("FIFO was closed before data could be read.\n");
            }
        }
    }

    close(fd);
    unlink(FIFO_PATH);
    return 0;
}

