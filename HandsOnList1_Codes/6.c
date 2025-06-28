/*    Program Number: 6  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program takes input from STDIN and displays it on STDOUT using only read and write system calls.  
*/  

#include <stdio.h>
#include <unistd.h>

int main() {
    char buffer[20];  // Buffer size 20, but we read only 10

    // Read up to 10 bytes from standard input (STDIN)
    ssize_t bytes_read = read(STDIN_FILENO, buffer, 10);

    if (bytes_read == -1) {
        perror("Error reading input");
        return 1;
    }

    // Null-terminate the string (optional, for safety)
    buffer[bytes_read] = '\0';

    // Write the exact number of bytes read to standard output (STDOUT)
    write(STDOUT_FILENO, buffer, bytes_read);

    return 0;
}

