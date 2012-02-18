#ifndef STOPWATCH_H_GUARD
#define STOPWATCH_H_GUARD

typedef void* stopwatch_t;

stopwatch_t stopwatch_start();
void stopwatch_restart(stopwatch_t stopwatch);
double stopwatch_gettime(stopwatch_t stopwatch);
void stopwatch_stop(stopwatch_t stopwatch);

#endif /* STOPWATCH_H_GUARD */
