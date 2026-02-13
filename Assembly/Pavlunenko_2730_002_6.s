/*
NAME:    Gregory Pavlunenko
COURSE:  ECE 2730
SECTION: 002
DATE:    04.07.2025
FILE:    Pavlunenko_2730_002_6.s
PURPOSE: This program is designed to
         take an integer input and
         calculate the fibonacci 
         sequence numbers up to that
         point.
*/



/* begin assembly stub */

.globl Factorial
.type Factorial, @function

/* put assembler directives here */

Factorial:
    /* prolog */

    pushl %ebx 
    pushl %ebp
    movl %esp, %ebp    

    /* put code here */

    movl 12(%ebp), %eax /*gets n value */
    cmpl $0, %eax /*if n==0 go to jret0 */
    je jret0
    cmpl $1, %eax /*if n==1 go to jret */
    je jret

    subl $1, %eax /*remove 1 from n */
    pushl %eax /*store on stack */
    call Factorial /*recursive function call */
    addl $4, %esp /*allocate space */
    movl 12(%ebp), %ebx /*retrieve n */
    mull %ebx /*mult n * factorial(n-1) */
    jmp jret

    jret0:
    movl $1, %eax /*if n==0 return 1 */

    /* epilog */
    jret:
        movl %ebp, %esp
        popl %ebp
        popl %ebx
        ret
    
/* end assembly stub */
