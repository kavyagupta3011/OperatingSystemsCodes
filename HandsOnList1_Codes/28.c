/*    Program Number: 28  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program finds out the priority of a running program and modifies it using the nice command.  
*/  

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    int newNice;
    
    // Get current priority (nice value)
    int priority = getpriority(PRIO_PROCESS, getpid());
    printf("Current Priority (Nice Value): %d\n", priority);

    printf("Enter new nice value: ");
    scanf("%d", &newNice);

    // Modify the nice value
    errno = 0; // Clear errno before calling nice()
    int result = nice(newNice);
    
    // Error handling
    if (result == -1 && errno != 0) {
        perror("Error changing priority");
        return 1;
    }

    // Get new priority (nice value) after modification
    int newPriority = getpriority(PRIO_PROCESS, getpid());
    printf("Updated Priority (Nice Value): %d\n", newPriority);

    return 0;
}
