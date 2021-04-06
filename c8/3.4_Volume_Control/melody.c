/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"
#include "music.h"

/* Pin configuration
 *       progress LED:  PB7
*/

/*
| Signal 	| Port	| Pin	|
|-----------+-------+-------|
| Tone Osc	| D   	| 5 	|
| PWM		| D		| 6		|
| Inv PWM	| D		| 7		|
*/

#define STEP_DELAY_MS 450
#define TONE_PRESCALER 8
#define VOLUME_PERCENT 50

/* Inaudible frequencies used to indicate state for melody2freq: */
#define M2F_END 0
#define M2F_REST 1
#define M2F_UNKOWN 2

void init_tone(void);
void init_volume(void);
void tone(uint16_t frequency);
void volume(uint8_t x);
uint16_t melody2freq(const char *abc_melody);

int main()
{
	uint16_t f;

	DDRB |= _BV(PB7); /* LED */
	DDRD |= _BV(PD0); /* Trigger*/
	init_tone();
	init_volume();
	int vol = 1;

	for (;;)
	{
		melody2freq(melody); /* initialise  */
		while ((f = melody2freq(NULL)) != M2F_END)
		{
			if (f == M2F_UNKOWN)
			{
				continue; /* skip unknown symnols */
			}

			tone(f);
			volume(vol);
			_delay_ms(STEP_DELAY_MS);
			PORTB ^= _BV(PB7); 		/* toggle LED */
			
		}
		_delay_ms(STEP_DELAY_MS);
		_delay_ms(STEP_DELAY_MS);

		vol++;
	}
}

/* 
init_tone ---
Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
	DDRD |= _BV(PD5);	   /* enable ouput driver for OC1A */
	TCCR1A = _BV(COM1A0)   /* toggle OC1A on match */
			 | _BV(WGM10); /* frequency (f) correct PWM, */
	TCCR1B = _BV(WGM13)	   /* varying f with OCR1A */
			 | _BV(CS11);  /* prescaler set to 8 */
}

void init_volume(void)
{
	DDRD |= _BV(PD6);    
    DDRD |= _BV(PD7);    

    TCCR2A = _BV(COM2A1) /* toggle OC2A on match */
         | _BV(WGM21)    /* fast PWM, */
         | _BV(WGM20);   /* fast PWM, */
    TCCR2B = _BV(CS20);  /* prescaler set to 1 */
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

void volume(uint8_t x)
{	
	uint8_t vol = (256*(x/100));
	OCR2A = vol;
}

/* melody2freq ---
 *   If called with a string of abc music notation
 *   initialise with this string.
 *   If called with a null-pointer, return next
 *   frequency.
 *
 *   Low frequencies which are not part of the
 *   the tone scale are returned to report state.
 *
 *   The folowing is a very crude implementation
 *   of an abc-player.
 *
 */
uint16_t melody2freq(const char *m)
{
	static const char *melody;
	static uint16_t pos;
	static uint8_t scale_index;

	if (m != NULL)
	{ /* initialization */
		melody = m;
		pos = 0;
		return M2F_END; /* to be ignored */
	}

	if (melody[++pos] == '\0')
		return M2F_END;

	switch (melody[pos])
	{
	case 'c':
	case 'C':
	{
		scale_index = ET_SCALE_C;
		break;
	}
	case 'd':
	case 'D':
	{
		/* 2 semitones above C */
		scale_index = ET_SCALE_C + 2;
		break;
	}
	case 'e':
	case 'E':
	{
		/* 4 semitones above C */
		scale_index = ET_SCALE_C + 4;
		break;
	}
	case 'f':
	case 'F':
	{
		/* 5 semitones above C */
		scale_index = ET_SCALE_C + 5;
		break;
	}
	case 'g':
	case 'G':
	{
		/* 7 semitones above C */
		scale_index = ET_SCALE_C + 7;
		break;
	}
	case 'a':
	case 'A':
	{
		/* 9 semitones above C */
		scale_index = ET_SCALE_C + 9;
		break;
	}
	case 'b':
	case 'B':
	{
		/* 11 semitones above C */
		scale_index = ET_SCALE_C + 11;
		break;
	}
	default:
	{ /* unknown symbol --> no change */
		return M2F_UNKOWN;
	}
	}

	if (melody[pos] > 'Z')
	{					   /* lower case chars have higher ASCII codes than A-Z */
		scale_index += 12; /* shift one octave up */
	}

	return et_scale[scale_index];
}