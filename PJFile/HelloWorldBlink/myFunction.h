/*
 * myFunction.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Khanh
 */

#ifndef MYFUNCTION_H_
#define MYFUNCTION_H_

//build in library
#include "msp430g2553.h"
#include <msp430.h>

//for easier GPIO control
#define ledRedOn P1OUT |= BIT0
#define ledGreenOn P1OUT |= BIT6
#define ledRedOff P1OUT &= ~BIT0
#define ledGreenOff P1OUT &= ~BIT6

//for UART
#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1



//the functions
void interuptconfig();
void IOconfig();
void clockconfig();
void timerconfig();
void UARTconfig();
void UARTTx(unsigned char byte);


#endif /* MYFUNCTION_H_ */


