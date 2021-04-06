/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 */
#include "i2c.h"
#include "RTCC.h"

void init_clock(void)
{
    /* TODO: Code to initiliase interface and start clock */

    init_i2c_master();
    i2c_start();
    i2c_tx(RTCC_ADDR | I2C_WRITE);
    i2c_tx(0x00);
    i2c_tx(1<<7);
    i2c_stop();
}

void set_time(rtcc t)
{
    /* TODO: Code to set time to value in t */
    i2c_start();
    i2c_tx(RTCC_ADDR | I2C_WRITE);
    i2c_tx(0x00);
    i2c_tx(1<<7 | t.ten_seconds << 4 | t.seconds);
    i2c_tx(t.ten_minutes << 4 | t.minutes);
    i2c_tx(t.ten_hours << 4 | t.hours);
    i2c_stop();
}

rtcc get_time()
{
    /* TODO: Code to get time from RTCC and return it in an rtcc struct */
}

