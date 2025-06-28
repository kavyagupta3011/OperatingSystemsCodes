/*    Program Number: 58 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will create three threads and print the IDs of the created threads.
*/

#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    printf("Thread ID : %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];  // Array to store thread IDs

    // Create 3 threads
    for(int i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    // Wait for all threads to finish
    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

