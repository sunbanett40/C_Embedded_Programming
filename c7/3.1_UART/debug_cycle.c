#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "debug.h"

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

int main(void)
{
    DDRA = 0xFF; //Sets portA as outputs
    init_debug_uart0();

    for (;;)
    {
        int display = count % 10;
        printf("%i", display);
        while (display == 9)
        {
            char str1[1];
            printf("\n");
            fprintf(stderr, "Count overflow\n\r");
            while (fscanf(stdin, "%s", str1) == 0)
            {
            }
            break;
        }
        PORTA = segments[display];
        count++;
        _delay_ms(1000); //Delay by 1 sec
    }
}