#include<stdio.h>
#include<pthread.h>


typedef struct {
    int value;
} ThreadArg;


void* display(void *arg){

    ThreadArg* data = (ThreadArg*)arg;
    int n = data->value;

    // printf("%d\n",n);
    
    if (n >= 2) {
        pthread_t nextThread;
        ThreadArg nextArg;
        nextArg.value = n / 2;

        pthread_create(&nextThread, NULL, display, (void*)&nextArg);
        pthread_join(nextThread, NULL);
    }

    printf("%d\n", n);
    return NULL;

}

int main(){
    pthread_t t1;
    ThreadArg arg;
    arg.value=16;

    pthread_create(&t1,NULL,display,(void*)&arg);
    pthread_join(t1,NULL);

    return 0;
}