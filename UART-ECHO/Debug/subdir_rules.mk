################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DSPF_sp_mat_mul.obj: ../DSPF_sp_mat_mul.s $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DSPF_sp_mat_mul.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSPF_sp_mat_mul_cn.obj: ../DSPF_sp_mat_mul_cn.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DSPF_sp_mat_mul_cn.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

DSPF_sp_mat_mul_opt.obj: ../DSPF_sp_mat_mul_opt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DSPF_sp_mat_mul_opt.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

diskio.obj: ../diskio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="diskio.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

ff.obj: ../ff.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="ff.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="/home/arjun/workspace_v7/UART-ECHO" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/third_party/fatfs/src" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/hw" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x/omapl138" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/include/c674x" --include_path="/opt/ti/OMAPL138_StarterWare_1_10_04_01/usblib/include" --include_path="/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


