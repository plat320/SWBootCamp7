	.syntax unified
	.thumb

	.text

	.align 4

	.extern current_tcb
	.extern OS_Scheduler

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:
	@ 필요 시 작성
	@ 여기서 context 저장 필요

	@ R4-R11 레지스터의 context 저장
	MRS     R0, PSP
    STMDB   R0!, {R4-R11}
    @ MSR		PSP, R0
	@ r0 tcb
	@ psp 값으로 top_of_stack (r0) 변경
    LDR		R3, =current_tcb
	LDR		R1, [R3]
	STR		R0, [R1]

	push {r0-r4, lr}
	bl OS_Scheduler
	pop {r0-r4, lr}

	@ R3 current_tcb는 current_tcb 변수의 주소
	@ R1은 current_tcb
	@ R0는 tcb
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	@ IA: increment after
	@ R0는 tcb의 top_of_stack
	@ PSP는 tcb의 스택 8번을 가리킴
	LDMIA	R0!, {R4-R11}
	MSR		PSP, R0

	@ LR에 exception return
	@ Thread mode, process stack
	@ stack에 들어감
	@ R0 para
	ORR		LR, LR, #0xd
	BX		LR

	.global SVC_Handler
	.type 	SVC_Handler, %function
SVC_Handler:
	@ current_tcb는 current_tcb 변수의 주소
	@ R1은 &tcb[0]
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	@ IA: increment after
	@ R0는 tcb의 top_of_stack
	@ PSP는 tcb의 스택 8번을 가리킴
	LDMIA	R0!, {R4-R11}
	MSR		PSP, R0

	@ LR에 exception return
	@ Thread mode, process stack
	@ stack에 들어감
	@ R0 para
	ORR		LR, LR, #0xd
	BX		LR

	.global _OS_Start_First_Task
	.type 	_OS_Start_First_Task, %function
_OS_Start_First_Task:
	@ SVC exception을 발생시키는 코드
	@ SVC exception이 발생해서 SVC_Handler가 실행되게 됨
	SVC #0
	BX LR


	.end
