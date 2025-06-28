/*    Program Number: 50 
Student Name:  Kavya Gupta; Register Number: IMT2023016  
Date:  12-05-2025 
Description: This program will intentionally induce a deadlock scenario using semaphores.
*/


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore1, semaphore2;

void* thread1(void* arg) {
    printf("T1 : Attempting to acquire semaphore 1\n");
    sem_wait(&semaphore1);
    printf("T1: Acquired semaphore 1\n");
    sleep(1);
    printf("T1: Attempting to acquire semaphore 2\n");
    sem_wait(&semaphore2);
    printf("T1: Acquired semaphore 2\n");
    for(int i = 0; i < 100000000; i++)
    sem_post(&semaphore1);
    sem_post(&semaphore2);
    return NULL;
}

void* thread2(void* arg) {
    printf("T2: Attempting to acquire semaphore 2\n");
    sem_wait(&semaphore2);
    printf("T2: Acquired semaphore 2\n");
    sleep(1);
    printf("T2: Attempting to acquire semaphore 1\n");
    sem_wait(&semaphore1);
    printf("T2: Acquired semaphore 1\n");
    for(int i = 0; i < 100000000; i++)
    sem_post(&semaphore1);
    sem_post(&semaphore2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_init(&semaphore1, 0, 1);
    sem_init(&semaphore2, 0, 1);
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    return 0;
}
