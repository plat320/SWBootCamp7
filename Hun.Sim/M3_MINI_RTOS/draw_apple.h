/*
 * draw_apple.h
 *
 *  Created on: 2024. 7. 19.
 *      Author: hun.sim
 */

#ifndef DRAW_APPLE_H_
#define DRAW_APPLE_H_


#include "device_driver.h"
#include "lcd.h"
#include "OS.h"
#include "queue.h"


void draw_apple(unsigned short sx, unsigned short sy, unsigned short ex, unsigned short ey, unsigned short color);
void Lcd_Draw_IMG(int xs,  int ys,  int w,  int h,  unsigned short *img);



#endif /* DRAW_APPLE_H_ */
