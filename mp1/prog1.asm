;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6                 ,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

;PRINT_HIST only occurs after we've gone through the entire string (aka reach the null character) and completed the histogram
;In my lab, I created a program that would print a hexadecimal number stored in a register, and I decided to reuse it here.
;In my lab I use registers 0-3 &6 so while I could've changed my registers I didn't want to mess around with so instead
;since I am reusing R0,R2&R6 from the top part of the program, I make sure to store them into memory so that after I use
;my code from the lab, I can load the original values of those registers
;I use R6 as my loop counter, similarly to line 45 of this code
;The first thing I print in every line is the character being counted, nonalphabetic (represented all by @) or a specific letter
;To get this I figured that the current line I'm examining of the histogram - start of the histogram tells me if it's the 1st,2nd,
;and so on line of the histogram, if it's the first I would print out @, 2nd A, and onward. luckily all these characters are next to each other
;but @ has the ascii value of 64 so I need to add 64 to R0 before I get the right ascii Value to print out
;Then I print out a space, whose ascii value I already saved into memory location SPACE, so I load into R0 then print out
;I store R2 &R6 for later use. I clear R3 and turn it into the value stored at the line of the histogram being currently examined
;(I do this by making r3<-m[R2+x3F00]), the next part is turning R3 into a character seen on the monitor.

;These are the registers for printing a register value onto the screeen from the lab
;R1 digit counter
;R2 bit counter
;R3 is input
;R6 for math
;R0 is the digit

; I break up the 16 bit value stored into R3 conceptually as 4 digits containing 4 bits each
;I set up a digit counter, if we print all 4 digits, then we go to DONER (done for the lab but not MP)
;Otherwise, we clear the digit and the bit counter, if we have gotten 4 bits from R3 for the current digit we go to PBITS
;otherwise we shift digit left. Then we check to see if R3<0 aka MSB=1, if it is we add 1 to digit, if not we skip that step
;either ways we'll shift the input R3 to the left and increment the bit counter. Then we go back into the loop
;until we get 4 bits from R3 at which point we'll go to PBITS aka we print out the corresponding ascii char for the digit
;we do this by adding the ascii value of '0' if it's from 0-9 or the ascii value of'A' -10. After that we just print
;and increment the digit counter and then go back into the loop until we've printed 4 digits. At which point we go to DONER
;In Doner, we restore,increment,and once again store R2 in order to update the location of the histogram's line
;Then we restore,and decrement R6, If R6=0 then we're done with the program
;otherwise we print out a newline and go back into the printloop in order to get the next printed line 

PRINT_HIST
	ST R0,SAVER0 ; right now R0 contain pointer but we also need it for our outputs 
	ST R2,SAVER2
	LD R6, NUM_BINS ;Sets R6 to 27



	PRINTLOOP 
		LD R0,SAVER0
		LD R2,SAVER2
		NOT R0,R0
		ADD R0,R0,#1 ;R0=-R0
		ADD R0,R0,R2 ;R0=Current location - start of histogram
		ADD R0, R0, #15
		ADD R0, R0, #15
		ADD R0, R0, #15
		ADD R0, R0, #15
		ADD R0, R0, #4 ;R0=current location -start of histogram +#64(ascii value of @)
		OUT
		LD R0, SPACE ;loads space char
		OUT
;R1 digit counter
;R2 bit counter
;R3 is input
;R6 for math
;R0 is the digit


		ST R2, SAVER2 ;Stores R2 to load later
		ST R6, SAVER6 ;stores R6 to load later
		AND R3,R3,#0 ;Clears R3
		ADD R3,R3,R2 ;R3<-R2
		LD R0, SAVER0 ;Loads x3F00 into R0 which was previous the space char
		ADD R3,R3,R0 ;R3<-R2+x3F00 aka location of line currently being examine
		LDR R3,R3,#0 ;R3<-M[R3], the value stored at the line of histogram aka # of times written
		AND R1,R1, #0; Clear digit counter
		INITD
			ADD R6,R1,#-4 ;checks to see if printed <4 digits
			BRzp DONER ;if so done with printing the value stored in R3 but not with the program
			AND R0,R0, #0; Clear digit
			AND R2,R2, #0; Clear bit counter
				INITDB ADD R6,R2,#-4 ;got <4 bit from R3?
				BRzp PBITS ; False, when we've got 4 bits from R3
				ADD R0,R0,R0; shift digits left
				ADD R3,R3,#0; to get CC of r3
				BRn ADD1dig ;if negative add1 to digit
				BRnzp SHIFTR3 ;otherwise shift digits, don't need to add 0 to digit 
				ADD1dig 
					ADD R0,R0,#1; Add 1 to digit
				SHIFTR3
				ADD R3,R3,R3; Right shift R3
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

DONER ;This was DONE in lab must still need to do some stuff before moving on to the next line
	LD R2,SAVER2 ;Restore R2
	ADD R2,R2,#1 ;Increment R2
	ST R2,SAVER2 ;Store new value of R2
	LD R6, SAVER6 ;Restore R6
	ADD R6,R6,#-1 ;Decrement R6
	BRz DONE ;IF r6=0 printed all 27 lines & actually are done
	LD R0, NEWLINE ;otherwise print newline
	OUT
	BRnp PRINTLOOP ;go back to loop since you're not done







DONE	HALT			; done

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
SPACE           .FILL #32 ;Space char
NEWLINE         .FILL x000A ;newline char
SAVER0 .BLKW 1 ;These store values of registers to be restored later
SAVER2 .BLKW 1
SAVER6 .BLKW 1

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code. AbCd...WxYz. "



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
