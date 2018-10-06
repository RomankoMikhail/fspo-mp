#ifndef KERNEL_INCLUDE_ARCH_GDT_H_
#define KERNEL_INCLUDE_ARCH_GDT_H_

#include <stdint.h>

struct gdtr_desc
{
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));


extern void gdt_set(void *gdt, uint32_t size);

#endif /* KERNEL_INCLUDE_ARCH_GDT_H_ */
