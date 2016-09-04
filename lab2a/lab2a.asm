
;modified POP to store value in R6.
;read comments
;
.ORIG x3000

GET_CHAR
    AND R0, R0, #0 ;Clears R0
    GETC
    OUT
    LD R1, SPACE ;Loads SPACE CHAR
    NOT R1,R1
    ADD R1,R1,#1
    ADD R1,R0, R1 ;R1=R0-Space char
    BRz GET_CHAR ;R0= space so get next character
    LD R1, NEW_LINE
    NOT R1,R1
    ADD R1,R1,#1
    ADD R1,R0, R1 ;R1=R0-New line
    BRz DONER ;R0= NEW_LINE so DONE
    LD R1,CHAR_RETURN ;Loads return character
    NOT R1,R1
    ADD R1,R1,#1
    ADD R1,R0, R1 ;R1=R0-Return_char
    BRz DONER ;R0= return so done
    JSR IS_BALANCED
    BRnzp GET_CHAR ;RIGHT???   
SPACE    .FILL x0020

NEW_LINE    .FILL x000A
CHAR_RETURN    .FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else not modified.
IS_BALANCED
    ;ST R7,    IS_BALANCE_SaveR7
    LD R1,NEG_OPEN
    ADD R1,R1,R0;
    BRz subPUSH
    LD R1,NEG_CLOSE
    ADD R1,R1,R0
    BRz subPOP
    BRnp GET_CHAR ;DOES THIS EVEN HAPPEN? LIKE idk
subPUSH
    JSR PUSH
    BRnzp GET_CHAR
subPOP
    JSR POP
    LD R1,NEG_OPEN
    ADD R1,R1,R0
    BRz GET_CHAR
    AND R5,R5,#0
    ADD R5,R5,#-1
    BRnzp DONE
DONER
;pop until encounter starting bracket-> unbalanced or empty->balanced
ADD R1,R5,#-1
BRnp donerPOP
BRz DONE
donerPOP JSR POP
LD R1,NEG_OPEN
ADD R1,R0,R1;
BRz UNBALANCED
BRnzp DONER
UNBALANCED
    AND R5,R5,#0
    ADD R5,R5,#-1
DONE HALT


    ;RET


     

NEG_OPEN .FILL xFFD8
NEG_CLOSE .FILL xFFD7
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH   
    ST R3, PUSH_SaveR3    ;save R3
    ST R4, PUSH_SaveR4    ;save R4
    AND R5, R5, #0        ;
    LD R3, STACK_END    ;
    LD R4, STACk_TOP    ;
    ADD R3, R3, #-1        ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0        ;no overflow, store value in the stack
    ADD R4, R4, #-1        ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH        ;
OVERFLOW
    ADD R5, R5, #1        ;
DONE_PUSH
    LD R3, PUSH_SaveR3    ;
    LD R4, PUSH_SaveR4    ;
    RET


PUSH_SaveR3    .BLKW #1    ;
PUSH_SaveR4    .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3    .BLKW #1    ;
POP_SaveR4    .BLKW #1    ;
STACK_END    .FILL x3FF0    ;
STACK_START    .FILL x4000    ;
STACK_TOP    .FILL x4000    ;

.END
