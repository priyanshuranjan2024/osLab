#include <stdio.h>
#include <pthread.h>

#define SIZE 10  
int arr[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  
int g[2] = {0};  

void* compute_sum(void* arg) {
    int index = *(int*)arg;  
    int start = (index == 0) ? 0 : SIZE / 2;  
    int end = (index == 0) ? SIZE / 2 : SIZE; 

    for (int i = start; i < end; i++) {
        g[index] += arr[i];  
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int idx1 = 0, idx2 = 1;

    pthread_create(&t1, NULL, compute_sum, &idx1);
    pthread_create(&t2, NULL, compute_sum, &idx2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    int total_sum = g[0] + g[1];

    printf("Partial sum by Thread 1: %d\n", g[0]);
    printf("Partial sum by Thread 2: %d\n", g[1]);
    printf("Total Sum by Parent: %d\n", total_sum);

    return 0;
}
