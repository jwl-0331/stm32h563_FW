################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Solvine/Utils/src/qbuffer.c \
../Middlewares/Solvine/Utils/src/svCLI.c \
../Middlewares/Solvine/Utils/src/svLinkBuffer.c \
../Middlewares/Solvine/Utils/src/svList.c \
../Middlewares/Solvine/Utils/src/svOvRingBuffer.c \
../Middlewares/Solvine/Utils/src/svRingBuffer.c \
../Middlewares/Solvine/Utils/src/svTaskTimer.c \
../Middlewares/Solvine/Utils/src/svUtils.c 

OBJS += \
./Middlewares/Solvine/Utils/src/qbuffer.o \
./Middlewares/Solvine/Utils/src/svCLI.o \
./Middlewares/Solvine/Utils/src/svLinkBuffer.o \
./Middlewares/Solvine/Utils/src/svList.o \
./Middlewares/Solvine/Utils/src/svOvRingBuffer.o \
./Middlewares/Solvine/Utils/src/svRingBuffer.o \
./Middlewares/Solvine/Utils/src/svTaskTimer.o \
./Middlewares/Solvine/Utils/src/svUtils.o 

C_DEPS += \
./Middlewares/Solvine/Utils/src/qbuffer.d \
./Middlewares/Solvine/Utils/src/svCLI.d \
./Middlewares/Solvine/Utils/src/svLinkBuffer.d \
./Middlewares/Solvine/Utils/src/svList.d \
./Middlewares/Solvine/Utils/src/svOvRingBuffer.d \
./Middlewares/Solvine/Utils/src/svRingBuffer.d \
./Middlewares/Solvine/Utils/src/svTaskTimer.d \
./Middlewares/Solvine/Utils/src/svUtils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Solvine/Utils/src/%.o Middlewares/Solvine/Utils/src/%.su Middlewares/Solvine/Utils/src/%.cyclo: ../Middlewares/Solvine/Utils/src/%.c Middlewares/Solvine/Utils/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/MQTT/MQTTPacket" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Solvine-2f-Utils-2f-src

clean-Middlewares-2f-Solvine-2f-Utils-2f-src:
	-$(RM) ./Middlewares/Solvine/Utils/src/qbuffer.cyclo ./Middlewares/Solvine/Utils/src/qbuffer.d ./Middlewares/Solvine/Utils/src/qbuffer.o ./Middlewares/Solvine/Utils/src/qbuffer.su ./Middlewares/Solvine/Utils/src/svCLI.cyclo ./Middlewares/Solvine/Utils/src/svCLI.d ./Middlewares/Solvine/Utils/src/svCLI.o ./Middlewares/Solvine/Utils/src/svCLI.su ./Middlewares/Solvine/Utils/src/svLinkBuffer.cyclo ./Middlewares/Solvine/Utils/src/svLinkBuffer.d ./Middlewares/Solvine/Utils/src/svLinkBuffer.o ./Middlewares/Solvine/Utils/src/svLinkBuffer.su ./Middlewares/Solvine/Utils/src/svList.cyclo ./Middlewares/Solvine/Utils/src/svList.d ./Middlewares/Solvine/Utils/src/svList.o ./Middlewares/Solvine/Utils/src/svList.su ./Middlewares/Solvine/Utils/src/svOvRingBuffer.cyclo ./Middlewares/Solvine/Utils/src/svOvRingBuffer.d ./Middlewares/Solvine/Utils/src/svOvRingBuffer.o ./Middlewares/Solvine/Utils/src/svOvRingBuffer.su ./Middlewares/Solvine/Utils/src/svRingBuffer.cyclo ./Middlewares/Solvine/Utils/src/svRingBuffer.d ./Middlewares/Solvine/Utils/src/svRingBuffer.o ./Middlewares/Solvine/Utils/src/svRingBuffer.su ./Middlewares/Solvine/Utils/src/svTaskTimer.cyclo ./Middlewares/Solvine/Utils/src/svTaskTimer.d ./Middlewares/Solvine/Utils/src/svTaskTimer.o ./Middlewares/Solvine/Utils/src/svTaskTimer.su ./Middlewares/Solvine/Utils/src/svUtils.cyclo ./Middlewares/Solvine/Utils/src/svUtils.d ./Middlewares/Solvine/Utils/src/svUtils.o ./Middlewares/Solvine/Utils/src/svUtils.su

.PHONY: clean-Middlewares-2f-Solvine-2f-Utils-2f-src

