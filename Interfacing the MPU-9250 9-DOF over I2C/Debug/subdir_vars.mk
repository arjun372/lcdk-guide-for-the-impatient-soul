################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../OMAPL138.cmd 

ASM_SRCS += \
../intvecs.asm 

C_SRCS += \
../i2c.c \
../i2cLedBlink.c \
../interrupt.c 

OBJS += \
./i2c.obj \
./i2cLedBlink.obj \
./interrupt.obj \
./intvecs.obj 

ASM_DEPS += \
./intvecs.pp 

C_DEPS += \
./i2c.pp \
./i2cLedBlink.pp \
./interrupt.pp 

C_DEPS__QUOTED += \
"i2c.pp" \
"i2cLedBlink.pp" \
"interrupt.pp" 

OBJS__QUOTED += \
"i2c.obj" \
"i2cLedBlink.obj" \
"interrupt.obj" \
"intvecs.obj" 

ASM_DEPS__QUOTED += \
"intvecs.pp" 

C_SRCS__QUOTED += \
"../i2c.c" \
"../i2cLedBlink.c" \
"../interrupt.c" 

ASM_SRCS__QUOTED += \
"../intvecs.asm" 


