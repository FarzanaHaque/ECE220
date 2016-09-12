;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000

AND R4,R4,#0
ADD R4,R4,#10
MAINLOOP
	JSR DIV
	ADD R3,R0,#0 ;quotient to r3 to check later if done, did first bc about to change r0
	ADD R0,R1,#0 ;remainders show the digits of the #
	JSR PUSH
	ADD R3,R3,#0 ;check if done now
	BRp MAINLOOP
POPLOOP
	LD R6, ASCII_0
	JSR POP
	ADD R5,R5,#0
	BRp DONE ;when r5 is pos aka underflow
	ADD R0,R0,R6 ;so now it's the right ascii value
	OUT
	BR POPLOOP












ASCII_0 .FILL x30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0-quotient, R1-remainder
DIV	
;the idea is subtracting r4 from r3 (add 1 each time) til # less than r4, then store the incremented into r0 and new r3 into r1 
	AND R0,R0,#0 ;clear quotient
	
	ADD R1,r3,#0 ;set remainder to thing initially
;ADD R1,R1,R3 ;not sure why but if don't work....
	NOT R4,R4
	ADD R4,R4,#1 ;set r4 to -r4

DIVLOOP
	
	ADD R0,R0,#1
	ADD R1,R1,R4 ;current remainder-divisor	
	BRzp DIVLOOP 
	ADD R0,R0,#-1 ;otherwise quotient 1 too much
	NOT R4,R4
	ADD R4,R4,#1 ;restores R4 to original
	ADD R1,R1,R4 ;lol i think it's because it's off otherwise/neg
	

	RET

DONE
	HALT
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END
