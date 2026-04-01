all: roll.prg

roll.prg: roll.c
	cc65 -t c64 roll.c
	ca65 roll.s
	cl65 roll.o -o roll.prg

clean:
	rm roll.o roll.s roll.prg


