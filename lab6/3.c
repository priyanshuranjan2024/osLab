#include<stdio.h>
#include<pthread.h>

void* print_numbers(void* arg) {
    int thread_id = *(int*)arg; 
    for (int i = 1; i <= 1000; i++) {
        printf("Thread %d: %d\n", thread_id, i);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    if (pthread_create(&thread1, NULL, print_numbers, &id1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_numbers, &id2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    for (int i = 1; i <= 1000; i++) {
        printf("Parent Thread: %d\n", i);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}