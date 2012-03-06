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

#include "commonc/config.h"
#include "commonc/math.h"
#include "commonc/endian.h"
#include "commonc/integer.h"

/* Returns the larger of a and b. */

int cc_max(int a, int b) {
    if (a > b) return a;
    return b;
}


long cc_maxl(long a, long b) {
    if (a > b) return a;
    return b;
}


long long cc_maxll(long long a, long long b) {
    if (a > b) return a;
    return b;
}


unsigned int cc_maxu(unsigned int a, unsigned int b) {
    if (a > b) return a;
    return b;
}


unsigned long cc_maxul(unsigned long a, unsigned long b) {
    if (a > b) return a;
    return b;
}


unsigned long long cc_maxull(unsigned long long a, unsigned long long b) {
    if (a > b) return a;
    return b;
}


double cc_fmax(double a, double b) {
    if (a > b) return a;
    return b;
}


float cc_fmaxf(float a, float b) {
    if (a > b) return a;
    return b;
}

/*

    int cc_copysign(int a, int b);
    long cc_copysignl(long a, long b);
    long long cc_copysignll(long long a, long long b);
    double cc_fcopysign(double a, double b);
    float cc_fcopysignf(float a, float b);

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

inline long long cc_copysignll(long long a, long long b) {
    #ifdef CC_NO_BRANCH
    return ((b > 0) - (b < 0)) * a;
    #else
    if (!b) return 0;
    if ((a ^ b) < 0) a = -a;

    return a;
    #endif
}


inline double cc_fcopysign(double a, double b) {
    /*#ifdef CC_IEEE754
    union {
        double d;
        uint64_t l;

        #ifdef CC_LITTLE_ENDIAN
        struct {
            uint32_t lw;
            uint32_t hw;
        };
        #else
        struct {
            uint32_t hw;
            uint32_t lw;
        };
        #endif
    } al, bl;

    al.d = a;
    bl.d = b;

    al.hw &= 0x7FFFFFFF;
    al.hw |= bl.hw & 0x80000000;

    return al.d;
    #else*/

    return ((b > 0) - (b < 0)) * a;

    /*#endif*/
}


inline float cc_fcopysignf(float a, float b) {
    /*#ifdef CC_IEEE754
    union {
        float f;
        uint32_t i;
    } ai, bi;

    ai.f = a;
    bi.f = b;

    ai.i &= 0x7FFFFFFF;
    ai.i |= bi.i & 0x80000000;

    return ai.f;
    #else*/

    return ((b > 0) - (b < 0)) * a;

    /*#endif*/
}


int cc_sign(int x) {
    return (x > 0) - (x < 0);
}


int cc_signl(long x) {
    return (x > 0) - (x < 0);
}


int cc_signll(long long x) {
    return (x > 0) - (x < 0);
}


int cc_fsign(double x) {
    return (x > 0.0) - (x < 0.0);
}


int cc_fsignf(float x) {
    return (x > 0.0f) - (x < 0.0f);
}




/*
    Returns the absolute value of x (always positive)
*/




int cc_abs(int x) {
    if (x < 0) x = -x;

    return x;
}


long cc_absl(long x) {
    if (x < 0) x = -x;

    return x;
}


long long cc_absll(long long x) {
    if (x < 0) x = -x;

    return x;
}


float cc_fabsf(float x) {
    if (x < 0.0f) x = -x;

    return x;
}


double cc_fabs(double x) {
    if (x < 0.0) x = -x;

    return x;
}


/*

    long cc_round(double x);
    long cc_roundf(float x);

    Rounds x to the nearest integer (both negative and positive). Warning, this _may_ use "banker" rounding, that means 0.5 doesn't always get rounded up, instead if gets rounded to the nearest even integer. Note the _may_, if either CC_IEEE754 or CC_DOUBLE_PREC is not defined than it uses regular up-rounding. This version can be many times faster that simply casting to long.

*/


long cc_round(double x) {
    #if defined(CC_IEEE754) && defined(CC_DOUBLE_PREC)
    const double magic_round = 6755399441055744.0; /* http://stereopsis.com/sree/fpu2006.html */

    union {
        double d;

        struct {
            #ifdef CC_LITTLE_ENDIAN
            uint32_t lw;
            uint32_t hw;
            #else
            uint32_t hw;
            uint32_t lw;
            #endif
        };
    } bit_hack;

    bit_hack.d = x;
    bit_hack.d += magic_round;

    return bit_hack.lw;

    #else

    return (long) (x + cc_fcopysign(0.5, x));

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

    /* find offset of x from the range -pi to pi */
    k = cc_round(CC_1_PI_F * x);

    /* bring x into range */
    x -= k * CC_PI_F;

    /* calculate sine */
    x = cc_sinf_limrange(x);

    /* if x is in an odd pi count we must flip */
    #ifdef CC_NO_BRANCH
    x *= (1 - 2 * (k & 1));
    #else
    if (k & 1) x = -x;
    #endif

    return x;
}


inline double cc_sin(double x) {
    long k;

    /* find offset of x from the range -pi to pi */
    k = cc_round(CC_1_PI * x);

    /* bring x into range */
    x -= k * CC_PI;

    /* calculate sine */
    x = cc_sin_limrange(x);

    /* if x is in an odd pi count we must flip */
    #ifdef CC_NO_BRANCH
    x *= (1 - 2 * (k & 1));
    #else
    if (k & 1) x = -x;
    #endif

    return x;
}
