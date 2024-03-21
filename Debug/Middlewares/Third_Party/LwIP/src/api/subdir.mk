################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/api/api_lib.c \
../Middlewares/Third_Party/LwIP/src/api/api_msg.c \
../Middlewares/Third_Party/LwIP/src/api/err.c \
../Middlewares/Third_Party/LwIP/src/api/if_api.c \
../Middlewares/Third_Party/LwIP/src/api/netbuf.c \
../Middlewares/Third_Party/LwIP/src/api/netdb.c \
../Middlewares/Third_Party/LwIP/src/api/netifapi.c \
../Middlewares/Third_Party/LwIP/src/api/sockets.c \
../Middlewares/Third_Party/LwIP/src/api/tcpip.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.o \
./Middlewares/Third_Party/LwIP/src/api/api_msg.o \
./Middlewares/Third_Party/LwIP/src/api/err.o \
./Middlewares/Third_Party/LwIP/src/api/if_api.o \
./Middlewares/Third_Party/LwIP/src/api/netbuf.o \
./Middlewares/Third_Party/LwIP/src/api/netdb.o \
./Middlewares/Third_Party/LwIP/src/api/netifapi.o \
./Middlewares/Third_Party/LwIP/src/api/sockets.o \
./Middlewares/Third_Party/LwIP/src/api/tcpip.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.d \
./Middlewares/Third_Party/LwIP/src/api/api_msg.d \
./Middlewares/Third_Party/LwIP/src/api/err.d \
./Middlewares/Third_Party/LwIP/src/api/if_api.d \
./Middlewares/Third_Party/LwIP/src/api/netbuf.d \
./Middlewares/Third_Party/LwIP/src/api/netdb.d \
./Middlewares/Third_Party/LwIP/src/api/netifapi.d \
./Middlewares/Third_Party/LwIP/src/api/sockets.d \
./Middlewares/Third_Party/LwIP/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/api/%.o Middlewares/Third_Party/LwIP/src/api/%.su Middlewares/Third_Party/LwIP/src/api/%.cyclo: ../Middlewares/Third_Party/LwIP/src/api/%.c Middlewares/Third_Party/LwIP/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/MQTT/MQTTPacket" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/lib/mbedtls" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/aws/MQTT" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Core/App/aws" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/api/api_lib.cyclo ./Middlewares/Third_Party/LwIP/src/api/api_lib.d ./Middlewares/Third_Party/LwIP/src/api/api_lib.o ./Middlewares/Third_Party/LwIP/src/api/api_lib.su ./Middlewares/Third_Party/LwIP/src/api/api_msg.cyclo ./Middlewares/Third_Party/LwIP/src/api/api_msg.d ./Middlewares/Third_Party/LwIP/src/api/api_msg.o ./Middlewares/Third_Party/LwIP/src/api/api_msg.su ./Middlewares/Third_Party/LwIP/src/api/err.cyclo ./Middlewares/Third_Party/LwIP/src/api/err.d ./Middlewares/Third_Party/LwIP/src/api/err.o ./Middlewares/Third_Party/LwIP/src/api/err.su ./Middlewares/Third_Party/LwIP/src/api/if_api.cyclo ./Middlewares/Third_Party/LwIP/src/api/if_api.d ./Middlewares/Third_Party/LwIP/src/api/if_api.o ./Middlewares/Third_Party/LwIP/src/api/if_api.su ./Middlewares/Third_Party/LwIP/src/api/netbuf.cyclo ./Middlewares/Third_Party/LwIP/src/api/netbuf.d ./Middlewares/Third_Party/LwIP/src/api/netbuf.o ./Middlewares/Third_Party/LwIP/src/api/netbuf.su ./Middlewares/Third_Party/LwIP/src/api/netdb.cyclo ./Middlewares/Third_Party/LwIP/src/api/netdb.d ./Middlewares/Third_Party/LwIP/src/api/netdb.o ./Middlewares/Third_Party/LwIP/src/api/netdb.su ./Middlewares/Third_Party/LwIP/src/api/netifapi.cyclo ./Middlewares/Third_Party/LwIP/src/api/netifapi.d ./Middlewares/Third_Party/LwIP/src/api/netifapi.o ./Middlewares/Third_Party/LwIP/src/api/netifapi.su ./Middlewares/Third_Party/LwIP/src/api/sockets.cyclo ./Middlewares/Third_Party/LwIP/src/api/sockets.d ./Middlewares/Third_Party/LwIP/src/api/sockets.o ./Middlewares/Third_Party/LwIP/src/api/sockets.su ./Middlewares/Third_Party/LwIP/src/api/tcpip.cyclo ./Middlewares/Third_Party/LwIP/src/api/tcpip.d ./Middlewares/Third_Party/LwIP/src/api/tcpip.o ./Middlewares/Third_Party/LwIP/src/api/tcpip.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api

