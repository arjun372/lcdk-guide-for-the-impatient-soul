# Simple µ-benchmark routines for the C6000

Included in the file `profiler.h` are helper functions that provide clock-cycle level timing accuracy which can be used for creating small and effective benchmarks when profiling LCDK code. Cycle count is independent of clock frequency and therefore a better metric for work-done than elapsed time.

## Usage Example

```c
#include "profiler.h"

int main(void) {

  clock_t start_time = getClock();

  function_to_run(); // DO SOME INTERESTING CALCULATIONS HERE

  clock_t stop_time  = getClock();

  stats(stop_time, start_time);
}

```
#### Sample Output

```c
MEASURING OVERHEAD   : 2 cycles
CLOCKS PER SECOND    : 2000000 cycles
TOTAL CLOCKS CYCLES  : 9274010 cycles
```

### Note on compiler optimization
Different compiler optimization levels may heavily influence the functioning of your code in unexpected ways, so be sure to stick to one level of optimization while iterating through your design. For reference, `Build Config - Release` in Code Composer Studio defaults to optimization level `O2`, whereas `Build Config - Debug` has all optimizations disabled.
