// Lcd.a (Library)
// SPI1 @36MHz (PCLK2=72MHz)

#define BLACK	0x0000
#define WHITE	0xffff
#define BLUE	0x001f
#define GREEN	0x07e0
#define RED		0xf800
#define YELLOW	0xffe0
#define VIOLET	0xf81f

#define Lcd_CS  4
#define Lcd_RS  9

#define	Lcd_CS_EN()  	Macro_Clear_Bit(GPIOA->ODR, Lcd_CS);
#define	Lcd_RS_REG()	Macro_Set_Bit(GPIOB->ODR, Lcd_RS);
#define	Lcd_CS_DIS()	Macro_Set_Bit(GPIOA->ODR, Lcd_CS);

extern void Lcd_Init(void);
extern void Lcd_Set_Display_Mode(int mode);
extern void Lcd_Set_Cursor(unsigned short x, unsigned short y);
extern void Lcd_Set_Windows(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void Lcd_Put_Pixel(unsigned short x, unsigned short y, unsigned short color);
extern void Lcd_Clr_Screen(void);
extern void Lcd_Draw_Back_Color(unsigned short color);
extern void Lcd_Write_Data_16Bit(unsigned short color);
extern void Lcd_Draw_Box(int xs, int ys, int w, int h, unsigned short Color);

extern void _SPI1_Write_Byte(unsigned char data);
