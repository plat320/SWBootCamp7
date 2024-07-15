#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 0); // AFIO Clock Enable
	Macro_Set_Area(RCC->APB2ENR, 0x3, 2); // PA, PB Clock Enable

	Macro_Write_Block(AFIO->MAPR, 0x7, 0x4, 24); // JTAG Pin Free

	Macro_Write_Block(GPIOB->CRL, 0xf, 0x8, 12); // B3 => input pullup
	Macro_Set_Bit(GPIOB->ODR, 3);

	Macro_Write_Block(GPIOB->CRL, 0xfff, 0x888, 20); // B5,6,7 => input pullup
	Macro_Set_Area(GPIOB->ODR, 0x7, 5);

	Macro_Write_Block(GPIOA->CRH, 0xff, 0x88, 20); // A13,14 => input pullup
	Macro_Set_Area(GPIOA->ODR, 0x3, 13);
}

int Key_Get_Pressed(void)
{
	// bit pattern : 012345 UDLR01
	int key = 0;
	key = Macro_Check_Bit_Clear(GPIOB->IDR, 3);
	key |= (Macro_Extract_Area(~GPIOB->IDR, 0x7, 5) << 1);
	key |= (Macro_Extract_Area(~GPIOA->IDR, 0x3, 13) << 4);
	return key;
}

int Key_Wait_Key_Pressed(void)
{
	int key = 0;
	while(!(key = Key_Get_Pressed()));
	return key;
}

void Key_Wait_Key_Released(void)
{
	while(Key_Get_Pressed());
}

void Key_ISR_Enable(int en)
{
    if(en)
    {
        Macro_Set_Bit(RCC->APB2ENR,3);
        Macro_Set_Bit(RCC->APB2ENR,2);
        Macro_Set_Bit(RCC->APB2ENR,0);

        Macro_Write_Block(AFIO->EXTICR[0],0xf,0x1,12);		// EXTI3 -> PORTB
        Macro_Write_Block(AFIO->EXTICR[1],0xfff,0x111,4);	// EXTI5,6,7 -> PORTB
        Macro_Write_Block(AFIO->EXTICR[3],0xff,0x00,4);		// EXTI13,14 -> PORTA

        Macro_Set_Area(EXTI->FTSR,0x3,13);
        Macro_Set_Area(EXTI->FTSR,0x7,5);
        Macro_Set_Bit(EXTI->FTSR,3);

        EXTI->PR = (0x1<<3)|(0x7<<5)|(0x3<<13);

        NVIC_ClearPendingIRQ(EXTI3_IRQn);
        NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
        NVIC_ClearPendingIRQ(EXTI15_10_IRQn);

        Macro_Set_Area(EXTI->IMR,0x7,5);
        Macro_Set_Area(EXTI->IMR,0x3,13);
        Macro_Set_Bit(EXTI->IMR,3);

        NVIC_EnableIRQ(EXTI3_IRQn);
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        NVIC_EnableIRQ(EXTI15_10_IRQn);
    }
    else
    {
    	NVIC_EnableIRQ(EXTI3_IRQn);
    	NVIC_EnableIRQ(EXTI9_5_IRQn);
    	NVIC_EnableIRQ(EXTI15_10_IRQn);
    	Macro_Clear_Bit(RCC->APB2ENR,3);
		Macro_Clear_Bit(RCC->APB2ENR,2);
		Macro_Clear_Bit(RCC->APB2ENR,0);
    }
}
