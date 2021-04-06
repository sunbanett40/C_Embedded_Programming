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
7       1 1 1 0 0 0 0 0     0xE0
8       1 1 1 1 1 1 1 0     0xFE
9       1 1 1 0 0 1 1 0     0xE6
*/

const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
uint8_t count = 0;

int main(void)
{
    DDRA = 0xFF;  //Sets portA as outputs
    DDRC = 0x00;  //Sets portC as inputs
    PORTC = 0xFF; //Enables inbuilt pull-up resistors

    PORTA = segments[0];
    for (;;)
    {
        while ((PINC & _BV(PC7)) != 0)
        {
            count++;
            _delay_ms(300);   //stop program for 300 ms to debounce switch
        }

        while ((PINC & _BV(PC7)) == 0)
        {
            PORTA = segments[count % 10];
        }
        
    }
}