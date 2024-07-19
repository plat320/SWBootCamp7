#include "mutex.h"

Mutex mutexes[MAX_MUTEX];

void initMutex(void) {
	int i;
    for (i = 0; i < MAX_MUTEX; i++) {
        mutexes[i].owner = NULL;
        mutexes[i].locked = 0;
    }
}

int createMutex(void) {
	int i;
    for (i = 0; i < MAX_MUTEX; i++) {
        if (mutexes[i].owner == NULL) {
            mutexes[i].locked = 0;
            createQueue(&mutexes[i].waiting_queue, sizeof(TCB*), MAX_TCB + 1, 0);
            return i; // Mutex ���� ����, Mutex �ε��� ��ȯ
        }
    }
    return MUTEX_FULL; // ��� Mutex�� ��� ���� ���
}

int takeMutex(int mutex_id) {
    __set_BASEPRI(0x30);

    if (mutex_id < 0 || mutex_id >= MAX_MUTEX || mutexes[mutex_id].owner == current_tcb) {
        __set_BASEPRI(0x00);
        return MUTEX_TAKE_FAIL; // ��ȿ���� ���� mutex_id
    }

    if (mutexes[mutex_id].locked == 0) {
        mutexes[mutex_id].locked = 1;
        mutexes[mutex_id].owner = current_tcb;
        __set_BASEPRI(0x00);
        return MUTEX_TAKE_SUCCESS; // Mutex ȹ�� ����
    }

    // Priority Inheritance
    if (mutexes[mutex_id].owner->prio > current_tcb->prio) {
        mutexes[mutex_id].owner->prio = current_tcb->prio;
        pq_update(&ready_queue, mutexes[mutex_id].owner, pq_compare_ready);
    }

    current_tcb->state = STATE_BLOCKED;
    enqueue(&mutexes[mutex_id].waiting_queue, &current_tcb);
    OS_Pend_Trigger();

    __set_BASEPRI(0x00);
    return MUTEX_TAKE_SUCCESS;
}

void giveMutex(int mutex_id) {
    __set_BASEPRI(0x30);

    if (mutex_id < 0 || mutex_id >= MAX_MUTEX || mutexes[mutex_id].owner != current_tcb) {
        __set_BASEPRI(0x00);
        return; // ��ȿ���� ���� mutex_id �Ǵ� Mutex�� �����ڰ� �ƴ� ���
    }

    if (!isEmpty(&mutexes[mutex_id].waiting_queue)) {
        TCB* next_tcb;
        dequeue(&mutexes[mutex_id].waiting_queue, &next_tcb, next_tcb->no_task);
        next_tcb->state = STATE_READY;
        pq_push(&ready_queue, next_tcb, pq_compare_ready);
        mutexes[mutex_id].owner = next_tcb;
    } else {
        mutexes[mutex_id].locked = 0;
        mutexes[mutex_id].owner = NULL;
    }

    current_tcb->prio = current_tcb->base_prio; // Reset priority to base priority
    pq_update(&ready_queue, current_tcb, pq_compare_ready);

    __set_BASEPRI(0x00);
}
