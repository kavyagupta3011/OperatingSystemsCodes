/*    Program Number: 8  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program opens a file in read-only mode, reads it line by line,  
and displays each line as it is read. The file is closed upon reaching the end.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *val = (char *)malloc(sizeof(char));

    // Step 1: Create the file and write some sample content
    int f_create = open("f8_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (f_create < 0) {
        perror("Error creating file");
        return 1;
    }
    write(f_create, "Hello, this is line 1.\nThis is line 2.\nFinal line here.\n", 55);
    close(f_create);

    // Step 2: Open the file in read-only mode
    int f1 = open("f8_file.txt", O_RDONLY);
    if (f1 < 0) {
        perror("Error opening file");
        return 1;
    }

    // Step 3: Read line by line and display output
    read(f1, val, 1);
    while (1) {
        printf("%c", *val);
        if (*val == '\n') {
            sleep(1);  // Pause for clarity when displaying new lines
        }
        int x = read(f1, val, 1);
        if (x == 0)
            break;
    }

    // Step 4: Close the file
    close(f1);
    free(val);

    return 0;
}
