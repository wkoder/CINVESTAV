################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../arithlib64.c \
../testarithlib64.c \
../utils.c 

OBJS += \
./arithlib64.o \
./testarithlib64.o \
./utils.o 

C_DEPS += \
./arithlib64.d \
./testarithlib64.d \
./utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g3 -Wall -c -fmessage-length=0 -finline-functions -mmmx  -msse2 -mssse3 -msse4 -march=core2 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


