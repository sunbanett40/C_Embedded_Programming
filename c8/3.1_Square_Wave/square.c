/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>

#define FREQ 262
#define TONE_PRESCALER 8

/*
| Signal 	| Port	| Pin	   |
|-----------+--------+--------|
| Tone Osc	| D 	   | 5 	   |
*/

unsigned long toneClock; /* set at timer initialisation and used
                              to calculate TOP when setting frequency */

void init_tone(void);
void tone(uint16_t frequency);

int main(void)
{

   init_tone();

   for (;;)
      tone(FREQ);
}

/* 
init_tone ---
Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
   DDRD |= _BV(PD5);    /* enable ouput driver for OC1A */
   TCCR1A = _BV(COM1A0) /* toggle OC1A on match */
         | _BV(WGM10);  /* frequency (f) correct PWM, */
   TCCR1B = _BV(WGM13)  /* varying f with OCR1A */
         | _BV(CS11);   /* prescaler set to 8 */
}

/* 
tone ---
Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
   /* 
   We rely on the compiler to substitute the constant part of the expression.
   1/2 for symmetric PWM & 1/2 for toggle output
   */
   OCR1A = (uint16_t)(F_CPU / (2 * 2 * TONE_PRESCALER) / frequency);
}
