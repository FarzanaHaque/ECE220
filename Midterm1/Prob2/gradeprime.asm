;Write a program to check whether a given number is a weird number.
;Weird numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are weird while 14 is not since it includes another prime factor 7. You do not need to consider 1 for your program.
;input: a number stored in R3 (a number being set during testing)
;output: if the number stored in R3 is weird, R6 should be set to 1; otherwise R6 should not be set to 1 (can be any other number).


ECEGRADE .FILL  x3000

;; START YOUR CODE HERE
div2 AND R4,R4,#0
ADD R4,R4,#2
JSR DIV
ADD R1,R1,#0
Brz REPEAT2
div3 AND R4,R4,#0
ADD R4,R4,#3
JSR DIV
ADD R1,R1,#0
BRz REPEAT3
div5 AND R4,R4,#0
ADD R4,R4,#5
JSR DIV
ADD R1,R1,#0
BRz REPEAT5
AND R6,R3,R3
BRnzp DONE
REPEAT2
AND R3,R0,R0
BRnzp div2
REPEAT3
AND R3,R0,R0
BRnzp div3
REPEAT5
AND R3,R0,R0
BRnzp div5
DONE HALT









;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;DIVIDE SUBROUTINE
;input: R3, R4 
;calculate R3/R4
;out: R0-quotient, R1-remainder
;DIVIDE
;;IMPLEMENT SUBROUTINE HERE

DIV AND R0,R0,#0
ADD R1,R3,#0
NOT R4,R4
ADD R4,R4,#1
DIVLOOP ADD R0,R0,#1
ADD R1,R1,R4
BRzp divloop
ADD R0,R0,#-1
NOT R4,R4
ADD R4,R4,#1
ADD R1,R1,R4
RET
.END 
