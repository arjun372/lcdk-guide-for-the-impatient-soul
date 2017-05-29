/*
 * sqrt_bench.h
 *
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 *
 */

#ifndef sqrt_BENCH_H_
#define sqrt_BENCH_H_

#include <ti/mathlib/mathlib.h>
#include <math.h>


static void sqrtDP_MATHLIB(void *arguments, void *outputs, const size_t N) {
    size_t i;

    double *out = (double *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = sqrtdp(i);
    }
}

static void sqrtSP_MATHLIB(void *arguments, void *outputs, const size_t N) {
    size_t i;

    float *out = (float *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = sqrtsp(i);
    }
}


static void sqrtSP_MATH(void *arguments, void *outputs, const size_t N) {
    size_t i;

    float *out = (float *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = (float) sqrtf(i);
    }
}

static void sqrtDP_MATH(void *arguments, void *outputs, const size_t N) {
    size_t i;
    double *out = (double *) outputs;

    for(i = 0; i < N; i++)
    {
       out[i] = sqrt(i);
    }
}

static void sqrtSPVector_MATHLIB(void *arguments, void *outputs, const size_t N) {
    float *args = (float *) arguments;
    float *out = (float *) outputs;
    sqrtsp_v(args, out, N);
}

static void sqrtDPVector_MATHLIB(void *arguments, void *outputs, const size_t N) {
    double *args = (double *) arguments;
    double *out = (double *) outputs;
    sqrtdp_v(args, out, N);
}


#endif /* sqrt_BENCH_H_ */
