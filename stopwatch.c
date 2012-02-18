#include "stopwatch.h"

#if defined (__WIN32__) || defined (_WIN32)

#include <windows.h>
typedef LARGE_INTEGER* _intern_stopwatch_t;

#else

#include <sys/time.h>
typedef timeval* _intern_stopwatch_t;

#endif


stopwatch_t stopwatch_start() {
    _intern_stopwatch_t stopwatch = malloc(sizeof(*stopwatch));

    stopwatch_restart(stopwatch);

    return (stopwatch_t) stopwatch;
}


void stopwatch_stop(stopwatch_t stopwatch) {
    free((_intern_stopwatch_t) stopwatch);
}


#if defined (__WIN32__) || defined (_WIN32)

void stopwatch_restart(stopwatch_t stopwatch) {
    QueryPerformanceCounter((LARGE_INTEGER*) stopwatch);
}

double stopwatch_gettime(stopwatch_t stopwatch) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start, stop;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&stop);
    start = * (_intern_stopwatch_t) stopwatch;

    return (stop.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}

#else

void stopwatch_restart(stopwatch_t stopwatch) {
    gettimeofday((timeval*) stopwatch, NULL);
}

double stopwatch_gettime(stopwatch_t stopwatch) {
    timeval start, stop;

    gettimeofday(&stop, NULL);
    start = *(_intern_stopwatch_t) stopwatch;

    return (stop.tv_sec - start.tv_sec) * 1000.0 + (stop.tv_usec - start.tv_usec) / 1000.0;
}

#endif
