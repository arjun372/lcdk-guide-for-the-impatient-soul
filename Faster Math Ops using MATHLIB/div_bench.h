/*
 * div_bench.h
 *
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 *
 */

#ifndef DIV_BENCH_H_
#define DIV_BENCH_H_

#include <ti/mathlib/mathlib.h>
#include <math.h>

static void divDP_MATHLIB(void *arguments, void *outputs, const size_t N)
{
    size_t i;
    double *out = (double *) outputs;
    double *denominator = (double *) arguments;

    for(i = 0; i < N; i++)
    {
        out[i] = divdp(out[i], denominator[i]);
    }
}

static void divSP_MATHLIB(void *arguments, void *outputs, const size_t N)
{
    size_t i;
    float *out = (float *) outputs;
    float *denominator = (float *) arguments;

    for(i = 0; i < N; i++)
    {
        out[i] = divsp(out[i], denominator[i]);
    }
}


static void divSP_MATH(void *arguments, void *outputs, const size_t N)
{
    size_t i;
    float *out = (float *) outputs;
    float *denominator = (float *) arguments;

    for(i = 0; i < N; i++)
    {
        out[i] /= denominator[i];
    }
}

static void divDP_MATH(void *arguments, void *outputs, const size_t N)
{
    size_t i;
    double *out = (double *) outputs;
    double *denominator = (double *) arguments;

    for(i = 0; i < N; i++)
    {
        out[i] /= denominator[i];
    }
}

static void divSPVector_MATHLIB(void *arguments, void *outputs, const size_t N)
{
    float *args = (float *) arguments;
    float *out = (float *) outputs;
    divsp_v(out, args, out, N);
}

static void divDPVector_MATHLIB(void *arguments, void *outputs, const size_t N)
{
    double *args = (double *) arguments;
    double *out = (double *) outputs;
    divdp_v(out, args, out, N);
}


#endif /* DIV_BENCH_H_ */
