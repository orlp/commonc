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
    double f;
    double avgerr, worsterr, relerr;

    /* error checking */
    avgerr = relerr = worsterr = 0.0f;
    i = 0;
    for (f = -CC_PI; f < CC_PI; f += 0.0001) {
        i++;

        double err = fabs(sin(f) - cc_sin(f));

        avgerr += err;
        if (fabsf(sinf(f)) > 0.000001) relerr += err / fabsf(sin(f)) * 100.0;

        if (err > worsterr) worsterr = err;
    }
    avgerr /= i;
    relerr /= i;

    printf("Worst error: %f\nAverage error: %f\nAverage relative error: %.2f%%\n", worsterr, avgerr, relerr);
    printf("Values on critical points:\nsin(0) = %f\nsin(pi/2) = %f\nsin(pi/6) = %f\nsin(pi) = %f\n", cc_sin(0), cc_sin(CC_PI/2), cc_sin(CC_PI/6), cc_sin(CC_PI));

    return 0;
}
