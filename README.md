 # CMSIS-CMake-Project-Template
 > CMAKE CMSIS BARE-METAL TEMPLATE PROJECT FOR ARM CORTEX-M STM32 MCUS <

 FILE/DIRS STRUCTURE:
  ├── project (project source/header files located here)
  │   └── main.c/cpp
  │
  ├── cmsis (replace desired CMSIS version in here)
  │   └── CMSIS-<CMSIS_VERSION>
  │       ├── Core
  │       │   └── Include (cmsis core (Cortex-M) header files)
  │       └── etc.
  │
  ├── device
  │   └── <MCU>
  │       ├── include
  │       │   ├── stm32xxxx.h (vendor device header file)
  │       │   ├── stm32xxxxxx.h (will be included by stm32xxxx.h)
  │       │   └── system_stm32xxxx.h (System & Clock configuration header file)
  │       └── src
  │           ├── system_stm32xxxx.c (System & Clock configuration source file)
  │           └── startup_stm32xxxx.s (Startup and IRQs vector assembly file)
  │  
  └── CMakeLists.txt
