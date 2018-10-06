/*
 * serial.h
 *
 *  Created on: 3 мая 2018 г.
 *      Author: mikhail
 */

#ifndef KERNEL_INCLUDE_ARCH_SERIAL_H_
#define KERNEL_INCLUDE_ARCH_SERIAL_H_
#include "ports.h"

enum serial_ports
{
	COM1 = 0x3f8, COM2 = 0x2f8, COM3 = 0x3e8, COM4 = 0x2e8
};

void serial_init(enum serial_ports port);
int serial_received(enum serial_ports port);
int serial_read(enum serial_ports port);
int serial_busy(enum serial_ports port);
void serial_write(enum serial_ports port, char a);
void serial_puts(enum serial_ports port, char *str);

#endif /* KERNEL_INCLUDE_ARCH_SERIAL_H_ */
