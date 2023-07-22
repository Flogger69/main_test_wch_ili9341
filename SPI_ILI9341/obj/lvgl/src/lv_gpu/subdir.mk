################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/lv_gpu/lv_gpu_nxp_pxp.c \
../lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.c \
../lvgl/src/lv_gpu/lv_gpu_nxp_vglite.c \
../lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c 

OBJS += \
./lvgl/src/lv_gpu/lv_gpu_nxp_pxp.o \
./lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.o \
./lvgl/src/lv_gpu/lv_gpu_nxp_vglite.o \
./lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.o 

C_DEPS += \
./lvgl/src/lv_gpu/lv_gpu_nxp_pxp.d \
./lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.d \
./lvgl/src/lv_gpu/lv_gpu_nxp_vglite.d \
./lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/lv_gpu/%.o: ../lvgl/src/lv_gpu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/vl/git/repository3/SPI_ILI9341/Debug" -I"/home/vl/git/repository3/SPI_ILI9341/Core" -I"/home/vl/git/repository3/SPI_ILI9341/User" -I"/home/vl/git/repository3/SPI_ILI9341/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


