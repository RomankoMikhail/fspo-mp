/*
 * itoa.h
 *
 *  Created on: 4 июн. 2018 г.
 *      Author: romanko-mikhail
 */

#ifndef KERNEL_INCLUDE_ITOA_H_
#define KERNEL_INCLUDE_ITOA_H_

void itoa(unsigned input, char *buffer, int radix);
void itoa_p(unsigned input, char *buffer, int radix, int padding);

#endif /* KERNEL_INCLUDE_ITOA_H_ */
