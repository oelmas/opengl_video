################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../MeShaderCode.o \
../main.o \
../mainwindow.o \
../meglwidget.o \
../moc_mainwindow.o \
../moc_meglwidget.o 

CPP_SRCS += \
../main.cpp \
../mainwindow.cpp \
../meglwidget.cpp 

OBJS += \
./main.o \
./mainwindow.o \
./meglwidget.o 

CPP_DEPS += \
./main.d \
./mainwindow.d \
./meglwidget.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


