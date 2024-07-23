#include "device_driver.h"

#define TIM3_FREQ           (8000000)           // Hz
#define TIM3_TICK           (1000000/TIM3_FREQ) // usec
#define TIME3_PLS_OF_1ms    (1000/TIM3_TICK)
 
void TIM3_Out_Init(void)
{
    Macro_Set_Bit(RCC->APB1ENR, 1);
    Macro_Set_Bit(RCC->APB2ENR, 3);
    Macro_Write_Block(GPIOB->CRL,0xf,0xb,0);
    Macro_Write_Block(TIM3->CCMR2,0x7,0x6,4);
    TIM3->CCER = (0<<9)|(1<<8);
}
 
void TIM3_Out_Freq_Generation(unsigned short freq)
{
    TIM3->PSC = (unsigned int)(TIMXCLK/(double)TIM3_FREQ + 0.5)-1;
    TIM3->ARR = (double)TIM3_FREQ/freq-1;
    TIM3->CCR3 = TIM3->ARR/2;
 
    Macro_Set_Bit(TIM3->EGR,0);
    TIM3->CR1 = (1<<4)|(0<<3)|(0<<1)|(1<<0);
}
 
void TIM3_Out_Stop(void)
{
    Macro_Clear_Bit(TIM3->CR1, 0);
    Macro_Clear_Bit(TIM3->DIER, 0);
}