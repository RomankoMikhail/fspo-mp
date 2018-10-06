#include "arch/monitor.h"
#include "arch/tty.h"

#define MAX_WIDTH 128
#define MAX_HEIGHT 64

int tty_x, tty_y;
int tty_color;

void tty_init()
{
	monitor_init();
}

void tty_set_color(int color)
{
	tty_color = color;
	monitor_set_color(color);
}

void tty_set_position(int x, int y)
{
	tty_x = x;
	tty_y = y;
}

int tty_get_x_position()
{
	return tty_x;
}

int tty_get_y_position()
{
	return tty_y;
}

void tty_putc(char sym)
{
	int tc;
	switch(sym)
	{
	case '\n':
		tty_y++;
		tty_x = 0;
		break;
	case '\b':
		if(tty_x == 0)
		{
			tty_y --;
			tty_x = MAX_WIDTH - 1;
		}
		else
		{
			tty_x --;
		}
		tc = tty_color;
		monitor_set_color(TTY_BLACK);
		monitor_draw_rect(tty_x * 8, tty_y * 12, 8, 12);
		monitor_set_color(tc);
		break;
	default:
		monitor_draw_font(tty_x * 8, tty_y * 12, sym);
		tty_x++;
	}

	if(tty_x >= MAX_WIDTH)
	{
		tty_x = 0;
		tty_y++;
	}
}

void tty_puts(char *str)
{
	while(*str)
	{
		tty_putc(*str);
		str++;
	}
}
