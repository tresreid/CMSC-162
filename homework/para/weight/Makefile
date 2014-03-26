CFLAGS= -std=c99
LEX=flex
YACC=bison
YFLAGS= -d

SRC=atomic-weight.c element-db.c parse.tab.c tokens.c

all: atomic-weight ~/.mass_data

atomic-weight: atomic-weight.o element-db.o tokens.o parse.tab.o

atomic-weight.o: atomic-weight.[ch] element-db.h
element-db.o: element-db.[ch] atomic-weight.h

parse.tab.o: parse.tab.c
parse.tab.c parse.tab.h: parse.y
	${YACC.y} parse.y

tokens.o: tokens.c parse.tab.h
tokens.c: tokens.l

depend: parse.tab.c
	makedepend ${SRC} -Y >& /dev/null

clean:
	rm -f *.o tokens.c parse.tab.[ch] atomic-weight

~/.mass_data: mass.data
	cp mass.data ~/.mass_data
	
install: atomic-weight ~/.mass_data
	cp atomic-weight ~/bin

test: atomic-weight ~/.mass_data
	./atomic-weight "CH3(CH2)6CH3"

# DO NOT DELETE

atomic-weight.o: element-db.h
element-db.o: atomic-weight.h element-db.h
