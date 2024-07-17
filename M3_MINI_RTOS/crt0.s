	.syntax unified
	.thumb

	.text

    .extern   _HardFault_Handler
    .extern   _MemManage_Handler
    .extern   _BusFault_Handler
    .extern   _UsageFault_Handler
    .extern   SVC_Handler

	.extern   NMI_Handler
	.extern   DebugMon_Handler
	.extern   PendSV_Handler
	.extern   SysTick_Handler

	.extern   WWDG_IRQHandler
	.extern   PVD_IRQHandler
	.extern   TAMPER_IRQHandler
	.extern   RTC_IRQHandler
	.extern   FLASH_IRQHandler
	.extern   RCC_IRQHandler
	.extern   EXTI0_IRQHandler
	.extern   EXTI1_IRQHandler
	.extern   EXTI2_IRQHandler
	.extern   EXTI3_IRQHandler
	.extern   EXTI4_IRQHandler
	.extern   DMA1_Channel1_IRQHandler
	.extern   DMA1_Channel2_IRQHandler
	.extern   DMA1_Channel3_IRQHandler
	.extern   DMA1_Channel4_IRQHandler
	.extern   DMA1_Channel5_IRQHandler
	.extern   DMA1_Channel6_IRQHandler
	.extern   DMA1_Channel7_IRQHandler
	.extern   ADC1_2_IRQHandler
	.extern   USB_HP_CAN1_TX_IRQHandler
	.extern   USB_LP_CAN1_RX0_IRQHandler
	.extern   CAN1_RX1_IRQHandler
	.extern   CAN1_SCE_IRQHandler
	.extern   EXTI9_5_IRQHandler
	.extern   TIM1_BRK_IRQHandler
	.extern   TIM1_UP_IRQHandler
	.extern   TIM1_TRG_COM_IRQHandler
	.extern   TIM1_CC_IRQHandler
	.extern   TIM2_IRQHandler
	.extern   TIM3_IRQHandler
	.extern   TIM4_IRQHandler
	.extern   I2C1_EV_IRQHandler
	.extern   I2C1_ER_IRQHandler
	.extern   I2C2_EV_IRQHandler
	.extern   I2C2_ER_IRQHandler
	.extern   SPI1_IRQHandler
	.extern   SPI2_IRQHandler
	.extern   USART1_IRQHandler
	.extern   USART2_IRQHandler
	.extern   USART3_IRQHandler
	.extern   EXTI15_10_IRQHandler
	.extern   RTCAlarm_IRQHandler
	.extern   USBWakeUp_IRQHandler

	.word	  0x20005000
	.word	  __start

	.word     NMI_Handler               @ NMI Handler
	.word     _HardFault_Handler        @ Hard Fault Handler
	.word     _MemManage_Handler        @ MPU Fault Handler
	.word     _BusFault_Handler         @ Bus Fault Handler
	.word     _UsageFault_Handler       @ Usage Fault Handler
	.word     0                         @ Reserved
	.word     0                         @ Reserved
	.word     0                         @ Reserved
	.word     0                         @ Reserved
	.word     SVC_Handler				@ SVCall Handler
	.word     DebugMon_Handler          @ Debug Monitor Handler
	.word     0                         @ Reserved
	.word     PendSV_Handler            @ PendSV Handler
	.word     SysTick_Handler           @ SysTick Handler

	.word     WWDG_IRQHandler           @ Window Watchdog
	.word     PVD_IRQHandler            @ PVD through EXTI Line detect
	.word     TAMPER_IRQHandler         @ Tamper
	.word     RTC_IRQHandler            @ RTC
	.word     FLASH_IRQHandler          @ Flash
	.word     RCC_IRQHandler            @ RCC
	.word     EXTI0_IRQHandler          @ EXTI Line 0
	.word     EXTI1_IRQHandler          @ EXTI Line 1
	.word     EXTI2_IRQHandler          @ EXTI Line 2
	.word     EXTI3_IRQHandler          @ EXTI Line 3
	.word     EXTI4_IRQHandler          @ EXTI Line 4
	.word     DMA1_Channel1_IRQHandler  @ DMA1 Channel 1
	.word     DMA1_Channel2_IRQHandler  @ DMA1 Channel 2
	.word     DMA1_Channel3_IRQHandler  @ DMA1 Channel 3
	.word     DMA1_Channel4_IRQHandler  @ DMA1 Channel 4
	.word     DMA1_Channel5_IRQHandler  @ DMA1 Channel 5
	.word     DMA1_Channel6_IRQHandler  @ DMA1 Channel 6
	.word     DMA1_Channel7_IRQHandler  @ DMA1 Channel 7
	.word     ADC1_2_IRQHandler         @ ADC1 & ADC2
	.word     0  						@ USB High Priority or CAN1 TX
	.word     0 						@ USB Low  Priority or CAN1 RX0
	.word     0       					@ CAN1 RX1
	.word     0       					@ CAN1 SCE
	.word     EXTI9_5_IRQHandler        @ EXTI Line 9..5
	.word     TIM1_BRK_IRQHandler       @ TIM1 Break
	.word     TIM1_UP_IRQHandler        @ TIM1 Update
	.word     TIM1_TRG_COM_IRQHandler   @ TIM1 Trigger and Commutation
	.word     TIM1_CC_IRQHandler        @ TIM1 Capture Compare
	.word     TIM2_IRQHandler           @ TIM2
	.word     TIM3_IRQHandler           @ TIM3
	.word     TIM4_IRQHandler           @ TIM4
	.word     I2C1_EV_IRQHandler        @ I2C1 Event
	.word     I2C1_ER_IRQHandler        @ I2C1 Error
	.word     I2C2_EV_IRQHandler        @ I2C2 Event
	.word     I2C2_ER_IRQHandler        @ I2C2 Error
	.word     SPI1_IRQHandler           @ SPI1
	.word     SPI2_IRQHandler           @ SPI2
	.word     USART1_IRQHandler         @ USART1
	.word     USART2_IRQHandler         @ USART2
	.word     USART3_IRQHandler         @ USART3
	.word     EXTI15_10_IRQHandler      @ EXTI Line 15..10
	.word     RTCAlarm_IRQHandler       @ RTC Alarm through EXTI Line
	.word     USBWakeUp_IRQHandler      @ USB Wakeup from suspend

	.global	__start
  	.type 	__start, %function
__start:

	.extern __RO_LIMIT__
	.extern __RW_BASE__
	.extern __ZI_BASE__
	.extern __ZI_LIMIT__

	ldr		r0, =__RO_LIMIT__
	ldr		r1, =__RW_BASE__
	ldr		r3, =__ZI_BASE__

	cmp		r0, r1
	beq		2f

1:
	cmp		r1, r3
	ittt	lo
	ldrlo	r2, [r0], #4
	strlo	r2, [r1], #4
	blo		1b

2:
	ldr		r1, =__ZI_LIMIT__
	mov		r2, #0x0
3:
	cmp		r3, r1
	itt		lo
	strlo	r2, [r3], #4
	blo		3b

	.extern Clock_Init
	.extern System_Init
	.extern Main

	.equ RAM_END,	(0x20004FFF)
	.equ PSP_BASE,	(MSP_LIMIT)
	.equ MSP_BASE,	(RAM_END + 1)
	.equ MSP_SIZE,	(1*1024)
	.equ MSP_LIMIT,	(MSP_BASE - MSP_SIZE)

	ldr r0, =0x0
	msr control, r0

	bl 		Clock_Init
	bl		System_Init

	bl		Main
	
	b		.
			
	.end
