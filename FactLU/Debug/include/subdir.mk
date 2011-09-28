################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/LU.c \
../include/matrix.c 

OBJS += \
./include/LU.o \
./include/matrix.o 

C_DEPS += \
./include/LU.d \
./include/matrix.d 


# Each subdirectory must supply rules for building sources it contributes
include/%.o: ../include/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/matrix.o: ../include/matrix.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -lm -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"include/matrix.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


