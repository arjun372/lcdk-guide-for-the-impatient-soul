/****************************************************************************/
/*  OMAPL138.cmd                                                            */
/*  Copyright (c) 2010 Texas Instruments Incorporated                       */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the C compiler and  */
/*                 running the resulting .out file on an OMAPL138           */
/*                 device.  Use it as a guideline.  You will want to        */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/*    Usage:       The map below contains the local memory for each core    */
/*                 Use the linker option --define=DSP_CORE=n                */
/*                 Where n defines the core used: DSP (n=1) or ARM (n=0)    */
/*                                                                          */
/****************************************************************************/


//-l ../../../../../lib/mathlib.lib
/* linker_dsp.cmd */

-stack           0x00000800
-heap            0x00010000

MEMORY
{
	L2SRAM (RWX)  : org = 0x0800000, len = 0x080000
	MSMCSRAM (RWX): org = 0xc000000, len = 0x200000
}

SECTIONS
{
//	.kernel_asm: {mathlib*<*.o*> (.text:optasm) { SIZE(_kernel_asm_size) }}
//	.kernel_vec: {mathlib*<*.o*> (.text:optvec) { SIZE(_kernel_vec_size) }}
//	.kernel_ci:  {mathlib*<*.o*> (.text:optci) { SIZE(_kernel_ci_size) }}

	.text:			load >> L2SRAM
	.text:touch:	load >> L2SRAM

	GROUP (NEAR_DP)
	{
		.neardata
		.rodata
		.bss
	} load > L2SRAM

	.init_array: 	load >> L2SRAM
	.far: 			load >> L2SRAM
	.fardata: 		load >> L2SRAM
	.data: 			load >> L2SRAM
	.switch: 		load >> L2SRAM
	.stack: 		load > L2SRAM
	.args: 			load > L2SRAM align = 0x4, fill = 0 {_argsize = 0x200; }
	.sysmem: 		load > L2SRAM
	.cinit: 		load > L2SRAM
	.const: 		load > L2SRAM START(const_start) SIZE(const_size)
	.pinit: 		load > L2SRAM
	.cio: 			load >> L2SRAM
	xdc.meta: 		load >> L2SRAM, type = COPY
}
