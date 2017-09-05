################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 --include_path="/home/arjun/workspace_v7/DSPLIB_FFT" --include_path="/opt/ti/dsplib_c674x_3_4_0_0/packages/" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


