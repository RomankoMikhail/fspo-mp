#ifndef __KERNEL_SYSTEM_H_
#define __KERNEL_SYSTEM_H_

typedef int size_t;
typedef unsigned long   uint32_t;
typedef unsigned short  uint16_t;
typedef unsigned char   uint8_t;
typedef signed long     int32_t;
typedef signed short    int16_t;
typedef signed char     int8_t;

enum serial_ports
{
	COM1 = 0x3f8, COM2 = 0x2f8, COM3 = 0x3e8, COM4 = 0x2e8
};

enum vesa_attribute 
{
    IS_MODE_SUPPORTED = 0x0001,
    IS_OPTIONAL_INFO_AVAILABLE = 0x0002,
    IS_BIOS_OUTPUT_SUPPORTED = 0x0004,
    IS_COLOR = 0x0008,
    IS_TEXT_MODE = 0x0010,
    IS_NOT_VGA_COMPATIBLE = 0x0020,
    IS_BANK_SWITCHED_SUPPORTED = 0x0040,
    IS_LINEAR_MODE_SUPPORTED = 0x0080,
    IS_DOUBLE_SCAN_AVAILABLE = 0x0100,
    IS_INTERLACED_MODE_AVAILABLE = 0x0200,
    IS_HARDWARE_TRIPLE_BUFFERING_AVAILABLE = 0x0400,
    IS_HARDWARE_STEREOSCOPIC_AVAILABLE = 0x0800,
    IS_DUAL_DISPLAY_START_SUPPORT = 0x1000
};

enum vesa_window_attribute
{
    IS_EXSIST = 0x01,
    IS_READABLE = 0x02,
    IS_WRITABLE = 0x04
};

enum vesa_memory_model
{
    TEXT,
    CGA,
    HGC,
    EGA,
    PACKED_PIXEL,
    SEQU_256,
    DIRECT_COLOR,
    YUV
};

typedef struct vesa_mode_info_s
{
    // Basic VESA
    uint16_t attributes;
    uint8_t window_a_attributes;
    uint8_t window_b_attributes;
    uint16_t window_granularity;
    uint16_t window_size;
    uint16_t window_a_start;
    uint16_t window_b_start;
    uint32_t window_function;
    uint16_t bytes_per_scanline;
    // VBE 1.0+
    uint16_t width;
    uint16_t height;
    uint8_t width_char_cell;
    uint8_t height_char_cell;
    uint8_t planes;
    uint8_t bits_per_pixel;
    uint8_t banks;
    uint8_t memory_model_type;
    uint8_t bank_size;
    uint8_t image_pages;
    uint8_t reserved1;
    // VBE 1.2+
    uint8_t red_mask_size;
    uint8_t red_field_pos;
    uint8_t green_mask_size;
    uint8_t green_field_pos;
    uint8_t blue_mask_size;
    uint8_t blue_field_pos;
    uint8_t reserved_mask_size;
    uint8_t reserved_field_pos;
    uint8_t direct_color_mode;
    // VBE 2.0+
    uint32_t linear_address;
    uint32_t offscreen_address;
    uint16_t offscreen_size;

} __attribute__((packed)) vesa_mode_info_t;

typedef struct video_info_s
{
    uint16_t width, height;
    uint8_t bpp;
    uint8_t * memory;
} video_info_t;

typedef struct regs
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;    
} regs_t;

void * memset(void *dest, int val, size_t n);
int32_t _absi32(int32_t val);

void gdt_init (void);
void gdt_set_gate (int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void idt_init (void);
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void irq_init(void);
void irq_install_handler(int irq, void (*handler)(regs_t *r));
void irq_uninstall_handler(int irq);

void isrs_init(void);

void serial_init(enum serial_ports port);
int serial_received(enum serial_ports port);
int serial_read(enum serial_ports port);
int serial_busy(enum serial_ports port);
void serial_write(enum serial_ports port, const char a);
void serial_puts(enum serial_ports port, const char *str);

void video_init(const video_info_t fbinfo);
void video_draw_line(int x1, int y1,int x2, int y2, uint32_t clr);
void video_draw_rect(int x, int y, int w, int h, uint32_t clr);
int video_draw_font(int x, int y, int ch, uint32_t clr);

uint32_t color(uint8_t red, uint8_t blue, uint8_t green);

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

#endif