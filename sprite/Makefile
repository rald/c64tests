all: sprite.prg

sprite.prg: sprite.c
	cc65 -t c64 sprite.c
	ca65 sprite.s
	cl65 sprite.o -o sprite.prg

clean:
	rm sprite.o sprite.s sprite.prg


