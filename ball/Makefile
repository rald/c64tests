all: ball.prg

ball.prg: ball.c
	cc65 -t c64 ball.c
	ca65 ball.s
	cl65 ball.o -o ball.prg

clean:
	rm ball.o ball.s ball.prg


