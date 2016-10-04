.ORIG x3000

lea r0, stringInput ;input character
puts
;;START YOUR CODE HERE

;r1=max length
;r2=current length
;r0=current input
;r4=previous input
;r5 temp registor for math
 GETC
OUT
AND R1,R1,#0
ADD R1,R1,#1
AND R2,R2,#0
ADD R2,R2,#1
AND R4,R0,R0 ;set previous inpuot= current input when getting first char
loop NOT R5,R4
ADD R5,R5,#1
ADD R5,R5,R0; current i-prvi
BRp inccurrent
AND R2,R2,#0
ADD R2,R2,#1
BRnzp complength
inccurrent ADD R2,R2,#1
complength NOT R5,R1
ADD R5,R5,#1
ADD R5,R5,R2 ;current lenth-max
BRnz nextchar
AND R1,R2,R2; maxlength = current length
nextchar AND R4,R0,R0
GETC
OUT
LD R5,ast
NOT R5,R5
ADD R5,R5,#1
ADD R5,R5,R0
BRnp loop
AND R6,R1,R1 ;max length saved


DONE HALT
ast .FILL X002A
stringInput .stringz "Please input number: "
;maxLength .fill 0
;length .fill 0
;previous .fill 0
;current .fill 0
.END


