//Thread Creation 

#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Thread created successfully!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) {
        perror("Thread creation failed");
        return 1;
    }
    pthread_exit(NULL);
}


//Thread Joining

#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Thread created successfully!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    result = pthread_join(thread, NULL);
    if (result != 0) {
        perror("Thread join failed");
        return 1;
    }
    
    printf("Thread joined successfully!\n");
    return 0;
}


//Thread Equality
#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Thread created successfully!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int result1 = pthread_create(&thread1, NULL, thread_function, NULL);
    int result2 = pthread_create(&thread2, NULL, thread_function, NULL);
    
    if (result1 != 0 || result2 != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    if (pthread_equal(thread1, thread2)) {
        printf("Both threads are equal.\n");
    } else {
        printf("Threads are not equal.\n");
    }
    
    pthread_exit(NULL);
}


//Thread Exit
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("Thread created successfully!\n");
    sleep(1);
    printf("Thread is exiting.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) {
        perror("Thread creation failed");
        return 1;
    }
    
    pthread_exit(NULL);
}
