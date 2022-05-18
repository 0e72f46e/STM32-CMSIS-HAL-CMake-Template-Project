# (C) ERF4N: github.com/0e72f46e | 2022 #
# > CMAKE CMSIS BARE-METAL TEMPLATE PROJECT FOR ARM CORTEX-M STM32 MCUS <

#[[
vvv FILE/DIRS STRUCTURE vvv
├── project (STM32CubeIDE "Core" folder)
│   ├── Inc
│   │   └── main.h
│   ├── Src
│   │   ├── main.c
│   │   └── system_<device>.c
│   ├── Startup
│   │   └── startup_<device>.s
│   └── <device>_FLASH.ld
├── drivers (STM32CubeIDE "Drivers" folder)
│   ├── CMSIS
│   │   ├── Device
│   │   │   └── ST
│   │   │       └── STM32F0xx
│   │   │           ├── Include
│   │   │           └── Source
│   │   └── Include
│   │       └── core_cm0.h
│   └── <device>_HAL_Driver (present if "USE_HAL" is YES)
│       ├── Inc
│       │   ├── <device>_hal.h
│       │   └── etc.
│       └── Src
│           ├── <device>_hal.c
│           └── etc.
└── CMakeLists.txt
vvv FILE/DIRS STRUCTURE 
]]



cmake_minimum_required(VERSION 3.5)

# vvv USER CONFIGURATIONS vvv
project(stm32f030_led_blink LANGUAGES CXX C ASM VERSION 1.0)

set(MCU                         STM32F030x6)
set(ARCH                        cortex-m0)
set(CMSIS_VERSION               5.8.0)
set(HAL_DEVICE_NAME             STM32F0xx)
set(USE_HAL                     YES) # remove HAL files from "project" and "drivers" then set to NO, use only CMSIS

set(CMAKE_C_STANDARD            11)
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_C_COMPILER            arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER          arm-none-eabi-g++)
set(CMAKE_EXE_LINKER_LAUNCHER   arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER          arm-none-eabi-gcc)
set(OBJCOPY                     arm-none-eabi-objcopy)
set(SIZE                        arm-none-eabi-size)
# ^^^ USER CONFIGURATIONS ^^^

set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_C_EXTENSIONS          OFF)

# vvv COMPILE/LINK FALGS vvv
set(COMMON_COMPILE_FLAGS  -mcpu=${ARCH} -Os --specs=nosys.specs -Wl,--gc-sections --specs=nano.specs -mfloat-abi=soft -mthumb  -mthumb-interwork -Wall -MMD -MP -fmessage-length=0 -ffunction-sections -fdata-sections -fstack-usage)

set(LINK_FLAGS -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map -static -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fno-rtti -fno-exceptions") # NO C++ RTTI and exception
set(CMAKE_ASM_FLAGS ${CMAKE_ASM_FLAGS} "-xassembler-with-cpp")
# ^^^ COMPILE/LINK FLAGS ^^^

file(GLOB PROJECT_SRCS "${CMAKE_SOURCE_DIR}/project/Src/*.c" "${CMAKE_SOURCE_DIR}/project/Src/*.cpp" "${CMAKE_SOURCE_DIR}/project/Src/*.s")

# vvv CMSIS/HAL vvv
set(CMSIS_HDRS ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Device/ST/${HAL_DEVICE_NAME}/Include ${CMAKE_SOURCE_DIR}/drivers/CMSIS/Include)

if(${USE_HAL})
set(HAL_HDRS ${CMAKE_SOURCE_DIR}/drivers/${HAL_DEVICE_NAME}_HAL_Driver/Inc)
file(GLOB HAL_SRCS "${CMAKE_SOURCE_DIR}/drivers/${HAL_DEVICE_NAME}_HAL_Driver/Src/*.c")
endif()
# ^^^ CMSIS/HAL ^^^

file(GLOB STARTUP_FILE "${CMAKE_SOURCE_DIR}/project/Startup/*.s")
file(GLOB LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/project/${MCU}_FLASH.ld")

include_directories(project/Inc #[[RPOJECT_HDRS]] ${CMSIS_HDRS} $<$<BOOL:${USE_HAL}>:${HAL_HDRS}>)

add_executable(${PROJECT_NAME}.elf ${STARTUP_FILE} $<$<BOOL:${USE_HAL}>:${HAL_SRCS}> ${PROJECT_SRCS} )

set_target_properties(${PROJECT_NAME}.elf PROPERTIES CXX_STANDARD 20)
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC ${MCU} $<$<BOOL:${USE_HAL}>:USE_HAL_DRIVER>)
target_compile_options(${PROJECT_NAME}.elf PUBLIC ${COMMON_COMPILE_FLAGS})        
target_link_options(${PROJECT_NAME}.elf PUBLIC ${COMMON_COMPILE_FLAGS} -T${LINKER_SCRIPT} ${LINK_FLAGS})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${OBJCOPY} -O binary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
        COMMAND ${SIZE} --format=berkeley ${PROJECT_NAME}.elf)
