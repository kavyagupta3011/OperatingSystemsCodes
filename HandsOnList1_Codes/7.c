/*    Program Number: 7  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program copies the contents of file1 into file2, emulating the behavior of the cp command.  
*/  

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buffer[1000];  // Buffer to store file content
    ssize_t bytesRead;

    // Open source file in read-only mode
    int f1 = open("f7_file1", O_RDONLY);
    if (f1 < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file in write mode (create if it doesn’t exist)
    int f2 = open("f7_file2", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (f2 < 0) {
        perror("Error opening destination file");
        close(f1);
        return 1;
    }

    // Read and write in chunks to handle large files properly
    while ((bytesRead = read(f1, buffer, sizeof(buffer))) > 0) {
        write(f2, buffer, bytesRead);
    }

    // Close both files
    close(f1);
    close(f2);

    return 0;
}

/*running it :
 $ echo "Hello OS lab!" > f7_file1
$ ./file_copy
$ cat f7_file2
Hello OS lab!
$ diff f7_file1 f7_file2
# (no output means success!)
*/
