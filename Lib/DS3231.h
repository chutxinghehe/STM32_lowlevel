#ifndef __DS3231_H
#define __DS3231_H

#include "I2C.h"

#define DS3231_Address		0x68

uint8_t dec_to_bcd(uint8_t dec);
uint8_t bcd_to_dec(uint8_t bcd);

void get_time(uint8_t *hour, uint8_t *min, uint8_t *sec);
void set_time(uint8_t hour, uint8_t min, uint8_t sec);

#endif