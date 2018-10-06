/*
 * tty.h
 *
 *  Created on: 4 июн. 2018 г.
 *      Author: romanko-mikhail
 */

#ifndef KERNEL_INCLUDE_ARCH_TTY_H_
#define KERNEL_INCLUDE_ARCH_TTY_H_


enum tty_colors {
	TTY_RED = 0xff0000,
	TTY_BLUE = 0x0000ff,
	TTY_GREEN = 0x00ff00,
	TTY_WHITE = 0xffffff,
	TTY_BLACK = 0x000000
};


void tty_init();

void tty_set_color(int color);

void tty_set_position(int x, int y);

int tty_get_x_position();

int tty_get_y_position();

void tty_putc(char sym);

void tty_puts(char *str);

#endif /* KERNEL_INCLUDE_ARCH_TTY_H_ */
