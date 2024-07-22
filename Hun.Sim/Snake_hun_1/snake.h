/*
 * draw_apple.h
 *
 *  Created on: 2024. 7. 19.
 *      Author: hun.sim
 */

#ifndef SNAKE_H_
#define SNAKE_H_


#include "device_driver.h"
#include "lcd.h"
#include "OS.h"
#include "queue.h"

#define OBJECT_BLOCK_SIZE		(20)
#define GAME_WINDOW_HIGHT		(240)
#define GAME_WINDOW_WIDTH		(240)
#define GAME_WINDOW_ROW			((GAME_WINDOW_HIGHT) / (OBJECT_BLOCK_SIZE))
#define GAME_WINDOW_COLUMN		((GAME_WINDOW_WIDTH) / (OBJECT_BLOCK_SIZE))
#define GAME_OBJECT_MAP_ROW		((GAME_WINDOW_ROW) - 2)
#define GAME_OBJECT_MAP_COLUMN	((GAME_WINDOW_COLUMN) - 2)


int snake_game();
void logic();
void input();
void draw();
void setup();
void draw_init();
void Lcd_Draw_IMG(int xs,  int ys,  int w,  int h,  unsigned short *img);



#endif /* SNAKE_H_ */
