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

    // 힙 인덱스도 함께 업데이트
    int temp_index = (*a)->heap_index;
    (*a)->heap_index = (*b)->heap_index;
    (*b)->heap_index = temp_index;
}

void pq_heapify_up(PriorityQueue* pq, int index) {
    while (index > 0 && pq_compare(pq->heap[index], pq->heap[(index - 1) / 2]) < 0) {
        pq_swap(&pq->heap[index], &pq->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void pq_heapify_down(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (2 * index + 1 < size) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && pq_compare(pq->heap[left], pq->heap[smallest]) < 0) {
            smallest = left;
        }

        if (right < size && pq_compare(pq->heap[right], pq->heap[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        pq_swap(&pq->heap[index], &pq->heap[smallest]);
        index = smallest;
    }
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
    if (pq->size >= HEAP_SIZE) {
        return; // 큐가 가득 찬 경우
    }

    pq->heap[pq->size] = task;
    task->heap_index = pq->size;
    pq->size++;

    pq_heapify_up(pq, task->heap_index);
}

TCB* pq_pop(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL;
    }

    TCB* root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->heap[0]->heap_index = 0;
    pq->size--;

    pq_heapify_down(pq, 0);

    root->heap_index = -1; // 힙에서 제거됨을 표시
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

void pq_remove(PriorityQueue* pq, TCB* task) {
    if (task->heap_index < 0 || task->heap_index >= pq->size) {
        return; // 유효하지 않은 인덱스
    }

    int index = task->heap_index;
    pq->heap[index] = pq->heap[pq->size - 1];
    pq->heap[index]->heap_index = index;
    pq->size--;

    pq_heapify_up(pq, index);
    pq_heapify_down(pq, index);

    task->heap_index = -1; // 힙에서 제거됨을 표시
}

void pq_update(PriorityQueue* pq, TCB* task) {
    if (task->heap_index < 0 || task->heap_index >= pq->size) {
        return; // 유효하지 않은 인덱스
    }

    pq_heapify_up(pq, task->heap_index);
    pq_heapify_down(pq, task->heap_index);
}
