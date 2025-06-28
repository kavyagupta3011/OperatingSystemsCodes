/*    Program Number: 30  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program creates a daemon process to execute a task at a specific time.  
*/  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        printf("Daemon PID: %d\n", pid);
        exit(0);  // Parent exits, only child continues
    }

    // Child becomes a daemon
    setsid();  // Create a new session
    chdir("/");  // Change working directory to root
    umask(0);  // Reset file mode mask

    close(STDIN_FILENO);  // Close standard input
    close(STDOUT_FILENO); // Close standard output
    close(STDERR_FILENO); // Close standard error

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        if (t->tm_hour == 15  && t->tm_min == 5) {  // Execute task at 3:05 PM
            int log_file = open("/tmp/new_daemon_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
            dprintf(log_file, "Task executed at 3:05 PM\n");
            close(log_file);
            sleep(60);  // Prevent multiple executions in the same minute
        }
        sleep(30);  // Check every 30 seconds
    }

    return 0;
}

/*test : 
gcc randomexec.c -o randomexec
gcc Testing2obj.c -o Testing2obj
gcc 25a.c -o exec_a
gcc 25b.c -o exec_b
./exec_a
./exec_b
*/
