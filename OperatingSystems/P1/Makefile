CC = gcc
CFLAGS = -Wall -Wextra -fPIC
LDFLAGS = -ldl

all: leakcount mem_shim.so sctracer

leakcount: leakcount.c
	$(CC) $(CFLAGS) -o leakcount leakcount.c

mem_shim.so: mem_shim.c
	$(CC) $(CFLAGS) -shared -o mem_shim.so mem_shim.c $(LDFLAGS)

sctracer: sctracer.c
	$(CC) $(CFLAGS) -o sctracer sctracer.c

clean:
	rm -f leakcount mem_shim.so sctracer

