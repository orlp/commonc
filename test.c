#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "commonc/math.h"
#include "commonc/stopwatch.h"

#define assert(e) ((e) ? (void) 0 : _assert(#e, __FILE__, __LINE__))

void _assert(const char* statement, const char* file, int line) {
    printf("Assertion failed: %s, file %s, line %d", statement, file, line);
    exit(1);
}


int main(int argc, char **argv) {
    int i;
    double d;
    float f;
    double avgerr, worsterr, relerr;
    volatile double prevent_opti;
    cc_stopwatch_t timer;


    /* cc_sin test */
    printf("Testing cc_sin\n");

    /* performance check */
    {
        cc_stopwatch_start(&timer);
        for (i = 0; i < 10000; i++) {
            for (d = -16*CC_PI; d < 16*CC_PI; d += 0.1) {
                prevent_opti = cc_sin(d);
            }
        }
        printf("cc_sin time: %f\n", cc_stopwatch_gettime(&timer));

        cc_stopwatch_start(&timer);
        for (i = 0; i < 10000; i++) {
            for (d = -16*CC_PI; d < 16*CC_PI; d += 0.1) {
                prevent_opti = sin(d);
            }
        }
        printf("sin time: %f\n", cc_stopwatch_gettime(&timer));
    }

    /* accuracy check */
    {
        avgerr = relerr = worsterr = 0.0;
        i = 0;
        for (d = -4*CC_PI; d < 4*CC_PI; d += 0.001) {
            i++;

            double err = fabs(sin(d) - cc_sin(d));

            avgerr += err;
            if (fabs(sin(d)) > 0.000001) relerr += err / fabsf(sin(d)) * 100.0;

            if (err > worsterr) worsterr = err;
        }
        avgerr /= i;
        relerr /= i;

        printf("Worst error: %f\nAverage error: %f\nAverage relative error: %.2f%%\n", worsterr, avgerr, relerr);

        assert(fabs(cc_sin(0) - 0.0) < 0.000000001);
        assert(fabs(cc_sin(CC_PI/2) - 1.0) < 0.000000001);
        assert(fabs(cc_sin(CC_PI/6) - 0.5) < 0.000000001);
        assert(fabs(cc_sin(CC_PI) - 0.0) < 0.000000001);
    }

    /* cc_sinf test */
    printf("\nTesting cc_sinf\n");

    /* performance check */
    {
        cc_stopwatch_start(&timer);
        for (i = 0; i < 10000; i++) {
            for (f = -16*CC_PI_F; f < 16*CC_PI_F; f += 0.1f) {
                prevent_opti = cc_sinf(f);
            }
        }
        printf("cc_sinf time: %f\n", cc_stopwatch_gettime(&timer));

        cc_stopwatch_start(&timer);
        for (i = 0; i < 10000; i++) {
            for (f = -16*CC_PI_F; f < 16*CC_PI_F; f += 0.1f) {
                prevent_opti = sinf(f);
            }
        }
        printf("sinf time: %f\n", cc_stopwatch_gettime(&timer));
    }

    /* accuracy check */
    {
        avgerr = relerr = worsterr = 0.0;
        i = 0;
        for (d = -4*CC_PI; d < 4*CC_PI; d += 0.001) {
            i++;

            double err = fabs(sinf(d) - cc_sinf(d));

            avgerr += err;
            if (fabs(sin(d)) > 0.000001) relerr += err / fabsf(sin(d)) * 100.0;

            if (err > worsterr) worsterr = err;
        }
        avgerr /= i;
        relerr /= i;

        printf("Worst error: %f\nAverage error: %f\nAverage relative error: %.2f%%\n", worsterr, avgerr, relerr);


        assert(fabs(cc_sinf(0) - 0.0) < 0.0000001);
        assert(fabs(cc_sinf(CC_PI/2) - 1.0) < 0.0000001);
        assert(fabs(cc_sinf(CC_PI/6) - 0.5) < 0.0000001);
        assert(fabs(cc_sinf(CC_PI) - 0.0) < 0.0000001);
    }

    (void)prevent_opti;

    return 0;
}
