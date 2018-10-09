#include <system.h>

#define bitRead(val, bit) ((val >> bit) & 1)
#define bitSet(val, bit) (val | (1 << bit)
#define bitClear(val, bit) (val & (~(1 << bit)))

video_info_t info;
uint32_t video_color;

uint32_t font[] = {
		0x00000000, 0x00000000, 0x00000000,
		0x1e1e0c00, 0x000c0c1e, 0x00000c0c,
		0x66666600, 0x00000024, 0x00000000,
		0x7f363600, 0x7f363636, 0x00003636,
		0x033e0c0c, 0x30301e03, 0x000c0c1f,
		0x23000000, 0x060c1833, 0x00003133,
		0x1b1b0e00, 0x737b5f0e, 0x00006e3b,
		0x0c0c0c00, 0x00000006, 0x00000000,
		0x0c183000, 0x04060606, 0x0030180c,
		0x180c0600, 0x18303030, 0x0000060c,
		0x66000000, 0x663cff3c, 0x00000000,
		0x18000000, 0x18187e18, 0x00000000,
		0x00000000, 0x00000000, 0x00061c1c,
		0x00000000, 0x00007f00, 0x00000000,
		0x00000000, 0x00000000, 0x00001c1c,
		0x60400000, 0x060c1830, 0x00000103,
		0x73633e00, 0x676f6b7b, 0x00003e63,
		0x0f0c0800, 0x0c0c0c0c, 0x00003f0c,
		0x33331e00, 0x060c1830, 0x00003f33,
		0x30331e00, 0x30301c30, 0x00001e33,
		0x3c383000, 0x307f3336, 0x00007830,
		0x03033f00, 0x3030331f, 0x00001e33,
		0x03061c00, 0x33331f03, 0x00001e33,
		0x63637f00, 0x06183060, 0x00000606,
		0x33331e00, 0x33331e33, 0x00001e33,
		0x33331e00, 0x18183e33, 0x00000e0c,
		0x1c000000, 0x1c00001c, 0x0000001c,
		0x1c000000, 0x1c00001c, 0x000c181c,
		0x0c183000, 0x0c060306, 0x00003018,
		0x00000000, 0x007e007e, 0x00000000,
		0x180c0600, 0x18306030, 0x0000060c,
		0x30331e00, 0x000c0c18, 0x00000c0c,
		0x63633e00, 0x037b7b7b, 0x00003e03,
		0x331e0c00, 0x333f3333, 0x00003333,
		0x66663f00, 0x66663e66, 0x00003f66,
		0x63663c00, 0x63030303, 0x00003c66,
		0x66361f00, 0x66666666, 0x00001f36,
		0x06467f00, 0x06263e26, 0x00007f46,
		0x06467f00, 0x06263e26, 0x00001f06,
		0x63663c00, 0x63730303, 0x00007c66,
		0x33333300, 0x33333f33, 0x00003333,
		0x0c0c1e00, 0x0c0c0c0c, 0x00001e0c,
		0x30307800, 0x33313030, 0x00001e33,
		0x36666700, 0x36361e36, 0x00006766,
		0x06060f00, 0x66460606, 0x00007f66,
		0x7f776300, 0x63636b7f, 0x00006363,
		0x67636300, 0x737b7f6f, 0x00006363,
		0x63361c00, 0x63636363, 0x00001c36,
		0x66663f00, 0x06063e66, 0x00000f06,
		0x63361c00, 0x7b736363, 0x0078303e,
		0x66663f00, 0x66363e66, 0x00006766,
		0x33331e00, 0x33180e03, 0x00001e33,
		0x0c2d3f00, 0x0c0c0c0c, 0x00001e0c,
		0x33333300, 0x33333333, 0x00001e33,
		0x33333300, 0x33333333, 0x00000c1e,
		0x63636300, 0x366b6b63, 0x00003636,
		0x33333300, 0x331e0c1e, 0x00003333,
		0x33333300, 0x0c0c1e33, 0x00001e0c,
		0x19737f00, 0x46060c18, 0x00007f63,
		0x0c0c3c00, 0x0c0c0c0c, 0x00003c0c,
		0x03010000, 0x30180c06, 0x00004060,
		0x30303c00, 0x30303030, 0x00003c30,
		0x63361c08, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xff000000,
		0x00180c0c, 0x00000000, 0x00000000,
		0x00000000, 0x333e301e, 0x00006e33,
		0x06060700, 0x6666663e, 0x00003b66,
		0x00000000, 0x0303331e, 0x00001e33,
		0x30303800, 0x3333333e, 0x00006e33,
		0x00000000, 0x033f331e, 0x00001e33,
		0x06361c00, 0x06061f06, 0x00000f06,
		0x00000000, 0x3333336e, 0x1e33303e,
		0x06060700, 0x66666e36, 0x00006766,
		0x00181800, 0x1818181e, 0x00007e18,
		0x00303000, 0x3030303e, 0x1e333330,
		0x06060700, 0x360e3666, 0x00006766,
		0x18181e00, 0x18181818, 0x00007e18,
		0x00000000, 0x6b6b6b3f, 0x0000636b,
		0x00000000, 0x3333331f, 0x00003333,
		0x00000000, 0x3333331e, 0x00001e33,
		0x00000000, 0x6666663b, 0x0f063e66,
		0x00000000, 0x3333336e, 0x78303e33,
		0x00000000, 0x066e7637, 0x00000f06,
		0x00000000, 0x1806331e, 0x00001e33,
		0x06040000, 0x0606063f, 0x00003c76,
		0x00000000, 0x33333333, 0x00006e33,
		0x00000000, 0x33333333, 0x00000c1e,
		0x00000000, 0x6b6b6363, 0x00003636,
		0x00000000, 0x1c1c3663, 0x00006336,
		0x00000000, 0x66666666, 0x0f18303c,
		0x00000000, 0x0618313f, 0x00003f23,
		0x0c0c3800, 0x0c060306, 0x0000380c,
		0x18181800, 0x18180018, 0x00001818,
		0x0c0c0700, 0x0c183018, 0x0000070c,
		0x735bce00, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000
};

