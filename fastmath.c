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

#include <math.h>

#include "fastmath.h"

/*

    double cc_copysign(double a, double b);
    float cc_copysignf(float a, float b);

    Returns a with the sign of b.

*/

float cc_copysignf(float a, float b) {
    #ifdef NO_IEEE754
        return ((b > 0) - (b < 0)) * a;
    #else
        int *ai, *bi;

        ai = (int*) &a;
        bi = (int*) &b;

        *ai &= 0x7FFFFFFF;
        *ai |= (*bi) &0x80000000;

        return a;
    #endif
}

double cc_copysign(double a, double b) {
    #ifdef NO_IEEE754
        return ((b > 0) - (b < 0)) * a;
    #else
        int *ai, *bi;

        ai = (int*) &a;
        bi = (int*) &b;

        *ai &= 0x7FFFFFFF;
        *ai |= (*bi) &0x80000000;

        return a;
    #endif
}

/*

    double cc_sin(double x);
    double cc_sin_limrange(double x);
    float cc_sinf(float x);
    float cc_sinf_limrange(float x);

    Approximation of sin(x) by the formula f(x) = ax^5 + bx^3 + cx

    Constants chosen such that:

        f(pi/2) = 1
        f'(pi/2) = 0
        f(pi/6) = 1/2

    Resulting in:

        a =   9 / (4  * pi^5)
        b = -41 / (8  * pi^3)
        c = 201 / (64 * pi)

    Worst error: 0.000296
    Average error: 0.000124
    Average relative error: 0.02%

    The limrange version has valid range [-pi/2, pi/2], the others have full range.

*/

float cc_sinf_limrange(float x) {
    const float a =  0.00735246819687011731341356165096815f;
    const float b = -0.16528911397014738207016302002888890f;
    const float c =  0.99969198629596757779830113868360584f;

    float x2 = x * x;

    return x*(c + x2*(b + a*x2));
}

double cc_sin_limrange(double x) {
    const double a =  0.00735246819687011731341356165096815;
    const double b = -0.16528911397014738207016302002888890;
    const double c =  0.99969198629596757779830113868360584;

    double x2 = x * x;

    return x*(c + x2*(b + a*x2));
}

float cc_sinf(float x) {
    long k;

    /* bring x in range */
    k = (long) (CC_1_PI_F * x + cc_copysignf(0.5f, x));

    x -= k * CC_PI_F;

    x = cc_sinf_limrange(x);

    /* if x is in an odd pi count we must flip */
    x -= 2 * x * (k & 1); /* trick for x = (x % 2) == 0 ? x : -x; */

    return x;
}

double cc_sin(double x) {
    long k;

    /* find offset of x from the range -pi to pi */
    k = (long) (CC_1_PI * x + cc_copysign(0.5, x));

    /* bring x in range */
    x -= k * CC_PI;

    x = cc_sin_limrange(x);

    /* if x is in an odd pi count we must flip */
    x -= 2 * x * (k & 1); /* trick for r = (k % 2) == 0 ? r : -r; */

    return x;
}
