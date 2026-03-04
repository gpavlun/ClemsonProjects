The creator of this garbage is Gregory Pavlunenko



NOTICE: THIS SHIT DID NOT WORK VERY WELL



PROJECT DESCRIPTION

This project implements two simple Linux programs called sctracer and
leakcount. The first program monitors another process while it runs and 
counts how many times each system call is invoked. It uses ptrace to 
intercept syscall entry stops, tracks counts in a linked list, and writes 
the results to a file. The second program is a memory leak counter that
keeps track of any unfreed memory. It uses an LD_PRELOADed shim to intercept 
the calls to malloc, calloc, realloc, and free and stores them in a linked
list. Any allocated memory still in the list after the program terminates
is considered a leak; 

DESIGN

The tracer works by forking a child process and running the target program inside it. 
The parent uses ptrace with PTRACE_SYSCALL and PTRACE_O_TRACESYSGOOD to stop the child 
whenever it enters a syscall. Each syscall number is stored in a linked list that maintains 
counts. The list is kept sorted so output is in ascending order of syscall IDs. When the 
child finishes execution, the linked list is iterated and the counts are written to the 
specified output file. The program currently tracks only syscall entry stops, ignoring exits, 
signals, and child threads for simplicity.

The leak counter works by using LD_PRELOAD to create a shim that intercepts calls to malloc, 
calloc, realloc, and free and stores each call in a linked list that contains the address
and the number of bytes allocated. When a call to realloc is made, the address of the block
is updated and the amount of bytes is adjusted accordingly. Any calls to free will remove an
item from the linked list, if it exists. When the child process exits, the code will print
out all of the remaining(if there are any) items in the list to stderr as leaks.

WARNING!!!!

I am a ternary operator goblin so use of if statements will be few and far between. The syntax
is correct and readable, but it may be a bit odd if you haven't seen a lot of ternaries before.
This also means you MUST USE GCC to compile.

KNOWN PROBLEMS

The program does not follow forks or threads, so syscalls made by child processes of the traced 
program are not counted. The argument parser assumes simple space-separated arguments and so
more complex argument strings may not be handled correctly. The linked list approach will become 
very slow if a traced program makes a very large number of syscalls due to the poor complexity class 
Finally, the program does not explicitly handle signals other than exit, so a crash in the child 
may terminate tracing unexpectedly.