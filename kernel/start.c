#include "arch/serial.h"
#include "arch/gdt.h"
#include "arch/keyboard.h"
#include "arch/monitor.h"
#include "arch/cmos.h"
#include "arch/tty.h"
#include "itoa.h"

struct gdtr_desc gdtr;
uint64_t gdt_entries[5];

struct regs {
	uint32_t eax, ebx, ecx, edx, esi, edi, ebp, esp;
	uint16_t cs, ds, es, ss, fs, gs;
};

#define panic(msg) _panic(dump_regs(), msg)
void _panic(struct regs reg, char *msg);

struct regs dump_regs(void) {
	struct regs r = { 0 };
	asm("mov %%eax, %0;"::"m"(r.eax));
	asm("mov %%ebx, %0;"::"m"(r.ebx));
	asm("mov %%ecx, %0;"::"m"(r.ecx));
	asm("mov %%edx, %0;"::"m"(r.edx));
	asm("mov %%esi, %0;"::"m"(r.esi));
	asm("mov %%edi, %0;"::"m"(r.edi));
	asm("mov %%ebp, %0;"::"m"(r.ebp));
	asm("mov %%esp, %0;"::"m"(r.esp));
	asm("mov %%cs, %0;"::"m"(r.cs));
	asm("mov %%ds, %0;"::"m"(r.ds));
	asm("mov %%es, %0;"::"m"(r.es));
	asm("mov %%ss, %0;"::"m"(r.ss));
	asm("mov %%fs, %0;"::"m"(r.fs));
	asm("mov %%gs, %0;"::"m"(r.gs));
	return r;
}

void ReadCMOS(unsigned char array[]) {
	unsigned char index;

	for (index = 0; index < 128; index++) {
		array[index] = cmos_get_byte(index);
	}
}

void monitor_puts(int x, int y, char *str) {
	while (*str) {
		monitor_draw_font(x, y, *str);
		x += 8;
		str++;
	}
}

int bcd_to_number(char val)
{
	return ((val & 0xF0) >> 4) * 10 + (val & 0xF);
}

