#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Thread-safe Linked List structure
typedef struct {
    Node* head;
    pthread_mutex_t lock;
} ThreadSafeLinkedList;

// Initialize the linked list
void initList(ThreadSafeLinkedList* list) {
    list->head = NULL;
    pthread_mutex_init(&list->lock, NULL);
}

// Insert at the beginning (Thread-safe)
void insert(ThreadSafeLinkedList* list, int value) {
    pthread_mutex_lock(&list->lock); // Lock before modification

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        pthread_mutex_unlock(&list->lock);
        return;
    }
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;

    pthread_mutex_unlock(&list->lock); // Unlock after modification
}

// Delete a node by value (Thread-safe)
void deleteNode(ThreadSafeLinkedList* list, int value) {
    pthread_mutex_lock(&list->lock);

    Node *current = list->head, *prev = NULL;

    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value %d not found\n", value);
        pthread_mutex_unlock(&list->lock);
        return;
    }

    if (prev == NULL) {
        list->head = current->next; // Removing head node
    } else {
        prev->next = current->next;
    }
    
    free(current);
    pthread_mutex_unlock(&list->lock);
}

// Print the list (Thread-safe)
void printList(ThreadSafeLinkedList* list) {
    pthread_mutex_lock(&list->lock);

    Node* current = list->head;
    printf("Linked List: ");
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    pthread_mutex_unlock(&list->lock);
}

// Thread function to insert values
void* insertThread(void* arg) {
    ThreadSafeLinkedList* list = (ThreadSafeLinkedList*)arg;
    for (int i = 1; i <= 5; i++) {
        insert(list, i);
        printf("Inserted: %d\n", i);
    }
    return NULL;
}

// Thread function to delete values
void* deleteThread(void* arg) {
    ThreadSafeLinkedList* list = (ThreadSafeLinkedList*)arg;
    for (int i = 1; i <= 3; i++) {
        deleteNode(list, i);
        printf("Deleted: %d\n", i);
    }
    return NULL;
}

// Main function
int main() {
    ThreadSafeLinkedList list;
    initList(&list);

    pthread_t t1, t2;

    pthread_create(&t1, NULL, insertThread, &list);
    pthread_create(&t2, NULL, deleteThread, &list);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printList(&list);

    pthread_mutex_destroy(&list.lock);
    return 0;
}
