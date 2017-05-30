# Simple µ-benchmark routines for the C6000

Included in the file `profiler.h` are timing functions that count clock-ticks, and as such can be used for creating small and effective benchmarks (with clock-cycle level accuracy) when profiling LCDK code. Cycle count is independent of clock frequency and therefore a better metric for work-done than elapsed time.

## **Usage Example**

```c
#include "profiler.h"

int main(void) {

  const clock_t start_time = getClock();

  function_to_run(); // DO SOME INTERESTING CALCULATIONS HERE

  const clock_t stop_time  = getClock();

  stats(stop_time, start_time);
}
```
#### Sample Output
```c
MEASURING OVERHEAD   : 2 cycles
CLOCKS PER SECOND    : 2000000 cycles
TOTAL CLOCKS CYCLES  : 9274010 cycles // MEASURING OVERHEAD has been subtracted already
```

## **Some trivially achievable optimizations**
* ### Linker file Usage
Memory access latency can be reduced by a few orders of magnitude by ensuring that the entire code resides in L2 SRAM, as opposed to the-much-slower shared external RAM. Refer to the provided linker file `linker_dsp.cmd`. ** Note : EE113D developers already use another variant of this file. May not see much performance improvement here.**

 Effect of memory access on compute performance can be seen in this example. // ** TODO **

* ### Note on Compiler Optimizations
Different compiler optimization levels may heavily influence the functioning of your code in unexpected ways, so be sure to stick to one level of optimization while iterating through your design. For reference, `Build Config - Release` in Code Composer Studio defaults to optimization level `O2`, whereas `Build Config - Debug` has all optimizations disabled.

## ** Further Reading **

Additional information on good benchmarking practices for the C6000 can be found in the TI provided file `benchmarks.pdf`, listed here.

<!-- The tradeoff here is that the LCDK exposes 256KB of L2 cache, and care must be taken to ensure that all code can fit into it. Luckily, statically declared code, if oversized, will throw an error during link-time in the build process. Dynamically allocated memory however, will only throw runtime errors, therefore care must be taken to ensure that the design accounts for this change in -->
