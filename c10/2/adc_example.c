#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect)
{
    if (ADC > 650)
        PORTB |= _BV(PB7);
    else
        PORTB &= ~_BV(PB7);
}

int main(void)
{
    DDRB |= _BV(PB7);
    PORTB &= ~_BV(PB7);
    /* Set ADC prescaler to 64 - 187.5kHz ADC clock */
    ADCSRA = _BV(ADPS2) | _BV(ADPS1);
    /* AREF reference, channel 0, right shift result */
    ADMUX = 0x00;
    /* Free-running mode and enable ADC */
    ADCSRA |= _BV(ADATE) | _BV(ADEN);
    ADCSRB = 0x00;
    /* Enable Interrupts */
    sei();
    ADCSRA |= _BV(ADIE);
    /* Start Conversions */
    ADCSRA |= _BV(ADSC);
    while (1);
}