#include "GpioPin.h"
#include "stm32g4xx.h"


void init_pin()
{
    //1. Turn on clock for GPIOB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    //2. Configure pin 6 as output (01)
    GPIOB->MODER &= ~(0x3 << (6 * 2));   // clear bits
    GPIOB->MODER |=  (0x1 << (6 * 2));   // set as output (01)

    //3. Open-drain
    GPIOB->OTYPER |= (1 << 6);

    //4. Pull-up
    GPIOB->PUPDR &= ~(0x3 << (6 * 2));   //clear bits
    GPIOB->PUPDR |=  (0x1 << (6 * 2));   // pull-up (01)

    //5. Set pin 6 high
    GPIOB->BSRR = (1 << 6);
}

void set_pin_input()
{
    // Set pin 6 as input (00)
    GPIOB->MODER &= ~(0x3 << (6 * 2));
    GPIOB->MODER |= (0x0 << (6 * 2));
}

void set_pin_output()
{
    // Set pin 6 as output (01)
    GPIOB->MODER &= ~(0x3 << (6 * 2));
    GPIOB->MODER |= (0x1 << (6 * 2));
}
