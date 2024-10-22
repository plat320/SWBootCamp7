	.syntax unified
	.thumb

	.text

	.align 4

	.extern current_tcb
	.extern C_Scheduler

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:
	MRS		R0, PSP
	STMDB	R0!, {R4-R11}

	LDR 	R3, =current_tcb
	LDR		R1, [R3]
	STR		R0, [R1]			@ top_of_stack update		@ context store ��

	PUSH	{R0-R4, LR}
	BL		C_Scheduler
	POP		{R0-R4, LR}

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
