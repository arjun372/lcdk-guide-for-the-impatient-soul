/*
 * log10_bench.h
 *
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 *
 */

#ifndef log10_BENCH_H_
#define log10_BENCH_H_

#include <ti/mathlib/mathlib.h>
#include <math.h>


static void log10DP_MATHLIB(void *arguments, void *outputs, const size_t N) {
    size_t i;

    double *out = (double *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = log10dp(i);
    }
}

static void log10SP_MATHLIB(void *arguments, void *outputs, const size_t N) {
    size_t i;

    float *out = (float *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = log10sp(i);
    }
}


static void log10SP_MATH(void *arguments, void *outputs, const size_t N) {
    size_t i;

    float *out = (float *) outputs;

    for(i = 0; i < N; i++)
    {
        out[i] = (float) log10f(i);
    }
}

static void log10DP_MATH(void *arguments, void *outputs, const size_t N) {
    size_t i;
    double *out = (double *) outputs;

    for(i = 0; i < N; i++)
    {
       out[i] = log10(i);
    }
}

static void log10SPVector_MATHLIB(void *arguments, void *outputs, const size_t N) {
    float *args = (float *) arguments;
    float *out = (float *) outputs;
    log10sp_v(args, out, N);
}

static void log10DPVector_MATHLIB(void *arguments, void *outputs, const size_t N) {
    double *args = (double *) arguments;
    double *out = (double *) outputs;
    log10dp_v(args, out, N);
}


#endif /* log10_BENCH_H_ */
