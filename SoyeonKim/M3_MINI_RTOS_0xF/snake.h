#ifndef SNAKE_H
#define SNAKE_H

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

//	#define STATE_READY				(0)
//	#define STATE_BLOCKED			(1)
//	#define STATE_RUNNING			(2)

	typedef struct _snake_object{
		char object_map[GAME_OBJECT_MAP_ROW][GAME_OBJECT_MAP_COLUMN];
		int queue_no;
	}SNAKE_OBJECT;

	typedef struct _point{
		int x;
		int y;
	}POINT;

	extern SNAKE_OBJECT snake_object;

	void Snake_Init(void);
	void Lcd_Draw_Border(void);

#endif // SNAKE_H
