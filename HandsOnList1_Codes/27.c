/*    Program Number: 27  
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  04-04-2025  
Description: This program retrieves the maximum and minimum real-time priority.  
*/  

#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main() {
    int max_priority = sched_get_priority_max(SCHED_FIFO);
    int min_priority = sched_get_priority_min(SCHED_FIFO);

    if (max_priority == -1 || min_priority == -1) {
        perror("Error retrieving priority limits");
        return 1;
    }

    printf("Max Priority: %d\n", max_priority);
    printf("Min Priority: %d\n", min_priority);

    return 0;
}
