#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <time.h>
#include "OS.h"
#include "queue.h"

	#define OBJECT_BLOCK_SIZE		(20)
	#define GAME_WINDOW_HIGHT		(240)
	#define GAME_WINDOW_WIDTH		(240)
	#define GAME_WINDOW_ROW			((GAME_WINDOW_HIGHT) / (OBJECT_BLOCK_SIZE))
	#define GAME_WINDOW_COLUMN		((GAME_WINDOW_WIDTH) / (OBJECT_BLOCK_SIZE))
	#define GAME_OBJECT_MAP_ROW		((GAME_WINDOW_ROW) - 2)
	#define GAME_OBJECT_MAP_COLUMN	((GAME_WINDOW_COLUMN) - 2)

	#define JOY_KEY_UP				(1)
	#define JOY_KEY_DOWN			(2)
	#define JOY_KEY_LEFT			(3)
	#define JOY_KEY_RIGHT			(4)

	#define BACKGROUND_COLOR		(0x0000)
	#define BORDER_COLOR			(0xffff)
	#define SNAKE_COLOR				(0x07e0)
	#define TARGET_COLOR			(0xf800)

//	#define STATE_READY				(0)
//	#define STATE_BLOCKED			(1)
//	#define STATE_RUNNING			(2)

	typedef struct _snake_object{
		// TODO: 머리 위치도 여기서 바로 접근 가능하게 변수 만들기, 뱀의 head, tail 변수 (포인터)
		char object_map[GAME_OBJECT_MAP_ROW][GAME_OBJECT_MAP_COLUMN];
		int head_direction;
		int queue_no;
	}SNAKE_OBJECT;

	// queue.h로 이동
//	typedef struct _point{
//		int x;
//		int y;
//	}POINT;

	extern SNAKE_OBJECT snake_object;

	void Snake_Init(void);
	void Add_Snake_Position(POINT*);
	void Remove_Snake_Position(void);
	void Lcd_Draw_Border(void);
	void Lcd_Draw_Snake(void);
//	void Lcd_Draw_New_Position(POINT* head_position, POINT* tail_position);
	void Calculate_Snake_Position(int);
	void Make_Target(void);

#endif // SNAKE_H
