# Faster Math Ops using MATHLIB


## TODO (*will vanish upon completion*)
* [ ] Brief Abstract
* [ ] Example Code Usage
* [ ] General Guidelines
* [ ] Effect of memory access latency


![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/raw/master/Faster%20Math%20Ops%20using%20MATHLIB/charts/opTypes.png)

### Example Code Usage

```c
#include <ti/mathlib/mathlib.h>

/* don't forget to include "ti/mathlib/lib/mathlib.lib" under ::
*
*   C6000 Linker > File Search Options > "ti/mathlib/lib/mathlib.lib"
*
*/

#define N 1024

const double arguments[N] = {0};
double sinusoids[N] = {0};

// void init_args(double *args, const size_t N);

int main(void) {

  // initialize arguments to something meaningful here, init_args is trivially implemented elsewhere
  init_args(arguments, N);

  // single - call vectorized operation, equivalent to sinusoids[i] = sin(arg[i]) from 0 to N-1
  sindp_v(arguments, sinusoids, N);

}
```

### General Guidelines

### Effect of memory access latency
