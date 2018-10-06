#ifndef KERNEL_INCLUDE_ARCH_ATA_H_
#define KERNEL_INCLUDE_ARCH_ATA_H_

#include <stdint.h>

extern void ata_chs_read (void * dest, uint16_t cylinder, uint8_t head, uint8_t sector);
extern void ata_chs_write(void * src,  uint16_t cylinder, uint8_t head, uint8_t sector);

#endif /* KERNEL_INCLUDE_ARCH_ATA_H_ */
