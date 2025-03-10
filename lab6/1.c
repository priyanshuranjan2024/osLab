#include <stdio.h>
#include <pthread.h>

void* display_name(void* arg) {
    printf("Priyanshu Ranjan\n");
    return NULL;
}

int main() {
    pthread_t thread; 


    if (pthread_create(&thread, NULL, display_name, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(thread, NULL);

    return 0;
}