/*    Program Number: 63 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create an orphan process. The child process will use the kill system call to send a SIGKILL signal to the parent process.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    pid_t f = fork();

    if (f == 0) {
        // Child process
        pid_t ppid = getppid();
        printf("Child ID: %d | Parent ID before kill: %d\n", getpid(), ppid);
        fflush(stdout);

        sleep(1); // Let parent print first

        printf("Child: Sending SIGKILL to parent %d\n", ppid);
        fflush(stdout);

        kill(ppid, SIGKILL); // Kill the parent

        sleep(2); // Let parent die and become orphan

        printf("Child ID: %d | New Parent ID (should be 1): %d\n", getpid(), getppid());
        fflush(stdout);
    }
    else if (f > 0) {
        // Parent process
        printf("Parent ID: %d\n", getpid());
        fflush(stdout);
        while (1); // Wait to be killed
    }
    else {
        perror("fork");
        return 1;
    }

    return 0;
}

