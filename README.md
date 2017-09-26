# Performance oriented design on the LCDK

*** Please refer to the individual folders above. ***

## TODO (*will vanish upon completion*)
* [ ] System Overview
* [x] µ-benchmark tutorial
* [x] Faster Math Ops with MATHLIB
* [x] Efficient FFTs with DSPLIB
* [x] Optimizing Neural Nets using DSPLIB
* [ ] Interfacing a 9-DOF over I2C
* [ ] Running Linux on the LCDK


## Goals for this guide
* Write trivially reproducible code
* Groundwork for creating a collaborative toolkit for EE113D folk
* Exploring LCDK system capabilities & limitations
* Sharing lessons learned
* Introduction to performance oriented design
* Good design practices for low-memory, high-compute capability devices


// ** IN PROGRESS **
## Brief System Overview
|               |   OMAP L138  |  C6748 Float  |   PRU (x2)   |
|:-------------:|:------------:|:-------------:|:------------:|
|  Architecture |     ARM      |    TI - DSP   | generic 32bit RISC  |
|  Clock Freq.  | 456MHz  |  456MHz | 150 MHz |
|  C - Compiler     |   |   | **none** *(assembly only)* |
|  Assembler    ||   |   |   
|    ~FLOPs      |||||
