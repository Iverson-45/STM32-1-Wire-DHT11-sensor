#include "stm32g4xx.h"
#include "Timer.h"
/*
 * PSC Prescaler
 * ARR Auto-Reload Register
 * CNT counter
 * CR1 Control Register 1
 * SR Status Register
 * EGR Event Generation Register
 */
void TIM2_Init(void)
{
    // 1. Turn on clock for TIM2
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // 2. Stop timer
    TIM2->CR1 &= ~TIM_CR1_CEN;

    // 3.Set prescaler to 1MHz
    TIM2->PSC = (SystemCoreClock / 1000000) - 1;

    // 4. Auto-reload set to max
    TIM2->ARR = 0xFFFFFFFF;

    // 5. Generate update event to reload PSC & ARR
    TIM2->EGR = TIM_EGR_UG;

    // 6. Clear counter
    TIM2->CNT = 0;

    // 7. Run timer
    TIM2->CR1 |= TIM_CR1_CEN;
}


void delay_us(uint32_t us)
{
	uint32_t start = TIM2->CNT;
	uint32_t ticks = us;

	while((TIM2->CNT - start) <ticks)
	{

	}

}

void delay_ms(uint32_t ms)
{
	while (ms--)
	{
		delay_us(1000);
	}
}





