#include "snake.h"
#include "device_driver.h"
#include <stdlib.h>

void Snake_Init(void)
{
	int i, j;
	for (i = 0; i < GAME_OBJECT_MAP_ROW; i++)
	{
		for (j = 0; j < GAME_OBJECT_MAP_COLUMN; j++)
		{
			snake_object.object_map[i][j] = 0;
		}
	}
	snake_object.head_direction = JOY_KEY_RIGHT;
	Lcd_Draw_Border();
	snake_object.queue_no = OS_Create_Queue(sizeof(POINT), 10);
//	Uart_Printf("*** snake_object.queue_no: %d\n", snake_object.queue_no);
	POINT p1 = {4,5};
	POINT p2 = {5,5};
	POINT p3 = {6,5};
	enqueue(&queues[snake_object.queue_no], &p1);
	enqueue(&queues[snake_object.queue_no], &p2);
	enqueue(&queues[snake_object.queue_no], &p3);
	Lcd_Draw_Snake();
	Make_Target();
}

void Add_Snake_Position(POINT* p)
{
	enqueue(&queues[snake_object.queue_no], p);
	Lcd_Draw_Box(p->x * OBJECT_BLOCK_SIZE, p->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, SNAKE_COLOR);
}

void Remove_Snake_Position(void)
{
	POINT p;
	int ret = dequeue(&queues[snake_object.queue_no], &p, HAVE_PERMISSION);
	if (ret != DEQUEUE_SUCCESS)
	{
		Uart_Printf("Dequeue fail!\n");
	}
	Lcd_Draw_Box(p.x * OBJECT_BLOCK_SIZE, p.y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BACKGROUND_COLOR);
}

void Lcd_Draw_Border(void)
{
	int i;
	for (i = 0; i < GAME_WINDOW_ROW; i++)
	{
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, 0, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box(0, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, (GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
		Lcd_Draw_Box((GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BORDER_COLOR);
	}
}

void Lcd_Draw_Snake(void)
{
	Node* node = queues[snake_object.queue_no].front;
	while (node != NULL)
	{
		POINT* p = (POINT*)node->data;
		Lcd_Draw_Box(p->x * OBJECT_BLOCK_SIZE, p->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, SNAKE_COLOR);
		node = node->next;
	}
}

//void Lcd_Draw_New_Position(POINT* head_position, POINT* tail_position)
//{
////	Uart_Printf("Lcd_Draw_New_Position Start\n");
//	Lcd_Draw_Box(head_position->x * OBJECT_BLOCK_SIZE, head_position->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, SNAKE_COLOR);
//	Lcd_Draw_Box(tail_position->x * OBJECT_BLOCK_SIZE, tail_position->y * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, BACKGROUND_COLOR);
////	Uart_Printf("Lcd_Draw_New_Position End\n");
//}

void Calculate_Snake_Position(int head_direction)
{
	// TODO: ���� �ִ� ���� �ݴ� �������� ��ȯ�ϸ� ����
//	Uart_Printf("Calculate_Snake_Position Start\n");
	POINT* head_position = (POINT*)queues[snake_object.queue_no].rear->data;
	POINT new_head_position = {head_position -> x, head_position -> y};
//	POINT tail_position;
	if (head_direction == JOY_KEY_UP)
	{
		new_head_position.y -= 1;
	}
	else if (head_direction == JOY_KEY_DOWN)
	{
		new_head_position.y += 1;
	}
	else if (head_direction == JOY_KEY_LEFT)
	{
		new_head_position.x -= 1;
	}
	else if (head_direction == JOY_KEY_RIGHT)
	{
		new_head_position.x += 1;
	}
//	Uart_Printf("before enqueue\n");
//	enqueue(&queues[snake_object.queue_no], &new_head_position);
//	Uart_Printf("after enqueue\n");
//	int ret = dequeue(&queues[snake_object.queue_no], &tail_position, HAVE_PERMISSION);
//	Uart_Printf("ret: %d\n", ret);
//	Uart_Printf("after dequeue\n");

	Add_Snake_Position(&new_head_position);
	Remove_Snake_Position();
//	Lcd_Draw_New_Position(&new_head_position, &tail_position);
//	Uart_Printf("Calculate_Snake_Position End\n");
}

void Make_Target(void)
{
//	srand(time(NULL));  // ���� �ʱ�ȭ
	int rand_row, rand_column;
	rand_row = rand() % GAME_OBJECT_MAP_ROW;
	rand_column = rand() % GAME_OBJECT_MAP_COLUMN;
	Uart_Printf("rand_row: %d\n", rand_row);
	Uart_Printf("rand_column: %d\n", rand_column);
	Lcd_Draw_Box(rand_column * OBJECT_BLOCK_SIZE, rand_row * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, TARGET_COLOR);
}