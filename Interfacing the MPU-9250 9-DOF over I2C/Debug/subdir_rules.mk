################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
i2c.obj: ../i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/c674x/c6748" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/hw" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/" --include_path="C:/ti/dsplib_c674x_3_4_0_0/packages" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="i2c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2cLedBlink.obj: ../i2cLedBlink.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/c674x/c6748" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/hw" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/" --include_path="C:/ti/dsplib_c674x_3_4_0_0/packages" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="i2cLedBlink.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

interrupt.obj: ../interrupt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/c674x/c6748" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/hw" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/" --include_path="C:/ti/dsplib_c674x_3_4_0_0/packages" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="interrupt.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

intvecs.obj: ../intvecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6740 --abi=coffabi -g --include_path="C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/c674x/c6748" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/hw" --include_path="C:/ti/C6748_StarterWare_1_20_04_01/include/" --include_path="C:/ti/dsplib_c674x_3_4_0_0/packages" --define=omapl138 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="intvecs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


