CFLAGS=-std=c99
LEX=flex
YACC=bison
YFLAGS=-d

SRC=paray.tab.c paratok.c para.c

all: para

para: paray.tab.o paratok.o para.o

para.o: para.[ch]

paray.tab.o: paray.tab.c
paray.tab.c paray.tab.h: paray.y
	${YACC.y} paray.y 

paratok.o: paratok.c paray.tab.h
paratok.c: paratok.l

depend: paray.tab.c
	makedepend ${SRC} -Y >& /dev/null

clean:
	rm -f *.o paratok.c para.tab.[ch]