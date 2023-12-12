#include "main.h"
// #include "stm32f30x.h"

#define BIT21 0b1000000000000000000000

int main(void)
{
    RCC -> AHBENR |= BIT21; // Nustatom 21 bita, kad ijungti GPIOE LED'ams arba |= RCC_AHBENR_GPIOEEN
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN; // Ijungiam GPIOA mygtukui
    GPIOE->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | 
                   GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0 | 
                   GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | 
                   GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0); // Nustatom 8-15 GPIOE pinus kaip isejimus
    // GPIOA->MODER &= ~(GPIO_MODER_MODER0); // Visi GPIO_MODER_MODER0 bitai pagal nutylejima yra 1 isskyrus MODER0 bita. Visus GPIO_MODER_MODER0 bitus apverciam su ~. MODER0 bitas tampa 1, todel nustatom MODER0 bita i 0, kad butu iejimas, tuomet 0 GPIOA pinas tampa iejimu mygtukui

    int mygto_busena = 0;

    GPIOE->BSRR = 0xFF << 8; // Ijungiam visus LED'us

    while(1)
    {
        mygto_busena = GPIOA -> IDR & GPIO_IDR_0;

        if(mygto_busena == 1)
        {
            GPIOE -> BRR = 0xFF << 8; // Isjungiam visus LED'us
            for (int i = 0; i < 100000; i++);
        }
    }
    
}