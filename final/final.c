#include <msp430.h> 

#define LED0 BIT0
#define LED1 BIT6

/* Define a byte for each letter which indicates the positions of
 * dots and dashes in the morse code equivalent. The positions of
 * dots are specified by a 1 in the upper four bits while the
 * positions of dashes are specified by a 1 in the lower four 
 * bits. The byte is read right to left. For example:
 *
 * Byte A:  0100 1000
 * Morse:   X X . -     (where X means no symbol)
 *
 * A morse dot is shown by setting LED0 (red) and a morse dash is
 * shown by setting LED1 (green).
 */

void string_to_morse(char *target, int length, char *string)
{
    for(int i = 0; i < length; i++)
    {
        switch(string[i])
        {
            case 'A':
                target[i] = 0b01001000;
                break;
            case 'B':
                target[i] = 0b11100001;
                break;
            case 'C':
                target[i] = 0b10100101;
                break;
            case 'D':
                target[i] = 0b11000010;
                break;
            case 'E':
                target[i] = 0b10000000;
                break;
            case 'F':
                target[i] = 0b10110100;
                break;
            case 'G':
                target[i] = 0b10000110;
                break;
            case 'H':
                target[i] = 0b11110000;
                break;
            case 'I':
                target[i] = 0b11000000;
                break;
            case 'J':
                target[i] = 0b00011110;
                break;
            case 'K':
                target[i] = 0b01001010;
                break;
            case 'L':
                target[i] = 0b11010010;
                break;
            case 'M':
                target[i] = 0b00001100;
                break;
            case 'N':
                target[i] = 0b10000100;
                break;
            case 'O':
                target[i] = 0b00001110;
                break;
            case 'P':
                target[i] = 0b10010110;
                break;
            case 'Q':
                target[i] = 0b01001011;
                break;
            case 'R':
                target[i] = 0b10100100;
                break;
            case 'S':
                target[i] = 0b11100000;
                break;
            case 'T':
                target[i] = 0b00001000;
                break;
            case 'U':
                target[i] = 0b01101000;
                break;
            case 'V':
                target[i] = 0b01111000;
                break;
            case 'W':
                target[i] = 0b00101100;
                break;
            case 'X':
                target[i] = 0b01101001;
                break;
            case 'Y':
                target[i] = 0b00101101;
                break;
            case 'Z':
                target[i] = 0b11000011;
                break; 
        }
    }
}

void wait(unsigned int time)
{
    for(volatile unsigned int i = 0; i < time; i++){}
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= (LED0 + LED1);
    P1OUT &= ~(LED0 + LED1);

    int morse_length = 6;
    char morse[morse_length];
    string_to_morse(morse, morse_length, "ABC");

    char not_blank;

    for(int letter = 0; letter < morse_length; letter++)
    {
        for(int pos = 0; pos < 4; pos++)
        {
            not_blank = 0;

            if((morse[letter] >> 4) & 1)
            {
                P1OUT ^= LED0;
                not_blank = 1;
            }

            if(morse[letter] & 1)
            {
                P1OUT ^= LED1;
                not_blank = 1;
            }

            if(not_blank)
            {
                wait(50000);
                P1OUT &= ~(LED0 + LED1);
                wait(10000);
            }

            morse[letter] = morse[letter] >> 1;
        }

        if(not_blank)
        {
            wait(65535);
        }
    }

    P1OUT ^= (LED0 + LED1);
}
