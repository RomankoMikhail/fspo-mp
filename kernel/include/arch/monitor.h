#ifndef KERNEL_ARCH_MONITOR_H_
#define KERNEL_ARCH_MONITOR_H_

void monitor_set_color(int color);
void monitor_init();
void monitor_draw_line(int x1, int y1, int x2, int y2);
void monitor_draw_pixel(int x, int y);
void monitor_draw_rect(int x, int y, int w, int h);
int monitor_draw_font(int x, int y, int ch);

#endif /* KERNEL_ARCH_MONITOR_H_ */
