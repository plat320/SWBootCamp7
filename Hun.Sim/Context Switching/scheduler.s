	.syntax unified
	.thumb

	.text

	.align 4

	.extern current_tcb
	.extern OS_Scheduler

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:	//store
	@ 필요 시 작성
    MRS     R0, PSP
    STMDB   R0!, {R4-R11}
    LDR     R1, =current_tcb
    LDR     R2, [R1]
    STR     R0, [R2]

	push {r0-r4, lr}
    BL OS_Scheduler
    pop {r0-r4, lr}


    LDR     R1, =current_tcb
    LDR     R2, [R1]
    LDR     R0, [R2]

    LDMIA   R0!, {R4-R11}
    MSR     PSP, R0
    ORR     LR, LR, #0x0d

    BX      LR

	.global SVC_Handler
	.type 	SVC_Handler, %function
SVC_Handler:
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	LDMIA	R0!, {R4-R11}	// R4-R11 값을 stack 값에서 저장, 끝난 후 R0 == top of stack[8]
	MSR		PSP, R0			// psp 값 변경 top of stack[8] 위치	, unstacking 과정에서 스택에 있는 것들 unstacking되어 레지스터에 저장

	ORR		LR, LR, #0xd	// LR' 0xFFFFFFFD
	BX		LR

	.global _OS_Start_First_Task
	.type 	_OS_Start_First_Task, %function
_OS_Start_First_Task:
	SVC #0	// SVC handler 코드 실행
	BX LR


	.end
