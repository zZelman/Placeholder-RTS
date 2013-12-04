################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CGame.cpp \
../src/CGrid.cpp \
../src/CSprite.cpp \
../src/CTexture.cpp \
../src/CTile.cpp \
../src/IRenderable.cpp \
../src/IUpdateable.cpp \
../src/IUserInput.cpp \
../src/main.cpp 

OBJS += \
./src/CGame.o \
./src/CGrid.o \
./src/CSprite.o \
./src/CTexture.o \
./src/CTile.o \
./src/IRenderable.o \
./src/IUpdateable.o \
./src/IUserInput.o \
./src/main.o 

CPP_DEPS += \
./src/CGame.d \
./src/CGrid.d \
./src/CSprite.d \
./src/CTexture.d \
./src/CTile.d \
./src/IRenderable.d \
./src/IUpdateable.d \
./src/IUserInput.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDEBUG -I"/home/zZelman/Dropbox/Placeholder-RTS/SFML-2.1/include" -I"/home/zZelman/Dropbox/Placeholder-RTS/rapidxml-1.13" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


