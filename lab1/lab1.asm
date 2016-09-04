 ; Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor
;R1 digit counter
;R2 bit counter
;R3 is input
;R6 is for math
;R0 is the digit

 .ORIG x3000
AND R1,R1, #0; Clear digit counter
INITD
ADD R6,R1,#-4
BRzp DONE
AND R0,R0, #0; Clear digit
AND R2,R2, #0; Clear bit counter
INITDB ADD R6,R2,#-4
BRzp PBITS ; False
ADD R0,R0,R0; shift digits left
ADD R3,R3,#0; to get r3
BRn ADD1dig ;
BRnzp SHIFTR3 ;
ADD1dig 
ADD R0,R0,#1;
SHIFTR3
ADD R3,R3,R3;
ADD R2,R2,#1
BRnzp INITDB
PBITS ADD R6,R0, #-9
BRp ADDA
ADD R0,R0, #15
ADD R0,R0, #15
ADD R0,R0, #15
ADD R0,R0, #3; ADD '0'/48
BRnzp OUTTRAP
ADDA 
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#15
ADD R0,R0,#10;ADD 'A'-10/55
OUTTRAP TRAP x21
ADD R1, R1, #1;
BRnzp INITD



 ; stop the computer
DONE
 HALT

 ; program data section starts here
;next time make the adding zero thing the jumped branch, kinda unnecessary the way you currently did it

 .END

