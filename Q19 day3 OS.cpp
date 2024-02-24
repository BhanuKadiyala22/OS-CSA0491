#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

int counter = 0;
pthread_mutex_t mutex;

void *thread_function(void *arg) {
    int tid = *((int *)arg);
    pthread_mutex_lock(&mutex); // Lock the mutex
    counter++; // Critical section
    printf("Thread %d: Counter value: %d\n", tid, counter);
    pthread_mutex_unlock(&mutex); // Unlock the mutex
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_args[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
