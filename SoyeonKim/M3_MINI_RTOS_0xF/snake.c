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
	Lcd_Draw_Border();
	snake_object.queue_no = OS_Create_Queue(sizeof(POINT), 50);
	POINT p1 = {4,5};
	POINT p2 = {5,5};
	enqueue(&queues[snake_object.queue_no], &p1);
	enqueue(&queues[snake_object.queue_no], &p2);
}

void Lcd_Draw_Border(void)
{
	int i;
	// 정사각형이 아니라면 이 부분 수정 필요 (GAME_WINDOW_ROW != GAME_WINDOW_COLUMN 인 경우)
	for (i = 0; i < GAME_WINDOW_ROW; i++)
	{
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, 0, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, 0xffff);
		Lcd_Draw_Box(0, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, 0xffff);
		Lcd_Draw_Box(i * OBJECT_BLOCK_SIZE, (GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, 0xffff);
		Lcd_Draw_Box((GAME_WINDOW_ROW - 1) * OBJECT_BLOCK_SIZE, i * OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, OBJECT_BLOCK_SIZE, 0xffff);
	}
}

void Calculate_Snake_Position(int received_data)
{
	POINT* head_position = (POINT*)queues[snake_object.queue_no].rear->data;
	POINT new_position = {head_position -> x, head_position -> y};
	void* tail_position;
	if (received_data == JOY_KEY_UP)
	{
		new_position.y -= 1;
	}
	else if (received_data == JOY_KEY_DOWN)
	{
		new_position.y += 1;
	}
	else if (received_data == JOY_KEY_LEFT)
	{
		new_position.x -= 1;
	}
	else if (received_data == JOY_KEY_RIGHT)
	{
		new_position.x += 1;
	}
	enqueue(&queues[snake_object.queue_no], &new_position);
	int ret = dequeue(&queues[snake_object.queue_no], tail_position, HAVE_PERMISSION);
}
