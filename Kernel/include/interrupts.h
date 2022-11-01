 /*
 *   interrupts.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <idtLoader.h>

void systemCallsRoutine(void);
void timerRoutine(void);
void keyboardRoutine(void);
void _exception0Handler(void);
void _exception6Handler(void);
void _exception8Handler(void);

void _cli(void);

void _sti(void);

void _hlt(void);

void picMasterMask(uint8_t mask);
void picSlaveMask(uint8_t mask);
	
#endif /* INTERRUPS_H_ */
