#include <avr/io.h>
#include "spi.h"
#include "digitalPot.h"

int main(void)
{
    uint8_t i;
    init_pot();

    for(;;)
    {
        setXpot(0x00); 
        setYpot(0x00);

       for(i=0; i <= 255; i++)
       {
           incXpot();
           incYpot();
       }
    }
}