void _start() {

	serial_init(COM1);
	serial_puts(COM1, "Setting up GDT: ");
	gdt_entries[0] = 0;
	gdt_entries[1] = 0x00CF9A000000FFFF;
	gdt_entries[2] = 0x00CF92000000FFFF;
	gdt_entries[3] = 0x00CFFA000000FFFF;
	gdt_entries[4] = 0x00CFF2000000FFFF;
	gdt_set(gdt_entries, sizeof(gdt_entries));

	serial_puts(COM1, "ok\n");

	serial_puts(COM1, "Initializing monitor");
	tty_init();
	tty_set_color(TTY_WHITE);
	/*monitor_init();
	 monitor_set_color(0xffffffff);

	 int x = 0, y = 0, i;
	 for (i = ' '; i <= '~'; i++) {
	 monitor_draw_font((i - ' ') * 8, 0, i);
	 }
	 y += 12;

	 serial_write(COM1, '\n');
	 */
	unsigned char secs, min, hour, date, month;

	char str[32] = { 0 };

	while (cmos_get_update_flag());
	secs = bcd_to_number(cmos_get_byte(CMOS_SECONDS));
	min = bcd_to_number(cmos_get_byte(CMOS_MINUTES));
	hour = bcd_to_number(cmos_get_byte(CMOS_HOURS));
	date = bcd_to_number(cmos_get_byte(CMOS_DAY));
	month = bcd_to_number(cmos_get_byte(CMOS_MONTH));

	itoa_p(hour, str, 10, 2);
	tty_puts(str);
	tty_putc(':');

	itoa_p(min, str, 10, 2);
	tty_puts(str);
	tty_putc(':');

	itoa_p(secs, str, 10, 2);
	tty_puts(str);
	tty_putc(' ');

	itoa_p(date, str, 10, 2);
	tty_puts(str);
	tty_putc('-');

	itoa_p(month, str, 10, 2);
	tty_puts(str);
	tty_putc('\n');

	int base_memory = cmos_get_byte(0x15) | (cmos_get_byte(0x16) << 8);
	int extended_memory = cmos_get_byte(0x17) | (cmos_get_byte(0x18) << 8);
	int drive_0_type = cmos_get_byte(0x19);
	int drive_1_type = cmos_get_byte(0x1a);

	int floppy = cmos_get_byte(0x10);

	int floppy_b = floppy & 0xF;
	int floppy_a = (floppy & 0xF0) >> 4;

	itoa(base_memory, str, 10);
	tty_puts("Base memory:");
	tty_puts(str);
	tty_putc('\n');

	itoa(extended_memory, str, 10);
	tty_puts("Extended memory:");
	tty_puts(str);
	tty_putc('\n');

	itoa(drive_0_type, str, 10);
	tty_puts("HDD0:");
	tty_puts(str);
	tty_putc('\n');

	itoa(drive_1_type, str, 10);
	tty_puts("HDD1:");
	tty_puts(str);
	tty_putc('\n');

	tty_puts("Floppy A - ");
	switch (floppy_a) {
	case 0:
		tty_puts("No drive");
		break;
	case 1:
		tty_puts("360 KB 5.25 Drive");
		break;
	case 2:
		tty_puts("1.2 MB 5.25 Drive");
		break;
	case 3:
		tty_puts("720 KB 3.5 Drive");
		break;
	case 4:
		tty_puts("1.44 MB 3.5 Drive");
		break;
	case 5:
		tty_puts("2.88 MB 3.5 drive");
		break;
	}
	tty_putc('\n');

	tty_puts("Floppy B - ");
	switch (floppy_b) {
	case 0:
		tty_puts("No drive");
		break;
	case 1:
		tty_puts("360 KB 5.25 Drive");
		break;
	case 2:
		tty_puts("1.2 MB 5.25 Drive");
		break;
	case 3:
		tty_puts("720 KB 3.5 Drive");
		break;
	case 4:
		tty_puts("1.44 MB 3.5 Drive");
		break;
	case 5:
		tty_puts("2.88 MB 3.5 drive");
		break;
	}
	tty_putc('\n');

	while (1) {
		int scan = keyboard_pull();

		if (scan > 0) {
			serial_write(COM1, keyboard_toascii(scan));

			if (scan == SCAN_ENTER_PRESSED) {
				tty_putc('\n');
			}
			if (scan <= 0x80)
				tty_putc(keyboard_toascii(scan));
		}
	}
	// Army of snek(er)s ~~> ~~> ~~> ~~>
	serial_puts(COM1, "Setting up IDT: ");
	panic("IDT setup not implemented");
	serial_puts(COM1, "ok\n");

	panic("Kernel terminated");
	return;
}

void serial_hex(uint32_t val) {
	static char alpha[] = "0123456789abcdef";
	static char buf[8];

	int i = 7;
	while (i >= 0) {
		int rem = val % 16;
		val /= 16;
		buf[i--] = alpha[rem];
	}
	i = 0;
	while (i < 8)
		serial_write(COM1, buf[i++]);
}

void _panic(struct regs reg, char *msg) {
	serial_init(COM1);
	serial_puts(COM1, "\n\n\nPANIC: ");
	serial_puts(COM1, msg);
	serial_puts(COM1, "\nEAX: ");
	serial_hex(reg.eax);
	serial_puts(COM1, "\nEBX: ");
	serial_hex(reg.ebx);
	serial_puts(COM1, "\nECX: ");
	serial_hex(reg.ecx);
	serial_puts(COM1, "\nEDX: ");
	serial_hex(reg.edx);
	serial_puts(COM1, "\nESI: ");
	serial_hex(reg.esi);
	serial_puts(COM1, "\nEDI: ");
	serial_hex(reg.edi);
	serial_puts(COM1, "\nEBP: ");
	serial_hex(reg.ebp);
	serial_puts(COM1, "\nESP: ");
	serial_hex(reg.esp);

	serial_puts(COM1, "\nCS: ");
	serial_hex(reg.cs);
	serial_puts(COM1, "\nDS: ");
	serial_hex(reg.ds);
	serial_puts(COM1, "\nES: ");
	serial_hex(reg.es);
	serial_puts(COM1, "\nSS: ");
	serial_hex(reg.ss);
	serial_puts(COM1, "\nFS: ");
	serial_hex(reg.fs);
	serial_puts(COM1, "\nGS: ");
	serial_hex(reg.gs);
	serial_puts(COM1, "\n");

	asm("hlt;");
}
