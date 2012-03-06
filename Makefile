CC=gcc
CFLAGS=-O3 -Wall -Wno-strict-aliasing -Wno-unused-but-set-variable -Wno-unused-variable
LIBS=-s

all: test.exe

test.exe: test.c commonc/math.h commonc/stopwatch.h commonc/libcommonc.a
	${CC} ${CFLAGS} -o test.exe test.c -Lcommonc -lcommonc ${LIBS}

commonc/math.o: commonc/config.h commonc/math.h commonc/math.c
	${CC} ${CFLAGS} -c -o commonc/math.o commonc/math.c

commonc/stopwatch.o: commonc/config.h commonc/stopwatch.h commonc/stopwatch.c
	${CC} ${CFLAGS} -c -o commonc/stopwatch.o commonc/stopwatch.c

commonc/libcommonc.a: commonc/math.o commonc/stopwatch.o
	ar -rcs commonc/libcommonc.a commonc/math.o commonc/stopwatch.o

clean:
	del /S /Q *.exe > nul
