	.syntax unified
	.thumb

	.text

	.align 4

	.extern current_tcb
	.extern OS_Scheduler
	.extern PRINT_DUMMY

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:
	@ 필요 시 작성
    MRS     R0, PSP
    STMDB   R0!, {R4-R11}
    LDR     R1, =current_tcb
    LDR     R2, [R1]
    STR     R0, [R2]

	push 	{r0-r4, lr}
    BL 		OS_Scheduler
    pop 	{r0-r4, lr}

    B		SVC_Handler


	.global SVC_Handler
	.type 	SVC_Handler, %function
SVC_Handler:
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	LDMIA	R0!, {R4-R11}
	MSR		PSP, R0

	ORR		LR, LR, #0xd
	BX		LR

	.global _OS_Start_First_Task
	.type 	_OS_Start_First_Task, %function
_OS_Start_First_Task:
	SVC #0
	BX LR


	.end
