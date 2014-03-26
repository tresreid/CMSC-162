#Makefile

CFLAGS = -std=c99

power: pow.o power.o

pow.o : power.h
power.o :power.h

clean:
	rm -f power.o pow.o power

install: power
	cp power ~/bin