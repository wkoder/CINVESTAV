################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/gram_schmidt.c \
../include/matrix.c \
../include/simplecenterdiff.c 

OBJS += \
./include/gram_schmidt.o \
./include/matrix.o \
./include/simplecenterdiff.o 

C_DEPS += \
./include/gram_schmidt.d \
./include/matrix.d \
./include/simplecenterdiff.d 


# Each subdirectory must supply rules for building sources it contributes
include/%.o: ../include/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


