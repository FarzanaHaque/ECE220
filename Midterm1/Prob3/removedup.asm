;write a program that removes duplicate numbers of 
;a sorted sequence stored in memory. The sequence will contain only positive numbers. 
;The sequence starts at memory location x4000 and its end is 
;indicated by the number “0” (0x0). The output sequence should also be sorted.


.ORIG x3000
;;START YOUR CODE HERE

LD R1,SEQ_START
main LDR R2,R1,#0
BRz DONE
LDR R3,R1,#1
BRz DONE ;we can do this bc never two zeros in a row
NOT R2,R2
ADD R2,R2,#1
ADD R2,R2,R3
BRnp skip
JSR PULL
skip ADD R1,R1,#1
BRnzp main
DONE HALT
;;;;;;;;;;;;;;;;;;;;;;;;
;Subroutine PULL
;IN: R0(Start Location)
PULL
;; IMPLEMENT SUBROUTINE HERE
;R1 contains address getting pulled
ST R1,saver1
loop LDR R2,R1,#0 ;R2 value at r1
STR R2,R1,#-1
BRz end
ADD R1,R1,#1
BRnzp loop
end LD R1,saver1
ADD R1,R1,#-1
RET


SEQ_START .FILL x4000
saver1 .BLKW #1
.END







