
all: ttest

#tapestry: tapestry.c
#	gcc -g -Wall -c tapestry.c

#libmythreads: tapestry.o
#	ar -cvrs libmythreads.a tapestry.o

ttest: ttest.c
	gcc ttest.c tapestry.c -o ttest -L. -llinkedlist


clean:
	rm -f test

