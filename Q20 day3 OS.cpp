#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Shared variables
int shared_data = 0;
int readers_count = 0;

// Semaphores
sem_t mutex, wrt;

void *reader(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&mutex); // Lock the mutex to update readers_count
        readers_count++;
        if (readers_count == 1) // First reader, lock the write semaphore
            sem_wait(&wrt);
        sem_post(&mutex); // Release the mutex

        // Reading shared data
        printf("Reader %d reads: %d\n", id, shared_data);
        usleep(rand() % 1000000); // Sleep for random time

        sem_wait(&mutex); // Lock the mutex to update readers_count
        readers_count--;
        if (readers_count == 0) // Last reader, release the write semaphore
            sem_post(&wrt);
        sem_post(&mutex); // Release the mutex

        usleep(rand() % 1000000); // Sleep for random time
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&wrt); // Lock the write semaphore

        // Writing shared data
        shared_data++;
        printf("Writer %d writes: %d\n", id, shared_data);
        usleep(rand() % 1000000); // Sleep for random time

        sem_post(&wrt); // Release the write semaphore
        usleep(rand() % 1000000); // Sleep for random time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_args[NUM_READERS], writer_args[NUM_WRITERS];

    sem_init(&mutex, 0, 1); // Initialize the mutex semaphore
    sem_init(&wrt, 0, 1); // Initialize the write semaphore

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_args[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_args[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_args[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void *)&writer_args[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex); // Destroy the mutex semaphore
    sem_destroy(&wrt); // Destroy the write semaphore

    return 0;
}
