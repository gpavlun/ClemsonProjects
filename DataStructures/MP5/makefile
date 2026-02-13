# makefile for MP5
# Version: 1
#
# -lm is used to link in the math library
#
# -Wall turns on all warning messages 
#
comp = gcc
comp_flags = -Wall -lm


lab5 : yggdrasil.o lab5.o
	$(comp) $(comp_flags) yggdrasil.o lab5.o -o lab5 -lm


yggdrasil.o : yggdrasil.c veðrfölnir.h
	$(comp) $(comp_flags) -c yggdrasil.c

lab5.o : lab5.c veðrfölnir.h
	$(comp) $(comp_flags) -c lab5.c

clean :
	rm -f *.o lab5 core

