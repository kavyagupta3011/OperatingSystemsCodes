/*    Program Number: 53(c) 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will set an interval timer for 10 seconds using ITIMER_PROF.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

void alarmPrint(int);

int main() {
    time_t curtime;
    time(&curtime);
    printf("Starting time: %s", ctime(&curtime));

    struct itimerval value;
    struct itimerval ovalue;

    value.it_interval.tv_sec = 5;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 10;
    value.it_value.tv_usec = 0;

    if (setitimer(ITIMER_PROF, &value, &ovalue) < 0) {
        perror("Error in setitimer.");
        return 1;
    }

    if (signal(SIGPROF, alarmPrint) == SIG_ERR) {
        printf("\nCouldn't catch SIGPROF\n");
        return 1;
    }

    while(1) {
        // Infinite loop to keep the program alive for signal handling
    }

    return 0;
}

void alarmPrint(int signum) {
    time_t curtime;
    time(&curtime);
    printf("Current time: %s", ctime(&curtime));
}

