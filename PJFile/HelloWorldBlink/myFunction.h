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
#include "myFunction.h"

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


unsigned int i; //Counter

volatile unsigned char UARTRecvdata;
volatile unsigned int am;
volatile unsigned int adc;
volatile float vol;
volatile unsigned int test[2];

volatile unsigned char Count1s;
volatile unsigned char Seconds;
volatile unsigned char Minutes;
//the functions
void interuptconfig();
void IOconfig();
void clockconfig();
void timerconfig();
void UARTconfig();
void UARTTx(unsigned char byte);
void ADCconfig();

unsigned int gettemp();

//define min and max valid voltage to measure humidity
#define AMT1001_HUMIDITYVMIN 0.0
#define AMT1001_HUMIDITYVMAX 3.3

//slope factor to calculate humidity
#define AMT1001_HUMIDITYSLOPE 23.54

//define min and max valid adc to measure temperature
#define AMT1001_TEMPERATUREVMIN 0.0
#define AMT1001_TEMPERATUREVMAX 0.8

//slope factor to calculate temperature
#define AMT1001_TEMPERATURESLOPE 100.0

//define lookup method variables for temperature
#define amt1001_lookupadcfirst 1 //adc first value of lookup table
#define amt1001_lookupadcstep 10 //step between every table point
#define amt1001_lookuptablesize 103 //size of the lookup table



//functions
int amt1001_gethumidity(float voltage);
int amt1001_gettemperature(int adcvalue);



#endif /* MYFUNCTION_H_ */
