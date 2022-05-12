# (C) ERF4N: github.com/0e72f46e | 2022 #
# > CMAKE CMSIS BARE-METAL TEMPLATE PROJECT FOR ARM CORTEX-M STM32 MCUS <
#
# FILE/DIRS STRUCTURE:
#  ├── project 
#  │   └── main.c/cpp
#  │
#  ├── cmsis
#  │   └── CMSIS-<CMSIS_VERSION>
#  │       ├── Core
#  │       │   └── Include (cmsis core (Cortex-M) header files)
#  │       └── etc.
#  │
#  ├── device
#  │   └── <MCU>
#  │       ├── include
#  │       │   ├── stm32xxxx.h (vendor device header file)
#  │       │   ├── stm32xxxxxx.h (will be included by stm32xxxx.h)
#  │       │   └── system_stm32xxxx.h (System & Clock configuration header file)
#  │       └── src
#  │           ├── system_stm32xxxx.c (System & Clock configuration source file)
#  │           └── startup_stm32xxxx.s (Startup and IRQs vector assembly file)
#  │  
#  └── CMakeLists.txt



cmake_minimum_required(VERSION 3.5)

# >>>>> USER CONFIGURATIONS
project(stm32f030_led_blink LANGUAGES CXX C ASM VERSION 1.0)

set(MCU            STM32F030x6)
set(ARCH           cortex-m0)
set(CMSIS_VERSION  5.8.0)

set(CMAKE_C_STANDARD            11)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_C_COMPILER            arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER          arm-none-eabi-g++)
set(CMAKE_EXE_LINKER_LAUNCHER   arm-none-eabi-ld)
set(CMAKE_ASM_COMPILER          arm-none-eabi-gcc)
set(OBJCOPY                     arm-none-eabi-objcopy)
set(SIZE                        arm-none-eabi-size)

# USER CONFIGURATIONS <<<<<

set(PROJECT_CXX_SOURCE_FILES_FLAGS)
set(COMMON_COMPILE_LINK_FLAGS -mcpu=${ARCH} -Os -mthumb --specs=nano.specs -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -mfloat-abi=soft -fstack-usage -fno-exceptions -fno-rtti -MMD -MP)

set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_C_EXTENSIONS          OFF)

file(GLOB PROJECT_CXX_SOURCE_FILES "project/*.cpp")
file(GLOB PROJECT_C_SOURCE_FILES "project/*.c")
file(GLOB PROJECT_HEADER_FILES "project/*.h" "project/*.hpp")


#set_source_files_properties(D/main.cpp PROPERTIES COMPILE_FLAGS ${COMMON_COMPILE_LINK_FLAGS} ${PROJECT_CXX_SOURCE_FILES_FLAGS})

file(GLOB DEVICE_SOURCE_FILES "device/${MCU}/src/system_*.c" "device/${MCU}/src/startup_*.s")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/device/${MCU}/${MCU}_FLASH.ld)

include_directories(device/${MCU}/include)
include_directories(cmsis/CMSIS-${CMSIS_VERSION}/Core/Include)

add_executable(${PROJECT_NAME}.elf ${PROJECT_CXX_SOURCE_FILES} ${DEVICE_SOURCE_FILES})

set_target_properties(${PROJECT_NAME}.elf PROPERTIES CXX_STANDARD 20)
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC -D${MCU})
target_compile_options(${PROJECT_NAME}.elf PUBLIC ${COMMON_COMPILE_LINK_FLAGS})        
target_link_options(${PROJECT_NAME}.elf PUBLIC -T${LINKER_SCRIPT} -Wl,--gc-sections --specs=nosys.specs -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${OBJCOPY} -O binary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
        COMMAND ${SIZE} --format=berkeley ${PROJECT_NAME}.elf)
