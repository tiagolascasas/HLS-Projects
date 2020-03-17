#
# Set BINDIR to where you want the binaries to go.
#
BINDIR=	.

#CC = cc
#CFLAGS= +O3  -I. -DNDEBUG
CC = cc
CFLAGS= -O2  -I. -DNDEBUG
#CC = gcc
#CFLAGS= -I. -O2 -DNDEBUG

SRC= huffc.c huffd.c read.c write.c util.c mcu.c
OBJ= huffc.o huffd.o read.o write.o util.o mcu.o

default: filter timer tags

filter: $(OBJ) main.o
	$(CC) ${CFLAGS} -o filter main.o $(OBJ)

timer: $(OBJ) memory.o
	$(CC) ${CFLAGS} -o timer memory.o $(OBJ)

install: filter
	install -c -m 755 filter $(BINDIR)

clean:
	rm -f core lintout makeout Makefile.bak *.o filter timer

proto.h: $(SRC)
	mkproto $(SRC) > proto.h

tags: $(SRC)
	ctags $(SRC)

huffd.o:jpeg.h rle.h
huffc.o:jpeg.h rle.h
main.o:	jpeg.h rle.h
read.o:	jpeg.h rle.h
write.o:jpeg.h rle.h
util.o:	jpeg.h rle.h
mcu.o:	jpeg.h rle.h
