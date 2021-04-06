/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */

#include "spi.h"

void init_pot(void)
{
    /* TODO: Code to initiliase interface */
    init_spi_master();
}

void decXpot(void)
{
    /* TODO: Code to decrement first pot by 1 */
    uint8_t decx = 0x08;    //0000 1000
    spi_tx(decx);
}

void incXpot(void)
{
    /* TODO: Code to increment first pot by 1 */
    uint8_t incx = 0x04;    //0000 0100
    spi_tx(incx);
}

void decYpot(void)
{
    /* TODO: Code to decrement second pot by 1 */
    uint8_t decy = 0x18;    //0001 1000
    spi_tx(decy);
}

void incYpot(void)
{
    /* TODO: Code to increment second pot by 1 */
    uint8_t incy = 0x14;    //0001 0100
    spi_tx(incy);
}

void setXpot(uint8_t x)
{
    /* TODO: Code to set first pot to a value between 0 and 255 */
    uint8_t setx = 0x00;    //0000 00nn nnnn nnnn
    spi_tx(setx);
    spi_tx(x);
}

void setYpot(uint8_t y)
{
    /* TODO: Code to set second pot to a value between 0 and 255 */
    uint8_t sety = 0x10;    //0001 00nn nnnn nnnn
    spi_tx(sety);
    spi_tx(y);
}

