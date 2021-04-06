#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t count = 0;

ISR(INT0_vect)
{
    if (count > 0)
    {
        count--;
    }
    PORTA = count;
}

ISR(INT1_vect)
{
    if (count < 255)
    {
        count++;
    }
    PORTA = count;
}

int main()
{
    DDRA = 0xFF;
    DDRD = 0x00;
    PORTD = 0xFF; //Enables inbuilt pull-up resistors

    /* Set to trigger on falling edge */
    EICRA |= _BV(ISC01);
    /* Enable interrupt */
    EIMSK |= _BV(INT0) | _BV(INT1);
    sei();

    for (;;);
}