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
    ADCSRA |= _BV(ADEN);               // Enable ADC
}

uint16_t read_adc(void)
{
    ADCSRA |= _BV(ADSC); // Start ADC conversion
    while (ADCSRA & _BV(ADSC))
        ; //wait until result is valid
    return ADC;
}

int main(void)
{
    uint16_t result;
    uint8_t pulse = 0;
    uint8_t t_end;
    uint8_t t_start;
    double bpm;
    uint16_t count;
    uint8_t edge;

    init_debug_uart0();
    init_adc();
    DDRB = 0xFF; //Set 8-bits of port x as outputs

    for (;;)
    {
        result = read_adc(); //get position of an ADC
        if (result > 250)
        {
            if (pulse == 0)
            {
                t_end = t_start;
                t_start = count;
                if (edge)
                {
                    bpm = 60 * 100.0 / (t_end - t_start)
                }
                edge = 1;

                pulse = 1;
            }
            for(;;)
            {
                _delay_ms(10);
               result = read_adc(); //get position of an ADC 
               count += 10;
            }
        }

        printf("bpm = %6.5lf\n", bpm);
    }
}
