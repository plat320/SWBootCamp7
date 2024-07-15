#include "device_driver.h"

#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)
#define TIM4_MAX	  		(0xffffu)

void TIM4_Repeat_Interrupt_Enable(int en, int time)
{
    if(en)
    {
        Macro_Set_Bit(RCC->APB1ENR, 2);

        TIM4->CR1 = (1<<4)|(0<<3);
        TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
        TIM4->ARR = TIME4_PLS_OF_1ms * time - 1;
        Macro_Set_Bit(TIM4->EGR,0);

        // TIM4->SR 레지스터에서 Timer Pending Clear
        Macro_Clear_Bit(TIM4->SR, 0);

        // NVIC에서 30번 인터럽트 Pending Clear => NVIC용 Macro 사용
        NVIC_ClearPendingIRQ(TIM4_IRQn);

        // TIM4->DIER 레지스터에서 Timer 인터럽트 허용
        Macro_Set_Bit(TIM4->DIER, 0);

        // NVIC에서 30번 인터럽트를 허용으로 설정 => NVIC용 Macro 사용
        NVIC_EnableIRQ(TIM4_IRQn);

        // TIM4 Start
        Macro_Set_Bit(TIM4->CR1, 0);
    }

    else
    {
        NVIC_DisableIRQ(30);
        Macro_Clear_Bit(TIM4->CR1, 0);
        Macro_Clear_Bit(TIM4->DIER, 0);
    }
}
