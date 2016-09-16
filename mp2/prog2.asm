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
num LD R1, zero ;loads ascii value '0'
NOT R1,R1
ADD R1,R1,#1
ADD R0,R0,R1 ;R0<-char-'0' aka numerical value of char
JSR PUSH

BRnzp GETCHAR
operator
ST R0, SAVEOP
JSR POP
ADD R4,R0,#0 ;the newest operand is in r4
JSR POP
ADD R3,R0,#0 ;the older operand is in r3
LD R0, SAVEOP
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
LD R0, xchar
OUT ;prints out xchar
;RET ;removessssssssssssssssssssssssssss
AND R1,R1, #0; Clear digit counter
		INITD
			ADD R6,R1,#-4 ;checks to see if printed <4 digits
			BRzp DONE ;if so done with printing the value stored in R5 & the program
			AND R0,R0, #0; Clear digit
			AND R2,R2, #0; Clear bit counter
				INITDB ADD R6,R2,#-4 ;got <4 bit from R5?
				BRzp PBITS ; False, when we've got 4 bits from R5
				ADD R0,R0,R0; shift digits left
				ADD R5,R5,#0; to get CC of r5
				BRn ADD1dig ;if negative add1 to digit
				BRnzp SHIFTR5 ;otherwise shift digits, don't need to add 0 to digit 
				ADD1dig 
					ADD R0,R0,#1; Add 1 to digit
				SHIFTR5
				ADD R5,R5,R5; Right shift R5
				ADD R2,R2,#1 ;Increment bit counter
				BRnzp INITDB ;go back to loop to see if printed <4 bits
				PBITS ADD R6,R0, #-9 ;checks to see if digit <=9
					BRp ADDA ;If digit more than 9, add 'A' -10
					ADD R0,R0, #15 ;Digit is 9 or less so add ASCII '0' aka 48
					ADD R0,R0, #15
					ADD R0,R0, #15
					ADD R0,R0, #3; ADD '0' aka 48
					BRnzp OUTTRAP ;go print out digit
					ADDA  ;Digit is 10 or more so add "A" -10 to digit
						ADD R0,R0,#15
						ADD R0,R0,#15
						ADD R0,R0,#15
						ADD R0,R0,#10;ADD ('A'-10) aka 55
					OUTTRAP TRAP x21 ;OUT
						ADD R1, R1, #1; Increment digit counter
						BRnzp INITD ;go back to loop to see if printed 4 digits yet
DONE HALT

zero .FILL x0030


MULsign .FILL x002A 
PLUSsign .FILL x002B
MINsign .FILL x002D
DIVsign .FILL x002F
EXPsign .FILL x005E

SAVEOP .BLKW #1

NEG_OPEN .FILL xFFD8
NEG_CLOSE .FILL xFFD7
SPACE    .FILL x0020
NEW_LINE    .FILL x000A
CHAR_RETURN    .FILL x000D

invalidexp .STRINGZ "Invalid Expression"









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;PRINT_HEX


;DONER RET ;T
xchar .FILL x0078
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
ADD R0,R3,R4
RET


	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
NOT R4,R4
ADD R4,R4,#1
ADD R0,R3,R4
RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
AND R0,R0,#0 ;clears r0
checkmul ADD R3,R3,#0 ;checks if R3=0
BRz stopmult 
ADD R0,R0,R4
ADD R3,R3,#-1
BRnzp checkmul
stopmult RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here	
;the idea is subtracting r4 from r3 (add 1 each time) til # less than r4, then store the incremented into r0 and new r3 into r1 
	AND R0,R0,#0 ;clear quotient	
	ADD R1,R3,#0 ;set remainder to dividend initially
	NOT R4,R4
	ADD R4,R4,#1 ;set r4 to -r4
	ADD R3,R3,#0 ;testing to see if r3 is neg
	BRn neg ;if neg neg loop
DIVLOOP
	
	ADD R0,R0,#1
	ADD R1,R1,R4 ;current remainder-divisor	
	BRzp DIVLOOP 
	ADD R0,R0,#-1 ;otherwise quotient 1 too much
	NOT R4,R4
	ADD R4,R4,#1 ;restores R4 to original
	ADD R1,R1,R4 ;lol i think it's because it's off otherwise/neg
	BRnzp divdone		
neg
	NOT R3,R3
	ADD R3,R3, #1 ;R3=-r3 bc we already know how to divide w/ pos # and we can negate it to get the neg inverse later
	ADD R1,R3,#0 ;R1=-R3 so that our division works the same as for positive
negloop	ADD R0,R0,#1
	ADD R1,R1,R4 ;current remainder-divisor	
	BRzp negloop 
	ADD R0,R0,#-1 ;otherwise quotient 1 too much
	NOT R4,R4
	ADD R4,R4,#1 ;restores R4 to original
	ADD R1,R1,R4 ;lol i think it's because it's off otherwise/neg
	NOT R0,R0 ;R0 right now equals -R3/R4, want to negate
	ADD R0,R0,#1	;now r0 is correct
	BRnzp divdone		;for this problem we assume R4 always + bc can't input negative divisor in calc
divdone RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3=base of exponent, R4=exponent,r6=0 except when negative base and odd exponent bc then you're output is negative
;out R0
EXP
;your code goes here
AND R6,R6,#0 ;clears
AND R0,R0,#0 ;clears r0
ST R4, expr4 ;going to change the value r4 temporarily if r3 is negative, but then restore back
ADD R3,R3,#0
Brz stopexp ;if R3=0 then you want to keep the 0 in r0 
Brp posexp
NOT R3,R3
ADD R3,R3,#1 ;R3=-R3 , only occurs when R3 starts neg
ADD R4,R4,R4 ;right shift 15x if pos or zero, then R4 was even, if neg R4 was odd
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
ADD R4,R4,R4 ;right shift
Brzp posexp ;if R3= neg # &exp=even then -R3^R4 = R3^R4 so go to positive loop
ADD R6,R6,#-1 ;

posexp 
LD R4,expr4 ;restores value of r4
ADD R0,R0,#1 ;sets r0 to 1
checkexp ADD R4,R4,#0 ;checks CC of R4
 BRz stopexp
ST R3,expr3


AND R1,R1,#0 ;clears r1, will store current value of r0*r3
checkmul2 ADD R3,R3,#0 ;checks if R3=0
BRz stopmult2 
ADD R1,R1,R0
ADD R3,R3,#-1
BRnzp checkmul2
stopmult2 ADD R0,R1,#0
LD R3,expr3
ADD R4,R4,#-1
BRp checkexp ;doesn't work if r4 is negative but that's okay	
ADD R6,R6,#0
Brz stopexp
NOT R0,R0
ADD R0,R0,#1

stopexp RET
expr3 .BLKW #1	
expr4 .BLKW #1

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
