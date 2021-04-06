#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "debug.h"

int main()
{
    DDRA = 0xFF;
    init_debug_uart0();

    uint8_t count = 0;
    printf("%4.1i\n", count);

    for (;;)
    {
       PORTA = count;

        _delay_ms(20);
        printf("%4.1i\n", count);
        count++;
    }
    /* uint8_t i = 0;
    uint8_t out =0;

    for ( i = 7; i >= 0; i--)
    { //If not output binary number of count

        if (out >= 2**i)
        {
            PORTC | = _BV(j); //Set bit j of port C high
            out - 2**i;
        }
    }*/
}
