/*
 * main.c
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 */

#include <ti/mathlib/mathlib.h>
#include <math.h>

#include <string.h>

#include <stdlib.h>
//#include <time.h>

#include <profiler.h>

#include "sin_bench.h"
#include "div_bench.h"
#include "sqrt_bench.h"
#include "log10_bench.h"

#define N 1024
#define NUM_RUNS 1000
#define FLOAT_NOT_DOUBLE 0

#if FLOAT_NOT_DOUBLE
    static float a1[N] = {0};
    static float a2[N] = {0};
#else
    static double a1[N] = {0};
    static double a2[N] = {0};
#endif

static void init() {

    srand(time(NULL));

    // fill the two arrays with random values, as long as they are non-zero
    size_t i;
    for(i = 0; i < N; i++)
    {
      while(a1[i] != 0) a1[i] = rand();
      while(a2[i] != 0) a2[i] = rand();
    }

    printf("Array initialization complete...\n");
}

int main(void) {

    init();

    #if FLOAT_NOT_DOUBLE
        printf("Performing <float> benchmarks...\n");

        /** sin(x) **/
        runBenchmark("sinSP_math.h",    &sinSP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sinSP_MATHLIB",   &sinSP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sinSPVec_MATHLIB",&sinSPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** division **/
        runBenchmark("divSP_math.h",    &divSP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("divSP_MATHLIB",   &divSP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("divSPVec_MATHLIB",&divSPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** square-root **/
        runBenchmark("sqrtSP_math.h",    &sqrtSP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sqrtSP_MATHLIB",   &sqrtSP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sqrtSPVec_MATHLIB",&sqrtSPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** log_10(x) **/
        runBenchmark("log10SP_math.h",    &log10SP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("log10SP_MATHLIB",   &log10SP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("log10SPVec_MATHLIB",&log10SPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
    #else
        printf("Performing <double> benchmarks...\n");

        /** sin(x) **/
        runBenchmark("sinDP_math.h",    &sinDP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sinDP_MATHLIB",   &sinDP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sinDPVec_MATHLIB",&sinDPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** division **/
        runBenchmark("divDP_math.h",    &divDP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("divDP_MATHLIB",   &divDP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("divDPVec_MATHLIB",&divDPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** square-root **/
        runBenchmark("sqrtDP_math.h",    &sqrtDP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sqrtDP_MATHLIB",   &sqrtDP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("sqrtDPVec_MATHLIB",&sqrtDPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

        /** log_10(x) **/
        runBenchmark("log10DP_math.h",    &log10DP_MATH, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("log10DP_MATHLIB",   &log10DP_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);
        runBenchmark("log10DPVec_MATHLIB",&log10DPVector_MATHLIB, (void *) a2, (void *) a1, N, NUM_RUNS);

    #endif

	return 0;
}
