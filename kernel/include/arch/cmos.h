/*
 * cmos.h
 *
 *  Created on: 4 июн. 2018 г.
 *      Author: romanko-mikhail
 */

#ifndef KERNEL_INCLUDE_ARCH_CMOS_H_
#define KERNEL_INCLUDE_ARCH_CMOS_H_

unsigned char cmos_get_byte(unsigned char reg);
void cmos_set_byte(unsigned char reg, unsigned char val);
int cmos_get_update_flag();

enum cmos_registers
{
	CMOS_SECONDS = 0x00,
	CMOS_MINUTES = 0x02,
	CMOS_HOURS = 0x04,
	CMOS_WEEKDAY = 0x06,
	CMOS_DAY = 0x07,
	CMOS_MONTH = 0x08,
	CMOS_YEAR = 0x09
};

#endif /* KERNEL_INCLUDE_ARCH_CMOS_H_ */
