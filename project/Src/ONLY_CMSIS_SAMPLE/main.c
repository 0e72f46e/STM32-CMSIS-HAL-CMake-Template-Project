#include <stm32f030x6.h>
#include <stdint.h>

// uint32_t SystemCoreClock = 8000000; // Configured in system_device.c

// delay loop for 8 MHz CPU clock with optimizer enabled
void delay(uint32_t msec)
{
    for (uint32_t j = 0; j < 2000UL * msec; j++)
    {
        __NOP();
    }
}

int main(void)
{
    // Enable Port A clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // PA4 = Output for LEDs Push-Pull
    GPIOA->MODER |= GPIO_MODER_MODER4_0;
    
    while (1)
    {
        // LED Pin -> High
        GPIOA->BSRR = GPIO_BSRR_BS_4;
        delay(50);

        // LED Pin -> Low
        GPIOA->BSRR = GPIO_BSRR_BR_4;
        delay(5000);
    }
}
