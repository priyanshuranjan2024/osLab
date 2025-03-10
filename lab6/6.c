#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000

typedef struct {
    int *arr;
    int left;
    int right;
} ThreadArgs;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1)
        arr[k++] = L[i++];
    
    while (j < n2)
        arr[k++] = R[j++];
}

void *parallelMergeSort(void *args) {
    ThreadArgs *data = (ThreadArgs *)args;
    int left = data->left, right = data->right;
    int *arr = data->arr;
    
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        ThreadArgs leftArgs = {arr, left, mid};
        ThreadArgs rightArgs = {arr, mid + 1, right};
        
        pthread_t leftThread, rightThread;
        pthread_create(&leftThread, NULL, parallelMergeSort, &leftArgs);
        pthread_create(&rightThread, NULL, parallelMergeSort, &rightArgs);
        
        merge(arr, left, mid, right);
        
        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);
    }
    return NULL;
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ThreadArgs args = {arr, 0, n - 1};
    parallelMergeSort(&args);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}