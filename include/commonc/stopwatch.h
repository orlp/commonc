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

#ifndef CC_STOPWATCH_H_GUARD
#define CC_STOPWATCH_H_GUARD

/* prevent namespace pollution, use own definitions of timeval and LARGE_INTEGER */

#if defined (__WIN32__) || defined (_WIN32)

typedef union {
    struct {
        unsigned long LowPart;
        long HighPart;
    };
    struct {
        unsigned long LowPart;
        long HighPart;
    } u;

#if !defined(_M_IX86)
    long long QuadPart;
#else
    double QuadPart;
#endif

} cc_stopwatch_t;

#else /* defined (__WIN32__) || defined (_WIN32) */

typedef struct {
    long tv_sec;
    long tv_usec;
} cc_stopwatch_t;

#endif

void cc_stopwatch_start(cc_stopwatch_t* stopwatch);
double cc_stopwatch_gettime(cc_stopwatch_t* stopwatch);

#endif /* CC_STOPWATCH_H_GUARD */
