################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graphics/CSprite.cpp \
../src/Graphics/CTexture.cpp 

OBJS += \
./src/Graphics/CSprite.o \
./src/Graphics/CTexture.o 

CPP_DEPS += \
./src/Graphics/CSprite.d \
./src/Graphics/CTexture.d 


# Each subdirectory must supply rules for building sources it contributes
src/Graphics/%.o: ../src/Graphics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


