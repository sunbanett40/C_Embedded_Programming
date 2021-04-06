#include <avr/io.h>
#include <avr/interrupt.h>

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

ISR(TIMER1_COMPA_vect)
{
    PORTA = segments[count % 10];
    count++;
}

int main(void)
{
    DDRA = 0xFF; //Sets portA as outputs

    /* Timer 1 CTC Mode 4 */
    TCCR1A = 0;
    TCCR1B = _BV(WGM12);
    /* Prescaler /1024 */
    TCCR1B |= _BV(CS12) | _BV(CS10);
    /* Set timeout at 1000ms */
    OCR1A = 11719;
    /* Enable interrupt */
    TIMSK1 |= _BV(OCIE1A);
    sei();
    for (;;);
}