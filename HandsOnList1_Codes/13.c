/*    Program Number: 13  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program waits for input from STDIN for 10 seconds  
             using the select system call and prints whether data  
             is available within the specified time.  
*/  

#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set read_fds;
    struct timeval timeout;
    int result;

    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);  // stdin

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input (10 seconds)...\n");
    result = select(1, &read_fds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("Error in select()");
    } else if (result > 0) {
        printf("Input detected! Reading it now...\n");
        char buf[100];
        read(0, buf, sizeof(buf));  // read to clear buffer
        // Optional: print the input
        printf("You typed: %s", buf);
    } else {
        printf("No input received in 10 seconds.\n");
    }

    return 0;
}

