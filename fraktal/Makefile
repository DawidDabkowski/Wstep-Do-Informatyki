prog: prog.o utils.o draw.o
	gcc -Wall -pedantic prog.o utils.o draw.o -o prog `pkg-config --libs gtk+-3.0 gmodule-2.0` -lm

prog.o: prog.c draw.h
	gcc prog.c -c -o prog.o `pkg-config --cflags gtk+-3.0`

utils.o: utils.c utils.h
	gcc utils.c -c -o utils.o `pkg-config --cflags gtk+-3.0`

draw.o: draw.h draw.c
	gcc draw.c -c -o draw.o `pkg-config --cflags gtk+-3.0`


.PHONY: clean
clean:
	rm -f *~ *.o prog



