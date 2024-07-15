	.syntax unified
	.thumb

	.text

	.align 4

	.global PendSV_Handler
	.type 	PendSV_Handler, %function
PendSV_Handler:

	.global SVC_Handler
	.type 	SVC_Handler, %function
SVC_Handler:

	.end
