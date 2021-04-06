#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_adc(void)
{
    ADMUX = 0x00;
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
}

uint16_t read_adc(void)
{
    ADCSRA |= _BV(ADSC);
    while (ADCSRA & _BV(ADSC))
        ;

    return ADC;
}

void channel_adc(uint8_t a)
{
    ADMUX |= (a & 0x07);
}

int main(void)
{
    uint16_t result;
    uint16_t va = 93; //0.3V
    uint16_t vp = 62; //0.2V
    uint8_t pulse = 0;
    uint32_t time = 0;
    uint32_t t_start = 0;
    uint32_t t_end = 0;
    uint8_t edge = 0;
    double bpm;
    uint8_t led = 0;

    init_debug_uart0();
    init_adc();
    channel_adc(2);

    DDRB |= _BV(PB7);
    PORTB &= ~_BV(PB7);

    for (;;)
    {
        result = read_adc(); //get position of an ADC

        if (result < vp)
        {
            pulse = 0;
        }

        if (result > va)
        {
            if (pulse == 0)
            {
                t_end = t_start;
                t_start = time;
                if (edge)
                {
                    bpm = 60.0*100.0 / (t_end - t_start);
                    printf("%4.1f bpm\n", bpm);
                }
                edge = 1;
                led = 10;
                PORTB |= _BV(PB7);
                pulse = 1;
            }

            _delay_ms(10);
            if (led != 0)
            {
                led--;
            }
            else
            {
                PORTB &= ~_BV(PB7);
            }

            time++;
        }
    }
}