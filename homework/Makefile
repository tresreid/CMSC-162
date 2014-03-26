# Makefile

CFLAGS= -std=c99

bmi: weight.o height.o bmi.o

weight.o: weight.h
height.o: height.h
bmi.o: weight.h height.h

clean:
	rm -f weight.o height.o bmi.o bmi

install: bmi
	cp bmi ~/bin