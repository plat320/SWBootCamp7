#include "priority_queue.h"
#include "device_driver.h"
#include <stdlib.h>

void pq_init(PriorityQueue* pq) {
    pq->size = 0;
}

void pq_swap(TCB** a, TCB** b) {
    TCB* temp = *a;
    *a = *b;
    *b = temp;
}

int pq_compare(TCB* a, TCB* b) {
    if (a->state == STATE_READY && b->state != STATE_READY) {
        return -1;
    }
    if (a->state != STATE_READY && b->state == STATE_READY) {
        return 1;
    }
    if (a->prio != b->prio) {
        return a->prio - b->prio;
    }
    return a->timestamp - b->timestamp;
}

void pq_push(PriorityQueue* pq, TCB* task) {
    if (pq->size >= PQ_SIZE) {
        return; // Heap is full
    }

    pq->heap[pq->size] = task;
    int i = pq->size;
    pq->size++;

    while (i != 0 && pq_compare(pq->heap[i], pq->heap[(i - 1) / 2]) < 0) {
        pq_swap(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

TCB* pq_pop(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL; // Heap is empty
    }

    TCB* root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    //Uart_Printf("root->no_task : %d\n", root->no_task);

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < pq->size && pq_compare(pq->heap[left], pq->heap[smallest]) < 0) {
            smallest = left;
        }

        if (right < pq->size && pq_compare(pq->heap[right], pq->heap[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == i) {
            break;
        }

        pq_swap(&pq->heap[i], &pq->heap[smallest]);
        i = smallest;
    }

    return root;
}

TCB* pq_top(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL; // Heap is empty
    }

    TCB* root = pq->heap[0];
    //Uart_Printf("root->no_task : %d\n", root->no_task);
    //Uart_Printf("root->state : %d\n", root->state);
    return root;
}
