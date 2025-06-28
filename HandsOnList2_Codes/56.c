/*    Program Number: 56 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will measure the time taken to execute 100 getppid() system calls using a time stamp counter.
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

uint64_t rdtsc()
{
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi)); // Time Stamp Counter
    return ((uint64_t)hi << 32) | lo;
}

int main()
{
    uint64_t start, end; // Change to uint64_t for 64-bit values
    start = rdtsc(); // Record start timestamp
    for (int i = 0; i < 100; i++) {
        getppid(); // Call getppid() 100 times
    }
    end = rdtsc(); // Record end timestamp

    printf("Time to execute 100 getppid(): %lu cycles\n", end - start); // Use %lu for uint64_t
    return 0;
}

