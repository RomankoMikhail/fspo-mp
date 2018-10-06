#include "arch/ports.h"

// 0 - 14 байта - время

// 0x70 - отправить номер байта, которые хотим
// 0x71 - получить байт

#define NMI_ENABLED 0

int cmos_get_update_flag()
{
      outb(0x70, 0x0A);
      return (inb(0x71) & 0x80);
}

unsigned char cmos_get_byte(unsigned char reg)
{
	outb(0x70, (NMI_ENABLED << 7) | reg);
	return inb(0x71);
}

void cmos_set_byte(unsigned char reg, unsigned char val)
{
	outb(0x70, reg);
	outb(0x71, val);
}
