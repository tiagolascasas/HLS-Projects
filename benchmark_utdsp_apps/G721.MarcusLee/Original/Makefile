#
# Makefile for adpcm and test programs
#
# For Suns, define -DNODIVMUL (to make code run 5 times faster)
#CFLAGS=-DNODIVMUL -O
#
# For SGI's don't define -DNODIVMUL (it only makes things slower)
#CFLAGS=-O

ALLSRC=README adpcm.2 Makefile adpcm.h adpcm.c testc.c testd.c

all: testc testd adpcm.o

adpcm.o: adpcm.h

testc: testc.o adpcm.o
	cc testc.o adpcm.o -o testc

testd: testd.o adpcm.o
	cc testd.o adpcm.o -o testd

adpcm.shar: $(ALLSRC)
	shar $(ALLSRC) > adpcm.shar
