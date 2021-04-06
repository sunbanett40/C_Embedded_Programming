/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

#define V_MAX 3.3

void init_adc(void)
{
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1); // F_ADC = F_CPU/64
	ADCSRA |= _BV(ADEN);			   // Enable ADC
}

uint16_t read_adc(void)
{
	ADCSRA |= _BV(ADSC); 			// Start ADC conversion
	while (ADCSRA & _BV(ADSC)); 	//wait until result is valid
	return ADC;
}

void channel_adc(uint16_t n)
{
	if(n < 500)
	{
		PORTB |= _BV(PB7);
		printf("\nLED On\n");
	}
	if(n > 1000)
	{
		PORTB &= ~_BV(PB7);
		printf("\nLED Off\n");
	}
}

int main(void)
{
	uint16_t result;
	double voltage;

	init_debug_uart0();
	init_adc();
	DDRB = 0xFF; //Set 8-bits of port x as outputs

	for (;;)
	{
		result = read_adc();			//get position of an ADC
		channel_adc(result);
		voltage = V_MAX / 1023 * result;	//calculate the voltage
		printf("%4d : %6.5lfV\n", result, voltage);
		_delay_ms(200);
	}
}