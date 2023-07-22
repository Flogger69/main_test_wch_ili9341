################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/fonts.c \
../User/ili9341.c \
../User/main.c \
../User/system_ch32v30x.c \
../User/touchpad.c \
../User/xpt2046.c 

OBJS += \
./User/ch32v30x_it.o \
./User/fonts.o \
./User/ili9341.o \
./User/main.o \
./User/system_ch32v30x.o \
./User/touchpad.o \
./User/xpt2046.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/fonts.d \
./User/ili9341.d \
./User/main.d \
./User/system_ch32v30x.d \
./User/touchpad.d \
./User/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/vl/git/repository3/SPI_ILI9341/Debug" -I"/home/vl/git/repository3/SPI_ILI9341/Core" -I"/home/vl/git/repository3/SPI_ILI9341/User" -I"/home/vl/git/repository3/SPI_ILI9341/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


