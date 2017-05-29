/*
 * profiler.h
 *
 *  Created on: May 28, 2017
 *      Author: Arjun <arjun372@g.ucla.edu>
 *
 * Usage ::
 *
 *          clock_t start_time = getCurrentClockCount();
 *
 *          << DO INTERESTING CALCULATIONS/WORK HERE >>
 *
 *          clock_t stop_time  = getCurrentClockCount();
 *
 *          printStats(stop_time, start_time);
 *
 */

#ifndef PROFILER_H_
#define PROFILER_H_

#include <c6x.h>
#include <time.h>
#include <stdio.h>

/**
 * Returns the current clock count
 */
static clock_t getCurrentClockCount() {
    const clock_t now = _itoll(TSCH, TSCL);
    return now;
}

/**
 * @return The number of clock cycles it takes to compute the number of clock cycles elapsed
 */
static clock_t computeTimingOverhead() {

    /* Initialize timer for clock by setting C6748 registers TSCL & TSCH to 0 */
    TSCL= 0,TSCH=0;

    /* Compute the overhead of calling _itoll(TSCH, TSCL) twice to get timing info */
    const clock_t t_start = _itoll(TSCH, TSCL);
    const clock_t t_stop = _itoll(TSCH, TSCL);
    const clock_t t_overhead = t_stop - t_start;

    return t_overhead;
}

/**
 * Computes the elapsed clock cycles between start & stop times, taking into account the number
 * of clock cycles it takes to count clock cycles.
 */
static clock_t getElapsedCycles(const clock_t stop, const clock_t start) {
    const clock_t counting_overhead = computeTimingOverhead();
    return stop - start - counting_overhead;
}

/**
 *
 */
static double getElapsedTimeMs(const clock_t stop, const clock_t start) {
    const double diffticks = getElapsedCycles(stop, start);
    const double diffms = (diffticks) / (double) (CLOCKS_PER_SEC / 1000);
    return diffms;
}

/**
 * Prints the timing statistics to stdout
 */
static void printStats(const clock_t stop, const clock_t start) {

    const clock_t OVERHEAD = computeTimingOverhead();
    const clock_t TOTAL_CLOCKS = getElapsedCycles(stop, start);
    const double ELAPSED_MS = getElapsedTimeMs(stop, start);

    fprintf(stdout, "CLOCKS_PER_SEC       : %d cycles\n", CLOCKS_PER_SEC);
    fprintf(stdout, "CLOCKING_OVERHEAD    : %d cycles\n", OVERHEAD);
    fprintf(stdout, "TOTAL_CLOCKS_CYCLES  : %d cycles\n", TOTAL_CLOCKS);
    fprintf(stdout, "TOTAL_TIME_MILLISEC  : %f ms\n",     ELAPSED_MS);
    fflush(stdout);
}

/**
 * Prints the timing statistics to stdout, including the function name
 */
static void printRunStats(const char* func, const clock_t stop, const clock_t start) {
    fprintf(stdout, "\n------------%s------------\n", func);
    printStats(stop, start);
}

static void runBenchmark(const char* func, void (*functionPtr) (void *, void *, const size_t), void *arg1, void *arg2, const size_t N, const size_t RUNS) {

    size_t i;

    const clock_t start = getCurrentClockCount();

    for(i = 0; i < RUNS; i++)
    {
        (*functionPtr)((void *) arg1, (void *) arg2, N);
    }

    const clock_t stop = getCurrentClockCount();

    printRunStats(func, stop, start);
}

#endif /* PROFILER_H_ */
