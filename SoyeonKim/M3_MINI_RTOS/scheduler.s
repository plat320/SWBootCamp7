	.syntax unified
	.thumb

	.text

	.align 4

	.extern current_tcb
	.extern OS_Scheduler

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:
	@ �ʿ� �� �ۼ�
	@ ���⼭ context ���� �ʿ�

	@ R4-R11 ���������� context ����
	MRS     R0, PSP
    STMDB   R0!, {R4-R11}
    @ MSR		PSP, R0
	@ r0 tcb
	@ psp ������ top_of_stack (r0) ����
    LDR		R3, =current_tcb
	LDR		R1, [R3]
	STR		R0, [R1]

	push {r0-r4, lr}
	bl OS_Scheduler
	pop {r0-r4, lr}

	@ R3 current_tcb�� current_tcb ������ �ּ�
	@ R1�� current_tcb
	@ R0�� tcb
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	@ IA: increment after
	@ R0�� tcb�� top_of_stack
	@ PSP�� tcb�� ���� 8���� ����Ŵ
	LDMIA	R0!, {R4-R11}
	MSR		PSP, R0

	@ LR�� exception return
	@ Thread mode, process stack
	@ stack�� ��
	@ R0 para
	ORR		LR, LR, #0xd
	BX		LR

	.global SVC_Handler
	.type 	SVC_Handler, %function
SVC_Handler:
	@ current_tcb�� current_tcb ������ �ּ�
	@ R1�� &tcb[0]
	LDR		R3, =current_tcb
	LDR		R1, [R3]
	LDR		R0, [R1]
	@ IA: increment after
	@ R0�� tcb�� top_of_stack
	@ PSP�� tcb�� ���� 8���� ����Ŵ
	LDMIA	R0!, {R4-R11}
	MSR		PSP, R0

	@ LR�� exception return
	@ Thread mode, process stack
	@ stack�� ��
	@ R0 para
	ORR		LR, LR, #0xd
	BX		LR

	.global _OS_Start_First_Task
	.type 	_OS_Start_First_Task, %function
_OS_Start_First_Task:
	@ SVC exception�� �߻���Ű�� �ڵ�
	@ SVC exception�� �߻��ؼ� SVC_Handler�� ����ǰ� ��
	SVC #0
	BX LR


	.end
