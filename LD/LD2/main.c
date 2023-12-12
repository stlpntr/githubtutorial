#include "main.h"

void init_tim_gpio(void);
void init_tim(int period);

int main(void)
{
	init_tim_gpio();
	init_tim(1000);
}

void init_tim_gpio(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;

	GPIOE->MODER |= GPIO_MODER_MODER13_1;
	GPIOE->MODER &= ~GPIO_MODER_MODER13_0;
	GPIOE->AFR[1] |= (2 << ((13 - 8) * 4));
}

void init_tim(int period)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	TIM1->CCMR2 |= TIM_CCMR2_OC3PE;

	TIM1->CR1 |= TIM_CR1_ARPE;
	TIM1->ARR = period;

	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->CCER |= TIM_CCER_CC3E;

	TIM1->CR1 |= TIM_CR1_CEN;
}