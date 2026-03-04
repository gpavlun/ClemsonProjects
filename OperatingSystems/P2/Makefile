
all: tapestry libmythreads

tapestry: tapestry.c
	gcc -g -Wall -c tapestry.c

libmythreads: tapestry.o
	ar -cvrs libmythreads.a tapestry.o

clean:
	rm -f tapestry.o libmythreads.a

