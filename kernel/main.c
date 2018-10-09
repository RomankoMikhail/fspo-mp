#include <system.h>

int main (void)
{
    const char ready_str[] = "Ready\n\r";
    asm volatile ( "cli" );

    serial_init(COM1);
    serial_puts(COM1, "Setting up GDT\n\r");
    gdt_init();

    serial_puts(COM1, "Setting up IDT\n\r");
    idt_init();

    serial_puts(COM1, "Setting up IRQ\n\r");
    irq_init();

    serial_puts(COM1, "Setting up ISRS\n\r");
    isrs_init();
    
    serial_puts(COM1, ready_str);
    asm volatile ( "sti" );

    vesa_mode_info_t * vesa_info = (void*)0x500;
    video_info_t fb_info;
    fb_info.bpp = vesa_info->bits_per_pixel;
    fb_info.width = vesa_info->width;
    fb_info.height = vesa_info->height;
    fb_info.memory = (void*)vesa_info->linear_address;

    video_init(fb_info);

    for(int i = 0; ready_str[i]; i++)
        video_draw_font(i * 8, 0, ready_str[i], color(255, 255, 255));

    while(1);
}