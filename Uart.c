#include "Uart.h"
#include "stm32g4xx.h"
#include <stdio.h>

void UART2_Init(void)
{
    // 1. Turn on clock for GPIOA & USART2
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;      // GPIOA clock enable
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;   // USART2 clock enable

    // 2. Set pins PA2 & PA3 as AF7 (USART2 TX/RX)
    // MODER: 10 = Alternate function
    GPIOA->MODER &= ~((3 << (2*2)) | (3 << (3*2))); // clear pin modes 2 i 3
    GPIOA->MODER |=  (2 << (2*2)) | (2 << (3*2));   // Set AF mode

    // AFRL for PA2 i PA3 (AF7)
    GPIOA->AFR[0] &= ~((0xF << (2*4)) | (0xF << (3*4))); // clear
    GPIOA->AFR[0] |=  (7 << (2*4)) | (7 << (3*4));       // Set AF7 (USART2)

    // 3. Configure USART2 - baudrate 115200  64MHz
    // USARTDIV = 64MHz / (16 * 115200) = 34.72
    // Mantissa = 34, Fraction = 16 * 0.72 = ~12
    USART2->BRR = (34 << 4) | 12;

    // 4. Turn on USART2, RX & TX
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    // 5. Wait for uart to be ready
    while (!(USART2->ISR & USART_ISR_TEACK));
    while (!(USART2->ISR & USART_ISR_REACK));
}

void UART2_SendChar(char c)
{
    while (!(USART2->ISR & USART_ISR_TXE));  // wait for empty buffer
    USART2->TDR = c;                         // send char
}

void UART2_SendString(const char *str)
{
    while (*str)
    {
        UART2_SendChar(*str++);
    }
}

void UART2_SendFloat(float num, int decimals)
{
    char buffer[32];
    sprintf(buffer, "%.*f", decimals, num);
    UART2_SendString(buffer);
}
