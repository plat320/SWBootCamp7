#include "priority_queue.h"
#include "device_driver.h"
#include <stdlib.h>

void pq_init(PriorityQueue* pq) {
    pq->size = 0;
}

int pq_compare_delay(TCB* a, TCB* b) {
    if (a->state == STATE_BLOCKED && b->state != STATE_BLOCKED) {
        return -1;
    }
    if (a->state != STATE_BLOCKED && b->state == STATE_BLOCKED) {
        return 1;
    }
    return a->delay_until - b->delay_until;
}

int pq_compare_ready(TCB* a, TCB* b) {
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

void pq_swap(TCB** a, TCB** b) {
    TCB* temp = *a;
    *a = *b;
    *b = temp;

    // �� �ε����� �Բ� ������Ʈ
    int temp_index = (*a)->heap_index;
    (*a)->heap_index = (*b)->heap_index;
    (*b)->heap_index = temp_index;
}

void pq_heapify_up(PriorityQueue* pq, int index, int (*compare)(TCB*, TCB*)) {
    while (index > 0 && compare(pq->heap[index], pq->heap[(index - 1) / 2]) < 0) {
        pq_swap(&pq->heap[index], &pq->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void pq_heapify_down(PriorityQueue* pq, int index, int (*compare)(TCB*, TCB*)) {
    int size = pq->size;
    while (2 * index + 1 < size) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && compare(pq->heap[left], pq->heap[smallest]) < 0) {
            smallest = left;
        }

        if (right < size && compare(pq->heap[right], pq->heap[smallest]) < 0) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        pq_swap(&pq->heap[index], &pq->heap[smallest]);
        index = smallest;
    }
}

void pq_push(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*)) {
    if (pq->size >= HEAP_SIZE) {
        return; // ť�� ���� �� ���
    }

    pq->heap[pq->size] = task;
    task->heap_index = pq->size;
    pq->size++;

    pq_heapify_up(pq, task->heap_index, compare);
}

TCB* pq_pop(PriorityQueue* pq, int (*compare)(TCB*, TCB*)) {
    if (pq->size == 0) {
        return NULL;
    }

    TCB* root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->heap[0]->heap_index = 0;
    pq->size--;

    pq_heapify_down(pq, 0, compare);

    root->heap_index = -1; // ������ ���ŵ��� ǥ��
    return root;
}

TCB* pq_top(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL;
    }
    return pq->heap[0];
}

void pq_remove(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*)) {
    if (task->heap_index < 0 || task->heap_index >= pq->size) {
        return; // ��ȿ���� ���� �ε���
    }

    int index = task->heap_index;
    pq->heap[index] = pq->heap[pq->size - 1];
    pq->heap[index]->heap_index = index;
    pq->size--;

    pq_heapify_up(pq, index, compare);
    pq_heapify_down(pq, index, compare);

    task->heap_index = -1; // ������ ���ŵ��� ǥ��
}

void pq_update(PriorityQueue* pq, TCB* task, int (*compare)(TCB*, TCB*)) {
    if (task->heap_index < 0 || task->heap_index >= pq->size) {
        return; // ��ȿ���� ���� �ε���
    }

    pq_heapify_up(pq, task->heap_index, compare);
    pq_heapify_down(pq, task->heap_index, compare);
}
