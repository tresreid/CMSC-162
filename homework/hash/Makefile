CFLAGS= -std=c99 -O3
SRC=dict.c hist.c hash.c get_word.c

all: hist

hist: dict.o hist.o hash.o get_word.o

depend:
	makedepend -Y ${SRC} >& /dev/null

clean:
	rm -rf *.o hist Makefile.bak


