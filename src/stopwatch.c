/*

    Copyright 2012 Orson Peters. All rights reserved.

    Redistribution of this work, with or without modification, is permitted if
    Orson Peters is attributed as the original author or licensor of
    this work, but not in any way that suggests that Orson Peters endorses
    you or your use of the work.

    This work is provided by Orson Peters "as is" and any express or implied
    warranties are disclaimed. Orson Peters is not liable for any damage
    arising in any way out of the use of this work.

*/

#include "commonc/stopwatch.h"

#if defined (__WIN32__) || defined (_WIN32)
#include <windows.h>
#else
#include <sys/time.h>
#endif


#if defined (__WIN32__) || defined (_WIN32)

void cc_stopwatch_start(cc_stopwatch_t *stopwatch) {
    QueryPerformanceCounter((LARGE_INTEGER*) stopwatch);
}


double cc_stopwatch_gettime(cc_stopwatch_t *stopwatch) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, stop;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&stop);
    start = * (LARGE_INTEGER*) stopwatch;

    return (stop.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}

#else

void cc_stopwatch_start(cc_stopwatch_t *stopwatch) {
    gettimeofday((timeval*) stopwatch, NULL);
}


double cc_stopwatch_gettime(cc_stopwatch_t *stopwatch) {
    timeval start, stop;

    gettimeofday(&stop, NULL);
    start = *(timeval*) stopwatch;

    return (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
}

#endif
