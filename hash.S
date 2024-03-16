// CES30 assignment template
// 
// cse30sp23id: A17267531
//
// Describe target Hardware to the assembler
.arch   armv6
.cpu    cortex-a53
.syntax unified

.text                       //start of the text segment
//function hashFun 
.type   hashFun, %function  //define as a function
.global hashFun             //export function name
.equ    FP_OFFSET, 28       //(regs - 1) * 4

hashFun:
    push    {r4-r9, fp, lr}     // use r4-r9 protected regs
    add     fp, sp, FP_OFFSET   // locate our frame pointer
    //DO NOT EDIT PROLOGUE ABOVE
    //You can use temporary r0-r3 and preserved r4-r9
    //Store return value (results) in r0
    
    //YOUR CODE GOES HERE
    LSL R2, R1, #6  
    LSL R3, R1, #16  
    SUB R4, R3, R1 
    ADD R5, R4, R2
    ADD R0, R0, R5
   
    //DO NOT EDIT EPILOGUE BELOW
    sub     sp, fp, FP_OFFSET   //restore sp
    pop     {r4-r9, fp, lr}     //restore saved registers
    bx      lr                  //function return
    .size   hashFun,(.-hashFun)
