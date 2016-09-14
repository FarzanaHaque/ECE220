;Assuming user will only enter ' ' 0-9 *+/-
;
;
;
.ORIG x3000
	
;your code goes here
	
GETCHAR GETC
OUT ;getrid!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
AND R2,R2,#0 ;using R2 later on to store which operand 
LD R1,NEW_LINE
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0 ;R1=value-newline
BRz NEWLINE
LD R1,CHAR_RETURN
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0 ;R1=value-return
BRz NEWLINE ;(when value= either newline)
LD R1,SPACE
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0 ;R1=value-space ;if R1 is important might need to change reg
BRz GETCHAR
;check if it's 0-9
LD R1,zero
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz num ;checks zero
ADD R1,R1,#-1
BRz num ;checks one
ADD R1,R1,#-1
BRz num ;checks two
ADD R1,R1,#-1
BRz num ;three
ADD R1,R1,#-1
BRz num ;four
ADD R1,R1,#-1
BRz num ;five
ADD R1,R1,#-1
BRz num ;six
ADD R1,R1,#-1
BRz num ;seven
ADD R1,R1,#-1
BRz num ;eight
ADD R1,R1,#-1
BRz num ;nine
LD R1,MULsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz operator
LD R1,PLUSsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz operator
LD R1,MINsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz operator
LD R1,DIVsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz operator
LD R1,EXPsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz operator
invalid LEA R0, invalidexp
PUTS
BRnzp DONE
num JSR PUSH
BRnzp GETCHAR
operator
JSR POP
JSR POP
ADD R5,R5,#-1
BRz invalid

;this part checks which operator and then BRz to that place
LD R1,MULsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz mu
LD R1,PLUSsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz pl
LD R1,MINsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz mi
LD R1,DIVsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz di
LD R1,EXPsign
NOT R1,R1
ADD R1,R1,#1
ADD R1,R1,R0
BRz ex

;the places being called, jsr operator then push & go back to char
mu JSR MUL
JSR PUSH
BRnzp GETCHAR
pl JSR PLUS
JSR PUSH
BRnzp GETCHAR
mi JSR MIN
JSR PUSH
BRnzp GETCHAR
di JSR DIV
JSR PUSH
BRnzp GETCHAR
ex JSR EXP
JSR PUSH
BRnzp GETCHAR

NEWLINE JSR POP
ADD R5,R5,#0
BRp invalid
JSR POP
ADD R5,R5,#0
BRp loadresult
BR invalid
loadresult ADD R5,R0,#0

DONE HALT

zero .FILL x0030
nine .FILL x0039

MULsign .FILL x002A 
PLUSsign .FILL x002B
MINsign .FILL x002D
DIVsign .FILL x002F
EXPsign .FILL x005E

NEG_OPEN .FILL xFFD8
NEG_CLOSE .FILL xFFD7
SPACE    .FILL x0020
NEW_LINE    .FILL x000A
CHAR_RETURN    .FILL x000D

invalidexp .STRINGZ "Invalid Expression"









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	
RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
RET	
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
