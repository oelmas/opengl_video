################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Primitives/shapegenerator.cpp 

OBJS += \
./Primitives/shapegenerator.o 

CPP_DEPS += \
./Primitives/shapegenerator.d 


# Each subdirectory must supply rules for building sources it contributes
Primitives/%.o: ../Primitives/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


