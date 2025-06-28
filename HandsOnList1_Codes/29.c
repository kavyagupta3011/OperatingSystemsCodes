/*    Program Number: 29  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program obtains the scheduling policy of a process and modifies it (e.g., SCHED_FIFO, SCHED_RR).  
*/  

#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <stdlib.h>

void print_policy(int policy) {
    if (policy == SCHED_FIFO)
        printf("FIFO (SCHED_FIFO)\n");
    else if (policy == SCHED_RR)
        printf("Round Robin (SCHED_RR)\n");
    else if (policy == SCHED_OTHER)
        printf("Default (SCHED_OTHER)\n");
    else
        printf("Unknown Policy\n");
}

int main() {
    pid_t pid = getpid();
    int policy, priority;

    // Get the current scheduling policy
    int oldScheduling = sched_getscheduler(pid);
    if (oldScheduling == -1) {
        perror("Error getting scheduling policy");
        return 1;
    }

    printf("Old Scheduling Policy: ");
    print_policy(oldScheduling);

    // Ask user for new scheduling policy
    printf("Select New Scheduling Policy:\n");
    printf("1 - Default (SCHED_OTHER)\n");
    printf("2 - First-In-First-Out (SCHED_FIFO)\n");
    printf("3 - Round Robin (SCHED_RR)\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &policy);

    // Convert user input to valid policy
    if (policy == 1) {
        policy = SCHED_OTHER;
        priority = 0; // Priority is ignored for SCHED_OTHER
    } else if (policy == 2) {
        policy = SCHED_FIFO;
    } else if (policy == 3) {
        policy = SCHED_RR;
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    // If real-time policy is chosen, ask for priority
    if (policy == SCHED_FIFO || policy == SCHED_RR) {
        int max_priority = sched_get_priority_max(policy);
        int min_priority = sched_get_priority_min(policy);

        if (max_priority == -1 || min_priority == -1) {
            perror("Error getting priority range");
            return 1;
        }

        printf("Valid Priority Range: %d to %d\n", min_priority, max_priority);
        printf("Enter new priority: ");
        scanf("%d", &priority);

        // Validate priority input
        if (priority < min_priority || priority > max_priority) {
            printf("Invalid priority! Must be between %d and %d\n", min_priority, max_priority);
            return 1;
        }
    }

    // Modify the scheduling policy
    struct sched_param sched;
    sched.sched_priority = priority;

    if (sched_setscheduler(pid, policy, &sched) == -1) {
        perror("Error changing scheduling policy (Try running as root)");
        return 1;
    }

    // Get the new scheduling policy
    int newScheduling = sched_getscheduler(pid);
    if (newScheduling == -1) {
        perror("Error getting new scheduling policy");
        return 1;
    }

    printf("New Scheduling Policy: ");
    print_policy(newScheduling);

    return 0;
}

