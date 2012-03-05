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

#include "math.h"
#include "config.h"

/*

    int cc_copysign(int a, int b);
    long cc_copysignl(long a, long b);
    float cc_fcopysignf(float a, float b);
    double cc_fcopysign(double a, double b);

    Returns a with the sign of b.

*/


inline int cc_copysign(int a, int b) {
    #ifdef CC_NO_BRANCH
        return ((b > 0) - (b < 0)) * a;
    #else
        if (!b) return 0;
        if ((a ^ b) < 0) a = -a;

        return a;
    #endif
}


inline long cc_copysignl(long a, long b) {
    #ifdef CC_NO_BRANCH
        return ((b > 0) - (b < 0)) * a;
    #else
        if (!b) return 0;
        if ((a ^ b) < 0) a = -a;

        return a;
    #endif
}


inline float cc_fcopysignf(float a, float b) {
    #ifdef CC_NO_IEEE754
        return ((b > 0) - (b < 0)) * a;
    #else
        union {
            float f;
            int i;
        } ai, bi;

        ai.f = a;
        bi.f = b;

        ai.i &= 0x7FFFFFFF;
        ai.i |= bi.i & 0x80000000;

        return ai.f;
    #endif
}


inline double cc_fcopysign(double a, double b) {
    #ifdef CC_NO_IEEE754
        return ((b > 0) - (b < 0)) * a;
    #else
        union {
            double d;
            long l;
        } al, bl;

        al.d = a;
        bl.d = b;

        al.l &= 0x7FFFFFFFFFFFFFFF;
        al.l |= bl.l & 0x8000000000000000;

        return al.d;
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


inline float cc_sinf_limrange(float x) {
    const float a =  0.00735246819687011731341356165096815f;
    const float b = -0.16528911397014738207016302002888890f;
    const float c =  0.99969198629596757779830113868360584f;

    float x2 = x * x;

    return x*(c + x2*(b + a*x2));
}


inline double cc_sin_limrange(double x) {
    const double a =  0.00735246819687011731341356165096815;
    const double b = -0.16528911397014738207016302002888890;
    const double c =  0.99969198629596757779830113868360584;

    double x2 = x * x;

    return x*(c + x2*(b + a*x2));
}


inline float cc_sinf(float x) {
    long k;

    #ifndef CC_NO_IEEE754
    union {
        double d;
        long i;
    } dtoi_hack;
    #endif

    /* find offset of x from the range -pi to pi */
    #ifdef CC_NO_IEEE754
    k = (long) (CC_1_PI_F * x + cc_fcopysignf(0.5f, x));
    #else
    dtoi_hack.d = (double) (CC_1_PI_F * x) + 103079215104.5;
    k = dtoi_hack.i >> 16;
    #endif

    /* bring x into range */
    x -= k * CC_PI_F;

    /* calculate sine */
    x = cc_sinf_limrange(x);

    /* if x is in an odd pi count we must flip */
    x -= (2 * (k & 1)) * x; /* trick for x = (k % 2) == 0 ? x : -x; */

    return x;
}


inline double cc_sin(double x) {
    long k;

    #ifndef CC_NO_IEEE754
    union {
        double d;
        long i;
    } dtoi_hack;
    #endif

    /* find offset of x from the range -pi to pi */
    #ifdef CC_NO_IEEE754
    k = (long) (CC_1_PI * x + cc_fcopysign(0.5, x));
    #else
    dtoi_hack.d = CC_1_PI * x + 103079215104.5;
    k = dtoi_hack.i >> 16;
    #endif

    /* bring x into range */
    x -= k * CC_PI;

    /* calculate sine */
    x = cc_sin_limrange(x);

    /* if x is in an odd pi count we must flip */
    x -= (2 * (k & 1)) * x; /* trick for x = (k % 2) == 0 ? x : -x; */

    return x;
}
