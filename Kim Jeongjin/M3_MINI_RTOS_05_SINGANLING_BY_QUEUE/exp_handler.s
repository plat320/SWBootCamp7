	.syntax unified
	.thumb

	.text

    .global __get_IPSR
  	.type 	__get_IPSR, %function
__get_IPSR:
	MRS		r0, IPSR
	BX		lr

    .extern	Uart1_Printf

    .global _Print_Reg
  	.type 	_Print_Reg, %function
_Print_Reg:
    PUSH	{r0-r12,lr}
    MRS     r1, PSR
    PUSH    {r0, r1}

    MOV     r6, #14
    MOV     r4, #4
    LDR     r5, =_PSR
_loop:
    LDR     r0, =fmt
    MOV     r1, r5
    LDR     r2, [sp, r4]
    BL      Uart1_Printf

    ADD     r4, r4, #4
    ADD     r5, r5, #4
    SUBS    r6, r6, #1
    BGT     _loop

    LDR     r0, =fmt
    MOV     r1, r5
    MRS     r2, psp
    BL      Uart1_Printf

    POP     {r0, r1}
	MSR     APSR_nzcvq, r1
	MSR     IEPSR, r1
    POP		{r0-r12, pc}

fmt:	.string "%s : 0x%.8X\n"
_PSR:   .string "PSR"
_r0:    .string "R00"
_r1:    .string "R01"
_r2:    .string "R02"
_r3:    .string "R03"
_r4:    .string "R04"
_r5:    .string "R05"
_r6:    .string "R06"
_r7:    .string "R07"
_r8:    .string "R08"
_r9:    .string "R09"
_r10:   .string "R10"
_r11:   .string "R11"
_r12:   .string "R12"
_PSP:   .string "PSP"

	.align 2

    .extern  MemManage_Handler
    .extern  BusFault_Handler
    .extern	 UsageFault_Handler
    .extern  HardFault_Handler

    .global _HardFault_Handler
  	.type 	_HardFault_Handler, %function
_HardFault_Handler:

	PUSH	{r0, lr}
	BL    	_Print_Reg
	ADD   	r0, sp, #8
	LDR   	r1, [sp, #4]
	MRS   	r2, psp
	BL    	HardFault_Handler
	POP	 	{r0, pc}

    .global _MemManage_Handler
  	.type 	_MemManage_Handler, %function
_MemManage_Handler:

	PUSH	{r0, lr}
	BL    	_Print_Reg
	ADD   	r0, sp, #8
	LDR   	r1, [sp, #4]
	MRS   	r2, psp
	BL    	MemManage_Handler
	POP	 	{r0, pc}

    .global _BusFault_Handler
  	.type 	_BusFault_Handler, %function
_BusFault_Handler:

	PUSH	{r0, lr}
	BL    	_Print_Reg
	ADD   	r0, sp, #8
	LDR   	r1, [sp, #4]
	MRS   	r2, psp
	BL    	BusFault_Handler
	POP	 	{r0, pc}

    .global _UsageFault_Handler
  	.type 	_UsageFault_Handler, %function
_UsageFault_Handler:

	PUSH	{r0, lr}
	BL    	_Print_Reg
	ADD   	r0, sp, #8
	LDR   	r1, [sp, #4]
	MRS   	r2, psp
	BL    	UsageFault_Handler
	POP	 	{r0, pc}

 	.end