void video_draw_pixel(int x, int y) {
	int *p = (int*) (info.memory + (y * info.width + x) * (info.bpp >> 3));
	*p = (video_color & 0x00ffffff) | (*p & 0xff000000);
}

void video_init(const video_info_t fbinfo)
{
    info = fbinfo;
    video_draw_rect(0, 0, info.width, info.height, color(0, 0, 0));
}

void drawLineLow(	int x0, int y0,
					int x1, int y1) { //рисуем линию в низ влево
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}
	int D = 2 * dy - dx;
	int y = y0;
	int x;

	for (x = x0; x < x1; x++) { //рисуем линию в низ вправо
		video_draw_pixel(x, y);
		if (D > 0) {
			y += yi;
			D -= 2 * dx;
		}
		D += 2 * dy;
	}
}

void drawLineHigh(	int x0, int y0,
					int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}
	int D = 2 * dx - dy;
	int x = x0;
	int y;
	for (y = y0; y < y1; y++) {
		video_draw_pixel(x, y);
		if (D > 0) {
			x += xi;
			D -= 2 * dy;
		}
		D += 2 * dx;
	}
}

void video_draw_line(	int x1, int y1,
						int x2, int y2,
						uint32_t clr)
{
    video_color = clr;
    if (_absi32(y2 - y1) < _absi32(x2 - x1)) {
		if (x1 > x2) {
			drawLineLow(x2, y2, x1, y1);
		} else {
			drawLineLow(x1, y1, x2, y2);
		}
	} else {
		if (y1 > y2) {
			drawLineHigh(x2, y2, x1, y1);
		} else {
			drawLineHigh(x1, y1, x2, y2);
		}
	}
}

void video_draw_rect(	int x, int y, 
						int w, int h,
						uint32_t clr)
{
    int i, j;
    video_color = clr;
    for(j = y; j <= y + h; j++)
	{
		for(i = x; i <= x + w; i++)
		{
			video_draw_pixel(i, j);
		}
	}
}

int video_draw_font(int x, int y, 
					int ch, uint32_t clr)
{
    if(ch < ' ' || ch > '~')
		return 0;
    video_color = clr;
	int i, j;
	uint32_t *selected = &font[(ch - 0x20) * 3];

	for(j = 0; j < 3; j++)
	{
		for(i = 0; i < 32; i++)
		{
			if(bitRead(selected[j], i))
			{
				int ix, iy;
				ix = x + (i + j * 32) % 8;
				iy = y + (i + j * 32) / 8;
				video_draw_pixel(ix, iy);
			}
		}
	}
	return ch;
}

uint32_t color(uint8_t red, uint8_t blue, uint8_t green)
{
    return ((uint32_t)red) << 16 | ((uint32_t)blue) << 8 | ((uint32_t)green);
}
