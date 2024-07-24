#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

// ������ �ִ� ũ�� ����
//#define MAX_QUEUE_SIZE          (10)
#define MAX_QUEUE_SIZE          (5)
//#define QUEUE_BUFFER_SIZE       (4 * 1024)
#define QUEUE_BUFFER_SIZE       (5 * 1024)

// Queue ���� ����
#define QUEUE_SUCCESS           (0)
#define QUEUE_FAIL_ALLOCATE     (-1)

// DEQUEUE ���� ����
#define DEQUEUE_SUCCESS				(0)
#define DEQUEUE_NO_PERMISSION		(-2)
#define DEQUEUE_EMPTY				(-3)

#define HAVE_PERMISSION			(-1)

// ��� ����ü ����
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Queue ����ü ����
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;      // ���� Queue�� �ִ� ����� ��
    int max_size;  // ���� Queue�� ������ �� �ִ� ��� ���� �ִ�
    int data_size; // ������ ũ��
    Node* free_nodes; // �̸� �Ҵ�� ������ ����Ʈ
    int no_task; // Queue ������ task�� no
} Queue;

// �ӽ�
typedef struct _point{
	int x;
	int y;
}POINT;

// �Լ� ����
char* _OS_Get_Buffer(int size);
int createQueue(Queue* q, int data_size, int number_of_elements, int no_task);
int enqueue(Queue* q, const void* data);
int dequeue(Queue* q, void* data, int no_task);
int isEmpty(Queue* q);
int isFull(Queue* q);

// ���� ���� �Լ�
void queue_init(void);

#endif // QUEUE_H
