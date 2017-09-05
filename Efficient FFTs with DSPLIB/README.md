# Efficient FFTs with DSPLIB

## Scope


## Prerequisites
- DSPLIB v.xxx
-

#

## Limitations
MATHLIB was designed with performance in mind, and as such, makes a trade-off between accuracy and execution speed. In terms of level of accuracy, not all functions are created equal, so be sure to inspect the input and output-error-tolerance ranges for each function in the function reference file `MATHLIB_Function_Reference.chm`.

## Installation Guide
The latest installer version of MATHLIB can be downloaded from <a  href="http://software-dl.ti.com/sdoemb/sdoemb_public_sw/mathlib/latest/index_FDS.html" target="_blank">TI's software product webpage</a>. Download the appropriate installer for your platform (Windows & Linux supported) and follow the instructions that the installer provides. Next, restart Code Composer Studio once the installation is complete, at which point CCS will auto-discover the newly installed library.

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

### Example Usage & Walk Thru

We can use the provided libraries
MATHLIB also exposes a vectorized implementation for every function listed above. In nearly every case, vectorized implementations will outperform code that iterates over arrays. In this sense, their use is highly recommended.

```c

#include <stdio.h>
#include <ti/mathlib/mathlib.h>

/* don't forget to include "ti/mathlib/lib/mathlib.lib" under ::
*
*   C6000 Linker > File Search Options > "ti/mathlib/lib/mathlib.lib"
*
*/
#include <stdint.h>
#include <math.h>
#include <ti/dsplib/dsplib.h>

/* Global definitions */
/* Number of samples for which FFT needs to be calculated */
#define N 256
/* Number of unique sine waves in input data */
#define NUM_SIN_WAVES 4

/* Align the tables that we have to use */
#pragma DATA_ALIGN(x_ref, 8);
float   x_ref [2*N];

#pragma DATA_ALIGN(x_sp, 8);
float   x_sp [2*N];
#pragma DATA_ALIGN(y_sp, 8);
float   y_sp [2*N];
#pragma DATA_ALIGN(w_sp, 8);
float   w_sp [2*N];

unsigned char brev[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};

/*  
    This function generates the input data and also updates the
    input data arrays used by the various FFT kernels
*/
void generateInput (int numSinWaves) {
    int   i, j;
    float sinWaveIncFreq, sinWaveMag;

    /*
        Based on numSinWave information, create the input data. The
        input data is first created using floating point dataType. The
        floating point data type is then converted to the appropriate
        fixed point notation
    */

    /* Clear the input floating point array */
    for (i = 0; i < N; i++) {
        x_ref[2*i]   = (float)0.0;      
        x_ref[2*i+1] = (float)0.0;  
    }

    /* Calculate the incremental freq for each sin wave */
    sinWaveIncFreq = ((float)3.142)/(numSinWaves*(float)1.0);

    /* Calculate the magnitude for each sin wave */
    sinWaveMag = (float)1.0/(numSinWaves * (float)1.0*N);

    /* Create the input array as sum of the various sin wave data */
    for (j = 0; j < numSinWaves; j++) {
        for (i = 0; i < N; i++) {
            x_ref[2*i]  += sinWaveMag * (float)cos(sinWaveIncFreq*j*i);        
            x_ref[2*i+1] = (float) 0.0;
        }
    }

    /* Copy the reference input data to the various input arrays */     
    for (i = 0; i < N; i++) {
        x_sp [2*i]   = x_ref[2*i];
        x_sp [2*i+1] = x_ref[2*i+1];
    }
}

/*
    The seperateRealImg function seperates the real and imaginary data
    of the FFT output. This is needed so that the data can be plotted
    using the CCS graph feature
*/

float y_real_sp [N];
float y_imag_sp [N];

seperateRealImg () {
    int i, j;

    for (i = 0, j = 0; j < N; i+=2, j++) {
        y_real_sp[j] = y_sp[i];
        y_imag_sp[j] = y_sp[i + 1];
    }
}

/*
    The main function that implements the example functionality.
    This example demonstrates the usage of the various FFT kernels provided
    with the C6x DSPLIB. The example shows:
        - Twiddle factor generation for the various kernels
        - Needed scaling to get correct output
        - Demonstrates usage of FFT APIs
*/

/* Function for generating Specialized sequence of twiddle factors */
void gen_twiddle_fft_sp (float *w, int n)
{
    int i, j, k;
    double x_t, y_t, theta1, theta2, theta3;
    const double PI = 3.141592654;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
            theta1 = 2 * PI * i / n;
            x_t = cos (theta1);
            y_t = sin (theta1);
            w[k] = (float) x_t;
            w[k + 1] = (float) y_t;

            theta2 = 4 * PI * i / n;
            x_t = cos (theta2);
            y_t = sin (theta2);
            w[k + 2] = (float) x_t;
            w[k + 3] = (float) y_t;

            theta3 = 6 * PI * i / n;
            x_t = cos (theta3);
            y_t = sin (theta3);
            w[k + 4] = (float) x_t;
            w[k + 5] = (float) y_t;
            k += 6;
        }
    }
}

void main () {
    /* Generate the input data */
    generateInput (NUM_SIN_WAVES);

    /* Genarate twiddle factors */
    gen_twiddle_fft_sp(w_sp, N);

    /* Call FFT routine */
    DSPF_sp_fftSPxSP(N, x_sp, w_sp, y_sp, brev, 4, 0, N);

    /* Call the test code to seperate the real and imaginary data */
    seperateRealImg ();
}

```

## Limitations

Assumptions:
N needs to be power of 2
8 <= N <= 131072
Arrays pointed by ptr_x, ptr_w, and ptr_y should not overlap
Arrays pointed by ptr_x, ptr_w, and ptr_y should align on the double words boundary

## Performance Benchmarks
As a performance comparison, I wrote some benchmarks that compare MATHLIB with TI compiler provided `math.h` files. I've included all the source code needed to re-create this benchmark in this repo. In addition, raw-output values for this benchmark can be found in <a  href="https://docs.google.com/spreadsheets/d/1LWCkFIS9CJ5wdWN-qmfmCOh9VeTmIPtO3nftIYkhErU/edit?usp=sharing" target="_blank">this Google Sheets</a> document.


![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/raw/master/Faster%20Math%20Ops%20using%20MATHLIB/charts/opTypes.png)
*Note: the MATHLIB provided divide operation does not perform as well as the standard division operation (for C6000 compiler v8.2 atleast)*.  
