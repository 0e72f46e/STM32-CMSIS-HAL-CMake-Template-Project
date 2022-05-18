# STM32-CMSIS/HAL-CMake-Template-Project
```
CMAKE CMSIS/HAL BARE-METAL TEMPLATE PROJECT FOR ARM CORTEX-M STM32 MCUS
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
│   └── <device>_HAL_Driver >>> present if "USE_HAL" is "YES"
│       ├── Inc
│       │   ├── <device>_hal.h
│       │   └── etc.
│       └── Src
│           ├── <device>_hal.c
│           └── etc.
└── CMakeLists.txt
```
