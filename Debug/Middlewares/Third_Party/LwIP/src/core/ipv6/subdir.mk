################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/ipv6/%.o Middlewares/Third_Party/LwIP/src/core/ipv6/%.su Middlewares/Third_Party/LwIP/src/core/ipv6/%.cyclo: ../Middlewares/Third_Party/LwIP/src/core/ipv6/%.c Middlewares/Third_Party/LwIP/src/core/ipv6/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/lan8742" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW/Target" -I"C:/CubeWorspace/stm32h563_fw/Core/App/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP_RAW" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/App" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/LWIP/Target" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src/include" -I../Core/Inc -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/LwIP/src" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Third_Party/lwrb/inc" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils" -I"C:/CubeWorspace/stm32h563_fw/Middlewares/Solvine/Utils/inc" -I"C:/CubeWorspace/stm32h563_fw/Drivers/BSP/inc" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv6

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv6:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.su ./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.d ./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.o ./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv6

