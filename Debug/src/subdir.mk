################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CGame.cpp \
../src/CSprite.cpp \
../src/CTexture.cpp \
../src/IRenderable.cpp \
../src/IUpdateable.cpp \
../src/IUserInput.cpp \
../src/main.cpp 

OBJS += \
./src/CGame.o \
./src/CSprite.o \
./src/CTexture.o \
./src/IRenderable.o \
./src/IUpdateable.o \
./src/IUserInput.o \
./src/main.o 

CPP_DEPS += \
./src/CGame.d \
./src/CSprite.d \
./src/CTexture.d \
./src/IRenderable.d \
./src/IUpdateable.d \
./src/IUserInput.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


