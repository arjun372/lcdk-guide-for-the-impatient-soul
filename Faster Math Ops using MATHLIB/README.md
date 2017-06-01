# Faster Math Ops using MATHLIB


## TODO (*will vanish upon completion*)
* [ ] Brief Abstract
* [ ] Example Code Usage
* [ ] General Guidelines
* [ ] Effect of memory access latency

## Including MATHLIB
MATHLIB is acquired under license from TI, and therefore cannot be provided freely here. It can be downloaded from TI's website after agreeing to their terms and conditions. 


## Function Reference
MATHLIB *(Release 3.0.1.1)* provides implementations to the functions listed below. Additional information can be found in the MATHLIB function reference file `MATHLIB_Reference.chm`, provided in this repo.

Here is a list of all modules:
```c
* double atan2dp(double a,  double b) : returns the arc tangent of a floating-point argument a/b. The return value is an angle in the range [-PI/2, PI/2] radians
* Atandp  
* Cosdp
* Divdp
* Exp10dp  
* Exp2dp
* Expdp
* Log10dp  
* Log2dp
* Logdp
* Powdp
* Recipdp  
* Rsqrtdp
* Sindp
* Sqrtdp  
```

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
## Benchmarks
![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/raw/master/Faster%20Math%20Ops%20using%20MATHLIB/charts/opTypes.png)

### General Guidelines

### Effect of memory access latency
