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
