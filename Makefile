CC=gcc
CFLAGS=-O3 -Wall -Wno-strict-aliasing -Wno-unused-but-set-variable -Wno-unused-variable 
LIBS=-s

all: test.exe

test.exe: test.c commonc/math.h commonc/math.o commonc/stopwatch.h commonc/stopwatch.o
	${CC} ${CFLAGS} -o test.exe test.c commonc/math.o commonc/stopwatch.o ${LIBS}

commonc/math.o: commonc/math.h commonc/math.c
	${CC} ${CFLAGS} -c -o commonc/math.o commonc/math.c

commonc/stopwatch.o: commonc/stopwatch.h commonc/stopwatch.c
	${CC} ${CFLAGS} -c -o commonc/stopwatch.o commonc/stopwatch.c

clean:
	del /S /Q *.exe > nul
