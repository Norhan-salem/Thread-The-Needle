#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4
#define INCREMENT_AMOUNT 100000

int shared_counter = 0;

void *increment_counter(void *arg) {
    for (int i = 0; i < INCREMENT_AMOUNT; i++) {
        int temp = shared_counter;
        usleep(1); // Add a small delay to increase the chance of a context switch
        shared_counter = temp + 1; // Critical section: Incrementing the shared counter
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d (Expected: %d)\n", shared_counter, NUM_THREADS * INCREMENT_AMOUNT);
    return 0;
}

