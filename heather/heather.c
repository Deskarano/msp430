#include <msp430.h>

#define LED0 BIT0

#define BTN BIT3

void delay()
{
    for(volatile unsigned int count = 0; count < 60000; count++);
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= LED0;
    P1OUT = 0;

    int count = 0;
    int loop;

    while(true)
    {
        while((P1IN & BTN) != BTN);
        count++;

        for(loop = 0; loop < count; loop++)
        {
            P1OUT ^= LED0;
            delay();
            P1OUT ^= LED0;
            delay();
        }
    }
}
