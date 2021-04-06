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
uint8_t flag_flash = 0;

uint8_t initial_frequency(uint8_t count);
void flash(void);

int main()
{
    uint8_t count = 128;
    uint8_t frequency = 0;
    uint8_t k = 10;

    DDRA = 0xFF;  //Sets portA as outputs
    DDRC = 0x00;  //Sets portC as inputs
    PORTC = 0xFF; //Enables inbuilt pull-up resistors

    PORTA = segments[0];

    for (;;)
    {
        frequency = initial_frequency(count);

        while (frequency != 0)
        {
            PORTA = segments[count % 10];
            count++;
            _delay_ms(1 / frequency); //Delay by 1 sec

            frequency -= k / frequency

             flag_flash = 1;
        }
    }
}

uint8_t initial_frequency(uint8_t count)
{
    uint8_t AB = 0x0, lastAB = 0x0;
    int8_t click = 0;
    uint8_t time = 0, freq = 0;

    While(-3 = < click = < 3)
    {
        AB = ((PINC & _BV(PC1)) | (PINC & _BV(PC0))); // sample encoder

        if ((AB == 0x0 && lastAB == 0x2) || (AB == 0x3 && lastAB == 0x1)) // if CW
        {
            count++;
            click++;
        }

        if ((AB == 0x3 && lastAB == 0x2) || (AB == 0x0 && lastAB == 0x1)) // if CCW
        {
            count--;
            click--;
        }

        PORTA = segments[count % 10]; //display the  value
        _delay_ms(10);                // debounce
        time = +10;

        lastAB = AB; //update encoder position
    }
    freq = 3000 / time;

    return freq;
}

void flash()
{
    if (flag_flash == 1)
    {
        uint8_t i;
        for (i = 0; i < 3; i++)
        {
            PORTA = 0x00;
            _delay_ms(200);
            PORTA = segments[count % 10];
        }
        flag_flash = 0;
    }
}