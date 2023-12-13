#include "stm32f3xx.h"

void RCC_Configuration(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
}

void GPIO_Configuration(void)
{
    GPIOA->MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10);  
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10;
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR9 | GPIO_PUPDR_PUPDR10);
    GPIOA->AFR[1] |= (0x7 << (4 * (9 - 8))) | (0x7 << (4 * (10 - 8)));
}

void UART_Configuration(void)
{
    USART1->BRR = 8000000 / 9600;
    USART1->CR1 = USART_CR1_TE;  
    USART1->CR1 |= USART_CR1_UE;
}

int main(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    UART_Configuration();

    while (1)
    {
        uint16_t number = 1234;
        while (!(USART1->ISR & USART_ISR_TXE));
        USART1->TDR = (number >> 8) & 0xFF;
        while (!(USART1->ISR & USART_ISR_TXE));
        USART1->TDR = number & 0xFF;
    }
}
