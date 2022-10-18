 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <idtLoader.h>

void _irq00Handler(void);
void _irq01Handler(void);

void _cli(void);

void _sti(void);

void picMasterMask(uint8_t mask);

#endif /* INTERRUPS_H_ */
