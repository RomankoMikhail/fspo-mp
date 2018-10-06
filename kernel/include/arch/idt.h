#ifndef KERNEL_INCLUDE_IDT_H_
#define KERNEL_INCLUDE_IDT_H_

#include <stdint.h>

#define selector_form(rpl, table, index) (rpl & 3) | (table & 1) << 2 | index << 3

struct idt_desc {
	uint16_t offset_1; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	uint8_t zero;      // unused, set to 0
	uint8_t type_attr; // type and attributes, see below
	uint16_t offset_2; // offset bits 16..31
}__attribute__((packed));

enum idt_type {
	TASK_GATE_32 = 0x5,
	INTERRUPT_GATE_16 = 0x6,
	TRAP_GATE_16 = 0x7,
	INTERRUPT_GATE_32 = 0xe,
	TRAP_GATE_32 = 0xf
};

void idt_set(struct idt_desc *desc, void *isr, uint16_t val);

/*void idt_set(struct idt_desc *desc, void *isr, uint16_t selector,
		enum idt_type type) {
	desc->offset_1 = isr & 0xffff;
	desc->offset_2 = isr & 0xffff0000;
	desc->zero = 0;
	desc->type_attr = type;
	desc->selector = selector;
}*/



#endif /* KERNEL_INCLUDE_IDT_H_ */
