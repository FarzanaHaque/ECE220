.ORIG x3000

;;R5 - frame pointer
;;R6 - stack pointer
;;MAIN - DO NOT CHANGE ANY CODE HERE
	LD R6, STACK
	LD R5, STACK
	ADD R6, R6, 1	; runtime stack is empty
	ADD R6, R6, -1	; space for x

	AND R0, R0, 0	; counter for # of elements in array
	ADD R0, R0, 4	
	AND R1, R1, 0	; values of array
	ADD R1, R1, 4
INITARR
	ADD R6, R6, -1	; space for arr[i]
	STR R1, R6, 0	; initialize array cell with value
	ADD R1, R1, -1	; decrement value(4,3,2,1)
	ADD R0, R0, -1	; decrement R0 by 1	
	BRp INITARR	; check whether its done 4 times 

;;;;;;;;;;;;;;;;;;;;;;;IMPLEMENT ME: stack build up - prepare to call ARRAY_SUM

ADD R6,R6,#-1
LDR R0,R5,#-1
STR R0,R6,#0
ADD R0,R0, #-1
LDR R0,R5,#0
STR R0, R5,#-2

ADD R6,R6,#-2
STR R7,R6,#0
ADD R6,R6,#-1
STR R5,R5,#0
ADD R5,R6,#-1
ADD R6,R6,#-1
AND R0,R0,#0
STR R0,R0,#0





;IMPLEMENT ME: call ARRAY_SUM
	
JSR ARRAY_SUM

;;;;;;;;;;;;;;;;;;;;;;;;;IMPLEMENT ME: stack tear down after returning from ARRAY_SUM 
LDR R0,R6,#0
STR R0,R5,#0
ADD R6,R6,#1
ADD R5,R6,#1


;IMPLEMENT ME: return 0

HALT	

;----------END OF MAIN----------

;ARRAY_SUM subroutine starts here
ARRAY_SUM
;;;;;;;;;;;;;;;;;;;;;;;IMPLEMENT ME: stack build up at ARRAY_SUM

ADD R6,R6,#1 ;space for ret
ADD R6,R6,#-1
STR R7,R6,#0 ;push r7 onto stack
ADD R6,R6,#-1
STR R5,R6,#0
ADD R5,R6,#-1
ADD R6,R6,#-2 ;for the two local variables

;IMPLEMENT ME: Calculation

ST R1, save_R1
AND R2,R2,#0 ;clears i
AND R3,R3,#0 ;clears sum
LOOP 
ADD R2,R2,#-4 ;
Brzp SKIP
ADD R2,R2,#4 
LD R1, STACK
ADD R1,R1,#4
ADD R1, R1,R2 ;r1=address of array[i]
LDR R1,R1,#0 ;r1=value at i
ADD R3,R3,R1 ;r3=sum+array[i]
ADD R2,R2,#1
BRnzp LOOP
SKIP
ADD R0,R3,R3
;returns sum
LD R1, save_R1



;;;;;;;;;;;;;;;;;;;;;;;;IMPLEMENT ME: stack tear down - prepare to go back to main
;need to pop off return value (R3) and copy it to local variable?
;LDR R3,R6,#0
;STR R0,R5, #0 ;return value in x now
;ADD R3,R6,#1
;ADD R5,R6,#1 ;gets rid of the argument

;LDR R0,R6,#0
;ADD R6,R6, #1 ;pop ret
;ADD R6, R6, #1 ;pop argument

LDR R0,R5,#-1 ;Temp variable loaded
STR R0,R5, #3 ;return value stored
ADD R6,R6,#2
LDR R5,R6,#0
ADD R6,R6,#1

LDR R7,R6,#0 ;pop ret address
ADD R6,R6,#1
	RET

save_R1 .BLKW #1
STACK .FILL x6000

.END
