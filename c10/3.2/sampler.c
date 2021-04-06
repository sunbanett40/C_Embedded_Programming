/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "debug.h"

#define V_MAX 3.3

ISR(ADC_vect)
{
	PORTB |= _BV(PB7);
	_delay_us(1); //Delay by 1 microsecond
	PORTB &= ~_BV(PB7);
}

void init_adc(void)
{
	/* Set ADC prescaler to 64 - 187.5kHz ADC clock */
	ADCSRA = _BV(ADPS2) | _BV(ADPS1);
	/* AREF reference, channel 0, right shift result */
	ADMUX = 0x00;
	/* Free-running mode and enable ADC */
	ADCSRA |= _BV(ADATE) | _BV(ADEN);
	ADCSRB = 0x00;
}

uint16_t read_adc(void)
{
	ADCSRA |= _BV(ADSC); // Start ADC conversion
	while (ADCSRA & _BV(ADSC)); //wait until result is valid
	return ADC;
}

int main(void)
{
	init_debug_uart0();
	init_adc();
	DDRB |= _BV(PB7);
	PORTB &= ~_BV(PB7);

	/* Enable Interrupts */
	sei();
	ADCSRA |= _BV(ADIE);
	/* Start Conversions */
	ADCSRA |= _BV(ADSC);
	for (;;);
}
