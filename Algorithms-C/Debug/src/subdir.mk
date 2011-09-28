################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cocktailsort.c \
../src/disjointset.c \
../src/heapsort.c \
../src/kruskal.c 

OBJS += \
./src/cocktailsort.o \
./src/disjointset.o \
./src/heapsort.o \
./src/kruskal.o 

C_DEPS += \
./src/cocktailsort.d \
./src/disjointset.d \
./src/heapsort.d \
./src/kruskal.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


