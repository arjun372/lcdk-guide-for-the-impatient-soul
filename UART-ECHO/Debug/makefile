################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./DSPF_sp_mat_mul.obj" \
"./DSPF_sp_mat_mul_cn.obj" \
"./DSPF_sp_mat_mul_opt.obj" \
"./diskio.obj" \
"./ff.obj" \
"./main.obj" \
"../OMAPL138.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/omapl138/usblib/Debug/usblib.lib" \
-l"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/utils/Debug/utils.lib" \
-l"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/omapl138/system_config/Debug/system_config.lib" \
-l"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/omapl138/drivers/Debug/drivers.lib" \
-l"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/omapl138/lcdkOMAPL138/platform/Debug/platform.lib" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
UART-ECHO.out \

EXE_OUTPUTS__QUOTED += \
"UART-ECHO.out" \

BIN_OUTPUTS += \
UART-ECHO.hex \

BIN_OUTPUTS__QUOTED += \
"UART-ECHO.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "UART-ECHO.out"

# Tool invocations
UART-ECHO.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --define=omapl138 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"UART-ECHO.map" --heap_size=0x800 --stack_size=0x800 -i"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/include" -i"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/lib" -i"/opt/ti/OMAPL138_StarterWare_1_10_04_01/binary/c674x/cgt_ccs/utils/Debug" --reread_libs --define=DSP_CORE=1 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="UART-ECHO_linkInfo.xml" --rom_model -o "UART-ECHO.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

UART-ECHO.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"/opt/ti/ccsv7/tools/compiler/ti-cgt-c6000_8.2.0/bin/hex6x"  -o "UART-ECHO.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "DSPF_sp_mat_mul.obj" "DSPF_sp_mat_mul_cn.obj" "DSPF_sp_mat_mul_opt.obj" "diskio.obj" "ff.obj" "main.obj" 
	-$(RM) "DSPF_sp_mat_mul_cn.d" "DSPF_sp_mat_mul_opt.d" "diskio.d" "ff.d" "main.d" 
	-$(RM) "DSPF_sp_mat_mul.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

