/*    Program Number: 62 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will ignore a SIGINT signal and then reset it to the default action using the sigaction system call.
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    // Initialize the sigaction structure
    struct sigaction new_action;

    // Ignore SIGINT
    new_action.sa_handler = SIG_IGN;
    sigemptyset(&new_action.sa_mask);  // Clear signal mask
    new_action.sa_flags = 0;

    // Set SIGINT to be ignored
    if (sigaction(SIGINT, &new_action, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    // Simulate work by printing numbers
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", i);
        sleep(1);
    }

    // Reset SIGINT to default action (termination of the process)
    new_action.sa_handler = SIG_DFL;  // Default action
    if (sigaction(SIGINT, &new_action, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    printf("SIGINT Reset.\n");

    // Simulate more work by printing numbers
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", i);
        sleep(1);
    }

    return 0;
}

