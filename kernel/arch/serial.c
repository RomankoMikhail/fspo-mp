#include "arch/serial.h"

void serial_init(enum serial_ports port)
{
	outb(port + 1, 0x00);    // Disable all interrupts
	outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(port + 0, 0x0C);    // Set divisor to 3 (lo byte) 9600 baud
	outb(port + 1, 0x00);    //                  (hi byte)
	outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int serial_received(enum serial_ports port)
{
	return inb(port + 5) & 1;
}

int serial_read(enum serial_ports port)
{
	while (serial_received(port) == 0);
	return inb(port);
}

int serial_busy(enum serial_ports port)
{
	return inb(port + 5) & 0x20;
}

void serial_write(enum serial_ports port, char a)
{
	while (serial_busy(port) == 0);

	outb(port, a);
}

void serial_puts(enum serial_ports port, char *str)
{
	while(*str)
	{
		serial_write(port, *str);
		str++;
	}
}
