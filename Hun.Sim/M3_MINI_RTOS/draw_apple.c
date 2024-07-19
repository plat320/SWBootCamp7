#include "draw_apple.h"
#include "lcd.h"

unsigned short apple_img[400] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A0, 0x10A0,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x29A2, 0x63C6, 0x9D87, 0x1080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x2081, 0x5142, 0x0000, 0x5BE5, 0xA6C9, 0xBF8A, 0x4B04, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x48E2, 0x4223, 0x6628, 0x65C7, 0x2AE3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x2041, 0x79A7, 0xA1E8, 0x9166, 0x58C3, 0x2021, 0x4A83, 0x5BA5, 0x79E4, 0x68A4, 0x4082, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3882, 0xF38F, 0xFCB3, 0xFBAF, 0xFAEC, 0xFA6A, 0xE1C8, 0xC986, 0xE147,
0xF988, 0xF9C9, 0xF167, 0xA8E5, 0x1020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0xDA8B, 0xFC72, 0xF36E, 0xF2AB, 0xF2AB,
0xF26B, 0xF22A, 0xF1E9, 0xF1C8, 0xE9A8, 0xE167, 0xD926, 0xE926, 0x98A4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x40A2, 0xFB6E,
0xF36E, 0xF26A, 0xF229, 0xF209, 0xF1E9, 0xF1E9, 0xE9C8, 0xE9A8, 0xE987, 0xE947, 0xD905, 0xD0E5, 0xD0A4, 0x2020, 0x0000, 0x0000,
0x0000, 0x0000, 0x7125, 0xFB6E, 0xF2EC, 0xF22A, 0xF209, 0xF1E9, 0xF1C9, 0xF1A8, 0xE988, 0xE967, 0xE967, 0xE947, 0xD8E5, 0xC8A4,
0xC883, 0x4821, 0x0000, 0x0000, 0x0000, 0x0000, 0x8966, 0xFB2D, 0xF28B, 0xF209, 0xF1E9, 0xF1C8, 0xF1A8, 0xE988, 0xE967, 0xE947,
0xE926, 0xE926, 0xD8E5, 0xC083, 0xC863, 0x4821, 0x0000, 0x0000, 0x0000, 0x0000, 0x8125, 0xFACC, 0xF24A, 0xF1E9, 0xF1C8, 0xE9A8,
0xE988, 0xE967, 0xE947, 0xE926, 0xE906, 0xE8E6, 0xE0C5, 0xB862, 0xC042, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x50A3, 0xFA4A,
0xEA09, 0xF1C8, 0xF1A8, 0xE988, 0xE967, 0xE947, 0xE927, 0xE906, 0xE8E6, 0xE0C5, 0xC883, 0xB842, 0xA821, 0x1000, 0x0000, 0x0000,
0x0000, 0x0000, 0x1020, 0xE1C8, 0xF1C8, 0xE9A8, 0xE167, 0xE146, 0xE126, 0xE106, 0xE0E5, 0xD8C5, 0xD0A4, 0xC863, 0xB842, 0xB821,
0x8021, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x80E4, 0xF9A8, 0xD946, 0xD926, 0xD905, 0xD0E5, 0xD0C4, 0xC8A4, 0xC883,
0xC063, 0xC042, 0xB021, 0xB021, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0xC926, 0xE126, 0xD105, 0xD0E5,
0xD0C4, 0xC8A4, 0xC883, 0xC063, 0xC042, 0xB022, 0xB001, 0x8801, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x4061, 0xE906, 0xD0E5, 0xC8C4, 0xC8A4, 0xD083, 0xC863, 0xC042, 0xB021, 0xA801, 0xA801, 0x2000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7082, 0xD0C4, 0xD0A4, 0xC883, 0xA042, 0x9842, 0xB021, 0xB001, 0xA001, 0x3000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2020, 0x3821, 0x2000, 0x0000, 0x0000, 0x2800,
0x4000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

void draw_apple(unsigned short sx, unsigned short sy, unsigned short ex, unsigned short ey, unsigned short color)
{

//	unsigned short i,j;
//	unsigned short width = ex - sx + 1;
//	unsigned short height = ey - sy + 1;
//
//	Lcd_Set_Windows(sx,sy,ex,ey);
//
//	for(i = 0; i < height; i++)
//	{
//		for(j = 0; j < width; j++)
//		{
//			Lcd_Write_Data_16Bit(color);
//		}
//	}
//
//	Lcd_Set_Windows(0, 0, lcddev.width-1, lcddev.height-1);

}

void Lcd_Draw_IMG(int xs,  int ys,  int w,  int h,  unsigned short *img)
{
	unsigned int i;
	int xe, ye;
	xe = xs+w-1;
	ye = ys+h-1;
	if(xe >= 320) xe=319;
	if(ye >= 240) xe=239;

	Lcd_Set_Windows(xs,  ys,  xe,  ye);

	Lcd_CS_EN();
	Lcd_RS_REG();

	for(i=0; i < (xe - xs + 1) * (ye - ys + 1); i++)
	{
		_SPI1_Write_Byte(*img >> 8);
		_SPI1_Write_Byte(*img & 0xFF);
		img++;
	}

	Lcd_CS_DIS();
}
