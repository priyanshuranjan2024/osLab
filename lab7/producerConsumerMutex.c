#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define PRODUCERS 10
#define CONSUMERS 20

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

int produce_item(){
    return rand()%1000;
}

void insert_item(int item) {
    buffer[count++] = item;
}

int remove_item() {
    return buffer[--count];
}

void* producer(void* arg) {
    while (1) {
        int item = produce_item();
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        insert_item(item);
        printf("Producer %ld produced: %d (buffer count: %d)\n", (long)arg, item, count);

        pthread_cond_signal(&not_empty); 
        pthread_mutex_unlock(&mutex);

        usleep(100000); 
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = remove_item();
        printf("Consumer %ld consumed: %d (buffer count: %d)\n", (long)arg, item, count);

        pthread_cond_signal(&not_full); 
        pthread_mutex_unlock(&mutex);

        usleep(150000); 
    }
    return NULL;
}

int main() {
    pthread_t prod_threads[PRODUCERS];
    pthread_t cons_threads[CONSUMERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // Create producer threads
    for (long i = 0; i < PRODUCERS; i++) {
        pthread_create(&prod_threads[i], NULL, producer, (void*)i);
    }

    // Create consumer threads
    for (long i = 0; i < CONSUMERS; i++) {
        pthread_create(&cons_threads[i], NULL, consumer, (void*)i);
    }

    // Join threads (infinite loop, so practically they will run forever)
    for (int i = 0; i < PRODUCERS; i++) {
        pthread_join(prod_threads[i], NULL);
    }

    for (int i = 0; i < CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}