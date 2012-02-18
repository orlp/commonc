#include <stdio.h>
#include <math.h>
#include <windows.h>

#include "fastmath.h"
#include "stopwatch.h"

int main(int argc, char **argv) {
    stopwatch_t stopwatch;
    volatile double prevent_opti;
    double fastsin_time, sin_time;
    int i;
    double f;
    double avgerr, worsterr, relerr;

    /* time fast_sin*/
    stopwatch = stopwatch_start();
    for (i=0; i < 40; i++) {
        for (f = -FM_PI; f < FM_PI; f += 0.0001) {
            prevent_opti = fm_sin(f);
        }
    }
    fastsin_time = stopwatch_gettime(stopwatch);

    /* time sin */
    stopwatch_restart(stopwatch);
    for (i=0; i < 40; i++) {
        for (f = -FM_PI; f < FM_PI; f += 0.0001) {
            prevent_opti = sin(f);
        }
    }
    sin_time = stopwatch_gettime(stopwatch);
    stopwatch_stop(stopwatch);

    printf("Time fast_sin: %f\nTime sin: %f\n", fastsin_time, sin_time);

    /* error checking */
    avgerr = relerr = worsterr = 0.0f;
    i = 0;
    for (f = -FM_PI; f < FM_PI; f += 0.1) {
        i++;

        double err = fabsf(sinf(f) - fm_sinf(f));

        avgerr += err;
        if (fabsf(sinf(f)) > 0.000001) relerr += err / fabsf(sin(f)) * 100.0;

        if (err > worsterr) worsterr = err;
    }
    avgerr /= i;
    relerr /= i;

    printf("Worst error: %f\nAverage error: %f\nAverage relative error: %.2f%%", worsterr, avgerr, relerr);
    printf("Values on critical points:\nsin(0) = %f\nsin(pi/2) = %f\nsin(pi/6) = %f\nsin(pi) = %f\n", fm_sin_limrange(0), fm_sin_limrange(FM_PI/2), fm_sin_limrange(FM_PI/6), fm_sin_limrange(FM_PI));

    printf("%f\n", fm_copysignf(1.0f, 2.0f));
    printf("%f\n", fm_copysignf(-1.0f, 2.0f));
    printf("%f\n", fm_copysignf(1.0f, -2.0f));
    printf("%f\n", fm_copysignf(1.0f, 2.0f));


    return 0;
}
