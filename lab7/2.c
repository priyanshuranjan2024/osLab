// #include <stdio.h>
// #include <pthread.h>

// int a = 1000; 
// pthread_mutex_t lock;

// void* t1_task(void* arg) {

//         pthread_mutex_lock(&lock);
//         a -= 100;
//         pthread_mutex_unlock(&lock);
//     return NULL;
// }

// void* t2_task(void* arg) {
//         pthread_mutex_lock(&lock);
//         a -= 200;
//         pthread_mutex_unlock(&lock);
//     return NULL;
// }

// int main() {
//     pthread_t t1, t2;
//     pthread_mutex_init(&lock, NULL);

//     pthread_create(&t1, NULL, t1_task, NULL);
//     pthread_create(&t2, NULL, t2_task, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     pthread_mutex_destroy(&lock);

//     printf("Final value of a (with mutex): %d\n", a);
//     return 0;
// }


//now using semaphore

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a = 1000; // Global variable
sem_t sem;

void* t1_task(void* arg) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(&sem); // Acquire semaphore
        a -= 100;
        sem_post(&sem); // Release semaphore
    }
    return NULL;
}

void* t2_task(void* arg) {
    for (int i = 0; i < 1000; i++) {
        sem_wait(&sem); // Acquire semaphore
        a -= 200;
        sem_post(&sem); // Release semaphore
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    // Initialize the semaphore with a value of 1 (binary semaphore)
    sem_init(&sem, 0, 1);

    pthread_create(&t1, NULL, t1_task, NULL);
    pthread_create(&t2, NULL, t2_task, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the semaphore
    sem_destroy(&sem);

    printf("Final value of a (with semaphore): %d\n", a);
    return 0;
}
