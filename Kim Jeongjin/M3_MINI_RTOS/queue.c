#include "queue.h"
#include <string.h>

// static ������ ���� ����
char queue_buffer[QUEUE_BUFFER_SIZE] __attribute__((__aligned__(8)));

// ���� ���� �Լ�
char* _OS_Get_Buffer(int size) {
	static char* buffer_limit = queue_buffer;
	static char* pbuffer = queue_buffer + QUEUE_BUFFER_SIZE;

    size = (size + 7) & ~0x7; // 8����Ʈ ����

    if (pbuffer - size < buffer_limit) {
        return (char*)0; // �޸� ����
    }
    pbuffer -= size;

    return pbuffer;
}

// Queue ���� �Լ�
int createQueue(Queue* q, int data_size, int no_task) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    q->data_size = data_size;
    q->no_task = no_task;

    // �̸� �Ҵ�� �޸𸮷� ��� �ʱ�ȭ
    q->free_nodes = (Node*)_OS_Get_Buffer(sizeof(Node));
    if (q->free_nodes == NULL) {
        return QUEUE_FAIL_ALLOCATE;
    }

    Node* current_node = q->free_nodes;
    int i;
    for (i = 0; i < MAX_QUEUE_SIZE - 1; ++i) {
        current_node->data = _OS_Get_Buffer(data_size);
        if (current_node->data == NULL) {
            return QUEUE_FAIL_ALLOCATE;
        }
        current_node->next = (Node*)_OS_Get_Buffer(sizeof(Node));
        if (current_node->next == NULL) {
            return QUEUE_FAIL_ALLOCATE;
        }
        current_node = current_node->next;
    }
    current_node->data = _OS_Get_Buffer(data_size);
    if (current_node->data == NULL) {
        return QUEUE_FAIL_ALLOCATE;
    }
    current_node->next = NULL;

    return QUEUE_SUCCESS;
}

// Queue�� ������ �߰� �Լ�
int enqueue(Queue* q, void* data) {
    if (isFull(q)) {
        return -1;
    }

    Node* new_node = q->free_nodes;
    q->free_nodes = q->free_nodes->next;

    memcpy(new_node->data, data, q->data_size);
    new_node->next = NULL;

    if (q->rear != NULL) {
        q->rear->next = new_node;
    }
    q->rear = new_node;

    if (q->front == NULL) {
        q->front = new_node;
    }

    q->size++;
    return 0;
}

// Queue���� ������ ���� �Լ�
int dequeue(Queue* q, void* data, int no_task) {
    if (isEmpty(q)) {
        return DEQUEUE_EMPTY;
    }
    if (q->no_task != no_task) {
    	return DEQUEUE_NO_PERMISSION;
    }

    Node* temp = q->front;
    memcpy(data, temp->data, q->data_size);
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    temp->next = q->free_nodes;
    q->free_nodes = temp;

    q->size--;
    return DEQUEUE_SUCCESS;
}

// Queue�� ��� �ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q) {
    return (q->size == 0);
}

// Queue�� �� �� �ִ��� Ȯ���ϴ� �Լ�
int isFull(Queue* q) {
    return (q->size == MAX_QUEUE_SIZE);
}
