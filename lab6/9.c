#include<stdio.h>
#include<pthread.h>

typedef struct
{
    int value;
}ThreadArg;

void* display(void *arg){

    ThreadArg* data = (ThreadArg*)arg;
    int n = data->value;

    printf("%d",n);
    
    if (n >= 2) {
        pthread_t nextThread1;
        pthread_t nextThread2;
        ThreadArg nextArg;
        nextArg.value = n / 2;



        pthread_create(&nextThread1, NULL, display, (void*)&nextArg);

        pthread_create(&nextThread2, NULL, display, (void*)&nextArg);


        pthread_join(nextThread1, NULL);

        pthread_join(nextThread2,NULL);

    }

    // printf("%d", n);
    return NULL;

}


int main(){

    pthread_t t1;
    ThreadArg arg;
    arg.value=8;

    pthread_create(&t1,NULL,display,(void*)&arg);
    pthread_join(t1,NULL);


    return 0;
}