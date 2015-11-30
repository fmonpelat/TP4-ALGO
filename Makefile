CC=gcc
CFLAGS=-pedantic -Wall -g
SOURCES=main.o bignum.o simplecalc.o bignumList.o 
EXECUTABLE=tp4

all: $(EXECUTABLE)

tp4: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -lm -o $(EXECUTABLE)

main.o: main.c bignum.h
	$(CC) $(CFLAGS) -c main.c

bignum.o: bignum.h bignum.c
	$(CC) $(CFLAGS) -c bignum.c

simplecalc.o: simplecalc.h simplecalc.c
	$(CC) $(CFLAGS) -c simplecalc.c

bignumList.o: bignumList.h bignumList.c
	$(CC) $(CFLAGS) -c bignumList.c

clean:
	rm *.o tp3
