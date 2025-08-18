#include "Uart.h"
#include "stm32g4xx.h"
#include <stdio.h>

void UART2_Init(void)
{
    // 1. Włącz zegary dla GPIOA i USART2
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;      // GPIOA clock enable
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;   // USART2 clock enable

    // 2. Ustaw piny PA2 i PA3 jako AF7 (USART2 TX/RX)
    // MODER: 10 = Alternate function
    GPIOA->MODER &= ~((3 << (2*2)) | (3 << (3*2))); // wyczyść tryby pinów 2 i 3
    GPIOA->MODER |=  (2 << (2*2)) | (2 << (3*2));   // ustaw AF mode

    // AFRL dla PA2 i PA3 (AF7)
    GPIOA->AFR[0] &= ~((0xF << (2*4)) | (0xF << (3*4))); // wyczyść
    GPIOA->AFR[0] |=  (7 << (2*4)) | (7 << (3*4));       // ustaw AF7 (USART2)

    // 3. Skonfiguruj USART2 - baudrate 115200 przy 64MHz
    // USARTDIV = 64MHz / (16 * 115200) = 34.72
    // Mantissa = 34, Fraction = 16 * 0.72 = ~12
    USART2->BRR = (34 << 4) | 12;

    // 4. Włącz USART2, nadajnik i odbiornik
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    // 5. Poczekaj aż USART będzie gotowy
    while (!(USART2->ISR & USART_ISR_TEACK));
    while (!(USART2->ISR & USART_ISR_REACK));
}

void UART2_SendChar(char c)
{
    while (!(USART2->ISR & USART_ISR_TXE));  // czekaj na pusty bufor nadawczy
    USART2->TDR = c;                         // wyślij znak
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
