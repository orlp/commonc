/*

    Copyright 2011 Orson Peters. All rights reserved.

    Redistribution of this work, with or without modification, is permitted if
    Orson Peters is attributed as the original author or licensor of
    this work, but not in any way that suggests that Orson Peters endorses
    you or your use of the work.

    This work is provided by Orson Peters "as is" and any express or implied
    warranties are disclaimed. Orson Peters is not liable for any damage
    arising in any way out of the use of this work.

*/

#include "stopwatch.h"

#if defined (__WIN32__) || defined (_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#end


#if defined (__WIN32__) || defined (_WIN32)

void stopwatch_start(stopwatch_t *stopwatch) {
    QueryPerformanceCounter((LARGE_INTEGER*) stopwatch_t);
}


double stopwatch_gettime(stopwatch_t *stopwatch) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, stop;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&stop);
    start = * (LARGE_INTEGER*) stopwatch;

    return (stop.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}

#else

void stopwatch_start(stopwatch_t *stopwatch) {
    gettimeofday((timeval*) stopwatch, NULL);
}


double stopwatch_gettime(stopwatch_t *stopwatch) {
    timeval start, stop;

    gettimeofday(&stop, NULL);
    start = *(timeval*) stopwatch;

    return (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
}

#endif
