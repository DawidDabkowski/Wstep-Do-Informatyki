prog: prog.o drawing.o
	gcc -Wall -pedantic prog.o drawing.o -o prog `pkg-config --libs gtk+-3.0 gmodule-2.0` -lm

prog.o: prog.c drawing.h
	gcc prog.c -c -o prog.o `pkg-config --cflags gtk+-3.0`

drawing.o: drawing.h drawing.c
	gcc drawing.c -c -o drawing.o `pkg-config --cflags gtk+-3.0`


.PHONY: clean
clean:
	rm -f *~ *.o prog



