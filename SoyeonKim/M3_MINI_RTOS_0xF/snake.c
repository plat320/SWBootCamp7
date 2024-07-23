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
			snake_object.object_map[i][j] = EMPTY_ID;
		}
	}
	snake_object.snake_head_dir = KEY_RIGHT;
	snake_object.score = 0;
	Lcd_Draw_Border();
	snake_object.queue_no = OS_Create_Queue(sizeof(POINT), 10);
//	Uart_Printf("*** snake_object.queue_no: %d\n", snake_object.queue_no);
	POINT p1 = {4,5};
	POINT p2 = {5,5};
	POINT p3 = {6,5};
	POINT p4 = {-1,-1};
	enqueue(&queues[snake_object.queue_no], &p1);
	enqueue(&queues[snake_object.queue_no], &p2);
	enqueue(&queues[snake_object.queue_no], &p3);
	snake_object.snake_head_pos = *((POINT*)queues[snake_object.queue_no].rear->data);
	snake_object.snake_tail_pos = p4;

	snake_object.object_map[p1.x][p1.y] = SNAKE_ID;
	snake_object.object_map[p2.x][p2.y] = SNAKE_ID;
	snake_object.object_map[p3.x][p3.y] = SNAKE_ID;

	Lcd_Draw_Snake();
	Make_Target();
}

void Add_Snake_Position(POINT* p)
{
	enqueue(&queues[snake_object.queue_no], p);
	snake_object.object_map[p->x][p->y] = SNAKE_ID;
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
	snake_object.object_map[p.x][p.y] = EMPTY_ID;
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

void Move_Snake_Position(int received_head_dir)
{
//	Uart_Printf("Move_Snake_Position Start\n");
	POINT* head_position = (POINT*)queues[snake_object.queue_no].rear->data;
	POINT new_head_position = {head_position -> x, head_position -> y};
//	POINT tail_position;

	// 기존 뱀 진행 방향의 반대 방향이 입력으로 들어오면 무시하고 그렇지 않은 경우에만 입력값으로 방향 업데이트
	if (received_head_dir * snake_object.snake_head_dir != KEY_UP * KEY_DOWN
			&& received_head_dir * snake_object.snake_head_dir != KEY_LEFT * KEY_RIGHT)
	{
		snake_object.snake_head_dir = received_head_dir;
	}

	if (snake_object.snake_head_dir == KEY_UP)
	{
		new_head_position.y -= 1;
	}
	else if (snake_object.snake_head_dir == KEY_DOWN)
	{
		new_head_position.y += 1;
	}
	else if (snake_object.snake_head_dir == KEY_LEFT)
	{
		new_head_position.x -= 1;
	}
	else if (snake_object.snake_head_dir == KEY_RIGHT)
	{
		new_head_position.x += 1;
	}
//	Uart_Printf("before enqueue\n");
//	enqueue(&queues[snake_object.queue_no], &new_head_position);
//	Uart_Printf("after enqueue\n");
//	int ret = dequeue(&queues[snake_object.queue_no], &tail_position, HAVE_PERMISSION);
//	Uart_Printf("ret: %d\n", ret);
//	Uart_Printf("after dequeue\n");

	int ret = Check_Snake_Position(new_head_position);

	if (ret == TARGET_ID)
	{
		POINT p = {-1,-1};
		snake_object.snake_head_pos = new_head_position;
		snake_object.snake_tail_pos = p;

		Add_Snake_Position(&new_head_position);
//		Remove_Snake_Position();
	}
	else if (ret == EMPTY_ID)
	{
		snake_object.snake_head_pos = new_head_position;
		snake_object.snake_tail_pos = *((POINT*)queues[snake_object.queue_no].front->data);

		Add_Snake_Position(&new_head_position);
		Remove_Snake_Position();
	}

//	snake_object.snake_head_pos = new_head_position;
//	snake_object.snake_tail_pos = *((POINT*)queues[snake_object.queue_no].front->data);
//
//	Add_Snake_Position(&new_head_position);
//	Remove_Snake_Position();

//	Lcd_Draw_New_Position(&new_head_position, &tail_position);
//	Uart_Printf("Move_Snake_Position End\n");
}

int Check_Snake_Position(POINT p)
{
	switch (snake_object.object_map[p.x][p.y])
	{
		case SNAKE_ID:
			// TODO: Game over
			return SNAKE_ID;
		case TARGET_ID:
			snake_object.score += 1;
			Uart_Printf("score: %d\n", snake_object.score);
			Make_Target();
			return TARGET_ID;
		default:
			return EMPTY_ID;
	}
}

void Make_Target(void)
{
//	srand(time(NULL));  // 난수 초기화
	int rand_row, rand_column;
	rand_row = rand() % GAME_OBJECT_MAP_ROW;
	rand_column = rand() % GAME_OBJECT_MAP_COLUMN;
	Uart_Printf("rand_row: %d\n", rand_row);
	Uart_Printf("rand_column: %d\n", rand_column);
	snake_object.object_map[rand_row][rand_column] = TARGET_ID;
	Lcd_Draw_Box(rand_column * OBJECT_BLOCK_SIZE, rand_row * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, TARGET_COLOR);
}
