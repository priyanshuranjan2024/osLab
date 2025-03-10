#include <stdio.h>
#include <pthread.h>

int a = 0;  

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        a++;  
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;


    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    printf("Final value of a: %d\n", a);

    return 0;
}
