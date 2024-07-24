#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <time.h>
#include "OS.h"
#include "queue.h"
#include "lcd.h"

	#define OBJECT_BLOCK_SIZE		(20)
	#define GAME_WINDOW_HIGHT		(240)
	#define GAME_WINDOW_WIDTH		(240)
	#define GAME_WINDOW_ROW			((GAME_WINDOW_HIGHT) / (OBJECT_BLOCK_SIZE))
	#define GAME_WINDOW_COL			((GAME_WINDOW_WIDTH) / (OBJECT_BLOCK_SIZE))
//	#define GAME_OBJECT_MAP_ROW		((GAME_WINDOW_ROW) - 2)
//	#define GAME_OBJECT_MAP_COLUMN	((GAME_WINDOW_COL) - 2)

	#define SNAKE_MAX_LENGTH		(100)

	#define KEY_UP					(1)
	#define KEY_DOWN				(2)
	#define KEY_LEFT				(3)
	#define KEY_RIGHT				(4)

	#define EMPTY_ID				(0)
	#define SNAKE_ID				(1)
	#define TARGET_ID				(2)
	#define BORDER_ID				(3)

	#define BACKGROUND_COLOR		(0x0000)
	#define BORDER_COLOR			(0xffff)
//	#define SNAKE_COLOR				(0x07e0)
	#define SNAKE_COLOR				(0x0000)
	#define TARGET_COLOR			(0xf800)

//	#define STATE_READY				(0)
//	#define STATE_BLOCKED			(1)
//	#define STATE_RUNNING			(2)

	typedef struct _snake_object{
		// TODO: 머리 위치도 여기서 바로 접근 가능하게 변수 만들기, 뱀의 head, tail 변수 (포인터)
		char object_map[GAME_WINDOW_ROW][GAME_WINDOW_COL];
		int snake_head_dir;
		int snake_head_dir_pre;
		int queue_no;
		int score;
		POINT snake_head_pos;
		POINT snake_tail_pos;
		POINT snake_target_pos;
	}SNAKE_OBJECT;

	// queue.h로 이동
//	typedef struct _point{
//		int x;
//		int y;
//	}POINT;

	extern SNAKE_OBJECT snake_object;
	extern const unsigned short apple_img[];
	extern const unsigned short grass_img[];
	extern const unsigned short snake_head_img[];
//	extern const unsigned short big_apple_img[];

	void Snake_Init(void);
	void Add_Snake_Position(POINT*);
	void Remove_Snake_Position(void);
//	void Calculate_Snake_Position(int);
	void Make_Target(void);
	int Check_Snake_Position(POINT);
	void Move_Snake_Position(int);

	// draw function
	void draw_init(void);
	void Lcd_Draw_Border(void);
	void Lcd_Draw_Snake(void);
	void Lcd_Draw_Grass(void);
	void Lcd_Draw_IMG(int xs,  int ys,  int w,  int h,  const unsigned short *img);
	void rotate_image_array(const unsigned short* image_array, unsigned short *temp, int direction);

#endif // SNAKE_H
