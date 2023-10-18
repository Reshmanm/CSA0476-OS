#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Produce an item and add it to the buffer
        buffer[item % BUFFER_SIZE] = item;
        printf("Produced: %d\n", item);
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Consume an item from the buffer
        item = buffer[item % BUFFER_SIZE];
        printf("Consumed: %d\n", item);
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
