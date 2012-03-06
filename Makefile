CC=gcc
CFLAGS=-O3 -Wall -Iinclude

all: test.exe

test.exe: test.c  include/commonc/math.h  include/commonc/stopwatch.h lib/libcommonc.a
	${CC} ${CFLAGS} -o test.exe test.c -s -Llib -lcommonc

src/math.o: include/commonc/config.h include/commonc/math.h include/commonc/endian.h include/commonc/integer.h src/math.c
	${CC} ${CFLAGS} -c -o src/math.o src/math.c

src/stopwatch.o: include/commonc/stopwatch.h src/stopwatch.c
	${CC} ${CFLAGS} -c -o src/stopwatch.o src/stopwatch.c

lib/libcommonc.a: src/math.o src/stopwatch.o
	ar -rcs lib/libcommonc.a src/math.o src/stopwatch.o

clean:
	rm -Rf \*.exe
	rm -Rf \*.a
	rm -Rf \*.o
