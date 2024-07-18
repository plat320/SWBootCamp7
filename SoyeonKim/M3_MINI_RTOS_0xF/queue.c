#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

// Function to create a new queue
Queue* createQueue(size_t data_size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->data_size = data_size;
    return q;
}

// Function to add an item to the queue
void enqueue(Queue* q, void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(q->data_size);
    memcpy(new_node->data, data, q->data_size);
    new_node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }

    q->rear->next = new_node;
    q->rear = new_node;
}

// Function to remove an item from the queue
void dequeue(Queue* q, void* data) {
    if (q->front == NULL) {
        return;
    }

    Node* temp = q->front;
    memcpy(data, temp->data, q->data_size);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp->data);
    free(temp);
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Function to free the queue
void freeQueue(Queue* q) {
    Node* current = q->front;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(q);
}
