#include <stdio.h>
#include <math.h>

#include "fastmath.h"
#include "stopwatch.h"

int main(int argc, char **argv) {
    cc_stopwatch_t stopwatch;
    volatile double prevent_opti;
    double fastsin_time, sin_time;
    int i;
    double f;
    double avgerr, worsterr, relerr;

    /* time fast_sin*/
    cc_stopwatch_start(&stopwatch);
    for (i=0; i < 40; i++) {
        for (f = -CC_PI; f < CC_PI; f += 0.0001) {
            prevent_opti = cc_sin(f);
        }
    }
    fastsin_time = cc_stopwatch_gettime(&stopwatch);

    /* time sin */
    cc_stopwatch_start(&stopwatch);
    for (i=0; i < 40; i++) {
        for (f = -CC_PI; f < CC_PI; f += 0.0001) {
            prevent_opti = sin(f);
        }
    }
    sin_time = cc_stopwatch_gettime(&stopwatch);

    printf("Time fast_sin: %f\nTime sin: %f\n", fastsin_time, sin_time);

    /* error checking */
    avgerr = relerr = worsterr = 0.0f;
    i = 0;
    for (f = -CC_PI; f < CC_PI; f += 0.1) {
        i++;

        double err = fabsf(sinf(f) - cc_sinf(f));

        avgerr += err;
        if (fabsf(sinf(f)) > 0.000001) relerr += err / fabsf(sin(f)) * 100.0;

        if (err > worsterr) worsterr = err;
    }
    avgerr /= i;
    relerr /= i;

    printf("Worst error: %f\nAverage error: %f\nAverage relative error: %.2f%%\n", worsterr, avgerr, relerr);
    printf("Values on critical points:\nsin(0) = %f\nsin(pi/2) = %f\nsin(pi/6) = %f\nsin(pi) = %f\n", cc_sin_limrange(0), cc_sin_limrange(CC_PI/2), cc_sin_limrange(CC_PI/6), cc_sin_limrange(CC_PI));

    printf("%f\n", cc_copysignf(1.0f, 2.0f));
    printf("%f\n", cc_copysignf(-1.0f, 2.0f));
    printf("%f\n", cc_copysignf(1.0f, -2.0f));
    printf("%f\n", cc_copysignf(1.0f, 2.0f));


    return 0;
}
