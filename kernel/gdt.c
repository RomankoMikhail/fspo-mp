#include <system.h>

extern void gdt_load(void);

typedef struct gdt_ptr_s
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

typedef struct gdt_entry_s
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

gdt_entry_t gdt[3];
gdt_ptr_t gdtptr;

uint8_t gdt_access (uint8_t ring, uint8_t exec, uint8_t dir, uint8_t rw)
{
    /* Setup access flags*/
    return 1 << 7 | ring << 5 | 1 << 4 | exec << 3 | dir << 2 | rw << 1;
}

uint8_t gdt_gran (uint8_t gran, uint8_t size)
{
    /* Setup granularity flags*/
    return gran << 7 | size << 6;
}

void gdt_set_gate (int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_init (void)
{
    gdtptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdtptr.base = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, gdt_access(0, 1, 0, 1), gdt_gran(1, 1));
    gdt_set_gate(2, 0, 0xFFFFFFFF, gdt_access(0, 0, 0, 1), gdt_gran(1, 1));
    
    gdt_load();
}