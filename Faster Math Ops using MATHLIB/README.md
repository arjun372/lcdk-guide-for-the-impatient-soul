# Faster Math Ops using MATHLIB
## Limitations
MATHLIB was designed with performance in mind, and as such, makes a trade-off between accuracy and execution speed. In terms of level of accuracy, not all functions are created equal, so be sure to inspect the input and output-error-tolerance ranges for each function in the function reference file `MATHLIB_Function_Reference.chm`.

## Installation Guide
The latest installer version of MATHLIB can be downloaded from [TI's software product webpage](http://software-dl.ti.com/sdoemb/sdoemb_public_sw/mathlib/latest/index_FDS.html). Download the appropriate installer for your platform (Windows & Linux supported) and follow the instructions that the installer provides. Next, restart Code Composer Studio once the installation is complete, at which point CCS will auto-discover the newly installed library.

Alternatively, this repository also provides sources for `release 3.1.2.1`, which can be found in folder named `mathlib_c674x_3_1_2_1`.

### Including MATHLIB
Regardless of whether or not it was installed using the installer binary (above), MATHLIB can be trivially added to any C/C++ project on any platform as long as all the source files and statically linked libraries are provided at compile-time.

1. Add `mathlib_c674x_3_1_2_1/packages` to INCLUDE PATH
2. Add file `mathlib_c674x_3_1_2_1/packages/ti/mathlib/lib/mathlib.lib` to LINKER PATH

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

#include <stdio.h>
#include <ti/mathlib/mathlib.h>

/* don't forget to include "ti/mathlib/lib/mathlib.lib" under ::
*
*   C6000 Linker > File Search Options > "ti/mathlib/lib/mathlib.lib"
*
*/

#define N 1024

extern void init_args(double *angles, const size_t len);

int main(void) {

  size_t i;
  double angles[N] = {0};

  // initialize angles to something meaningful here, init_args is trivially implemented elsewhere
  init_args(angles, N);

  // typical usage for MATHLIB sindp (dp: double precision)
  double sin_arr[N] = {0};
  for(i = 0; i < N; i++)
  {
    sin_arr[i] = sindp(angles[i]);
  }

  // single-call vectorized operation, equivalent to for-loop above, just faster
  double sin_vec[N] = {0};
  sindp_v(angles, sin_vec, N);

  // do a quick sanity check here
  for(i = 0; i < N; i++)
  {
    if(sin_arr[i] != sin_vec[i])
    {
      fprintf(stderr, "array & vector values don't match for angle: %f\n", angles[i]);
    }
  }

}
```
## Performance Benchmarks
As a performance comparison, I wrote some benchmarks that compare MATHLIB with TI compiler provided `math.h` files. I've included all the source code needed to re-create this benchmark in this repo. In addition, raw-output values for this benchmark can be found in [this Google Sheets ](https://docs.google.com/spreadsheets/d/1LWCkFIS9CJ5wdWN-qmfmCOh9VeTmIPtO3nftIYkhErU/edit?usp=sharing)document.

![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/raw/master/Faster%20Math%20Ops%20using%20MATHLIB/charts/opTypes.png)
*Note: the MATHLIB provided divide operation does not perform as well as the standard division operation (for C6000 compiler v8.2 atleast)*.  
