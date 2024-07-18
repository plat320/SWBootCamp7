#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

// Node structure
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
    size_t data_size;  // Size of each data element
} Queue;

// Queue functions
Queue* createQueue(size_t data_size);
void enqueue(Queue* q, void* data);
void dequeue(Queue* q, void* data);
int isEmpty(Queue* q);
void freeQueue(Queue* q);

#endif
