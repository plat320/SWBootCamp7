#include "device_driver.h"

void SysTick_OS_Tick(unsigned int msec)
{
  SysTick->CTRL = (0<<2)+(1<<1)+(0<<0);
  SysTick->LOAD = (unsigned int)((HCLK/(8.*1000.))*msec+0.5);
  SysTick->VAL = 0;
  Macro_Set_Bit(SysTick->CTRL, 0);
}
