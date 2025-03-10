#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 3 

int A[SIZE][SIZE]; 
int B[SIZE][SIZE]; 
int C[SIZE][SIZE]; 


void *multiply_row(void *arg) {
    int row = *(int *)arg;
    for (int col = 0; col < SIZE; col++) {
        C[row][col] = 0;
        for (int k = 0; k < SIZE; k++) {
            C[row][col] += A[row][k] * B[k][col];
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[SIZE];
    int row_indices[SIZE];


    printf("Enter elements of Matrix A (%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B (%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            scanf("%d", &B[i][j]);

    for (int i = 0; i < SIZE; i++) {
        row_indices[i] = i;
        pthread_create(&threads[i], NULL, multiply_row, &row_indices[i]);
    }

    for (int i = 0; i < SIZE; i++)
        pthread_join(threads[i], NULL);

    printf("\nResultant Matrix C (%dx%d):\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
