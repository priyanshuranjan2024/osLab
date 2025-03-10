#include<stdio.h>
#include<pthread.h>

typedef struct {
    int a;
    int b;
} Numbers;


void* sum_function(void* arg) {
    Numbers* nums = (Numbers*) arg; 
    int sum = nums->a + nums->b;
    printf("Sum: %d\n", sum);
    return NULL;
}

int main() {
    pthread_t thread; 
    Numbers nums = {10, 20}; 

    if (pthread_create(&thread, NULL, sum_function, &nums) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(thread,NULL);
}