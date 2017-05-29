/*
 * sin_bench.h
 *
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 *
 */

#ifndef SIN_BENCH_H_
#define SIN_BENCH_H_

#include <ti/mathlib/mathlib.h>
#include <math.h>


static void sinDP_MATHLIB(void *arguments, void *sinusoids, const size_t N) {
    size_t i;

    double *out = (double *) sinusoids;

    for(i = 0; i < N; i++)
    {
        out[i] = sindp(i);
    }
}

static void sinSP_MATHLIB(void *arguments, void *sinusoids, const size_t N) {
    size_t i;

    float *out = (float *) sinusoids;

    for(i = 0; i < N; i++)
    {
        out[i] = sinsp(i);
    }
}


static void sinSP_MATH(void *arguments, void *sinusoids, const size_t N) {
    size_t i;

    float *out = (float *) sinusoids;

    for(i = 0; i < N; i++)
    {
        out[i] = sinf(i);
    }
}

static void sinDP_MATH(void *arguments, void *sinusoids, const size_t N) {
    size_t i;
    double *out = (double *) sinusoids;

    for(i = 0; i < N; i++)
    {
       out[i] = sin(i);
    }
}

static void sinSPVector_MATHLIB(void *arguments, void *sinusoids, const size_t N) {
    float *args = (float *) arguments;
    float *out = (float *) sinusoids;
    sinsp_v(args, out, N);
}

static void sinDPVector_MATHLIB(void *arguments, void *sinusoids, const size_t N) {
    double *args = (double *) arguments;
    double *out = (double *) sinusoids;
    sindp_v(args, out, N);
}


#endif /* SIN_BENCH_H_ */
