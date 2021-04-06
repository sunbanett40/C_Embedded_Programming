#include <avr/io.h>
#include <util/delay.h>

/*
Pin     7 6 5 4 3 2 1 0
Segment a b c d e f g dp

0       1 1 1 1 1 1 0 0     0xFC
1       0 1 1 0 0 0 0 0     0x60
2       1 1 0 1 1 0 1 0     0xDA
3       1 1 1 1 0 0 1 0     0xF2
4       0 1 1 0 0 1 1 0     0x66
5       1 0 1 1 0 1 1 0     0xB6
6       1 0 1 1 1 1 1 0     0xBE
7       1 1 1 0 0 0 0 0     0xE4
8       1 1 1 1 1 1 1 0     0xFE
9       1 1 1 0 0 1 1 0     0xF6
*/

const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};

uint8_t rot_AB(uint8_t rot)
{
    return (rot & _BV(PC1)) | (rot & _BV(PC0));
}

uint8_t buzz(uint8_t length)
{
    uint8_t i;
        for (i = 0; i < length; i++)
        {
            PORTA &= ~_BV(PA0); //Set bit n of port x low
            _delay_ms(0.5);
            PORTA |= _BV(PA0); //Set bit n of port x high
            _delay_ms(0.5);
        }
    return 0;
}

int main(void)
{
    uint8_t count = 0;
    uint8_t lastAB = 0x0, AB = 0x0;

    DDRA = 0xFF;  //Sets portA as outputs
    DDRC = 0x00;  //Sets portC as inputs
    PORTC = 0xFF; //Enables inbuilt pull-up resistors

    PORTA = segments[0];

    for (;;)
    {
        AB = rot_AB(PINC); // sample encoder

        if ((AB == 0x0 && lastAB == 0x2) || (AB == 0x3 && lastAB == 0x1)) // if CW
        {
            count--;
            buzz(30);
        }

        if ((AB == 0x3 && lastAB == 0x2) || (AB == 0x0 && lastAB == 0x1)) // if CCW
        {
            count++;
            buzz(30);
        }

        PORTA = segments[count % 10]; //display the  value
       _delay_ms(10); // debounce

        lastAB = AB; //update encoder position
    }
}