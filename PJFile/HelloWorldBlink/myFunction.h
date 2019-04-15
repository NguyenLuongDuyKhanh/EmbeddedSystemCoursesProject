/*
 * myFunction.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Khanh
 */

#ifndef MYFUNCTION_H_
#define MYFUNCTION_H_

#include "msp430g2231.h"
#include <msp430.h>

#define ledRedOn P1OUT |= BIT0
#define ledGreenOn P1OUT |= BIT6
#define ledRedOff P1OUT &= ~BIT0
#define ledGreenOff P1OUT &= ~BIT6

void interuptconfig();
void IOconfig();
void clockconfig();

#endif /* MYFUNCTION_H_ */


