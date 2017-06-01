# Faster Math Ops using MATHLIB


## TODO (*will vanish upon completion*)
* [ ] Brief Abstract
* [ ] Example Code Usage
* [ ] General Guidelines
* [ ] Effect of memory access latency

## Including MATHLIB
An latest installer version of MATHLIB can be downloaded from [download from TI's software product webpage](http://software-dl.ti.com/sdoemb/sdoemb_public_sw/mathlib/latest/index_FDS.html). Alternatively, this repository also provides sources for `release 3.1.2.1`, `Build date: 05182016`, and is known to be working with CCS compiler v8.2.


## Function Reference
MATHLIB *(Release 3.1.2.1)* provides both double precision and single precision implementations for the functions listed below. Additional information can be found in the MATHLIB function reference file `MATHLIB_Reference.chm`, provided in this repo.

Here is a list of commonly used functions that MATHLIB provides efficient implementations for. **Note, this is not a list of function definitions**, (those can be found in the function reference file).
```c
* atan2(a,b)
* atan(a)
* cos(a)
* div(a,b)
* exp10(a)  
* exp2(a)
* exp(a)
* log10(a)  
* log2(a)
* log(a)
* pow(a,b)
* recip(a)  
* rsqrt(a)
* sin(a)
* sqrt(a)
```

### Vectorized Code :: Example Usage

MATHLIB also exposes a vectorized implementation for every function listed above. In nearly every case, vectorized implementations will outperform code that iterates over arrays. In this sense, their use is highly recommended.

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
## Benchmarks
![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/raw/master/Faster%20Math%20Ops%20using%20MATHLIB/charts/opTypes.png)

### General Guidelines

### Effect of memory access latency
