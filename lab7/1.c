#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


void* display(void *arg) {
    Node* node = (Node*)arg;

    pthread_t left_thread, right_thread;

    if (node->value >= 2) {

        node->left = (Node*)malloc(sizeof(Node));
        node->left->value = node->value / 2;
        node->left->left = NULL;
        node->left->right = NULL;

        node->right = (Node*)malloc(sizeof(Node));
        node->right->value = node->value / 2;
        node->right->left = NULL;
        node->right->right = NULL;

        pthread_create(&left_thread, NULL, display, (void*)node->left);
        pthread_join(left_thread, NULL); 

        pthread_create(&right_thread, NULL, display, (void*)node->right);
        pthread_join(right_thread, NULL); 
    }

    printf("Node: %d\n", node->value);

    pthread_exit(NULL);
}

int main() {
    pthread_t t1;

    Node* root = (Node*)malloc(sizeof(Node));
    root->value = 8;
    root->left = NULL;
    root->right = NULL;

    pthread_create(&t1, NULL, display, (void*)root);
    pthread_join(t1, NULL);

    return 0;
}
