/*
 * myFunction.c
 *
 *  Created on: Apr 15, 2019
 *      Author: Khanh
 */



#include "myFunction.h"

void interuptconfig()
{
    __bis_SR_register(GIE);             //enable global interupt
    _BIS_SR(GIE);

     /*BUTTON P1.3*/
    P1IE |= BIT3;                       //Enable interupt on P1.3, the same way on P2IE. =0 is disable
    P1IES |= BIT3;                      //=1 falling egde, =0 interupt at raising edge
    P1IFG &=~ BIT3;                     //clear flag interupt on button, it can't cleajn by itseft so we must do that every time ISR jumb

    /*TIMER*/

}

void IOconfig()
{
    P1DIR |= BIT0 + BIT6;               //for led green (bit6) and led red (bit1) on lauchboard
    P1DIR &= ~BIT3;                     //Button on launchboard
    P1REN |= BIT3;                      //use pull up res on this pin
    P1OUT |= BIT3;                      //cause we use interupt on this pin
    P1OUT |= BIT0 + BIT6;
    //PxSEL and PxSEL2 bit is not use
}

void clockconfig() //chosing clock VLO 12Hz lau vai c*c luon
{
    if (CALBC1_8MHZ == 0xFF)
    {
        while (1);
    }
    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ; //8MHz/1MH/...

    BCSCTL2 |= SELM_0;
}

void timerconfig()
{
    TA0CTL |= TASSEL_2 + MC_2 + TAIE;
    //TA0CTL |= TASSEL_2  + MC_1 + TAIE;              //Upmode
    //TA0CTL |= TASSEL_2  + MC_3  + TAIE;           //Up/downmode

    //TA0CCR0 = 60000;                              //only in MC_1 or MC_3
}

void UARTconfig()
{
    P1SEL = BIT1 + BIT2;        //P1.1 = Rx, P1.2 = Tx
    P1SEL2 = BIT1 + BIT2;       //

    UCA0CTL1 |= UCSWRST;
    ////////////////
    UCA0CTL0 = 0;
    //none parity
    //8bits data
    //1bit stop
    //LSB

    UCA0CTL1 = UCSSEL_2 | UCSWRST;
    ///////////baud 9600
    UCA0MCTL = UCBRS_1 | UCBRS_0 | UCOS16;

    UCA0BR0 = 52;
    UCA0BR1 = 00;
    //////////////
    UCA0CTL1 &= ~UCSWRST;       //reset uart module

    IE2 |= UCA0RXIE;            //UART revc interuppt
}

void UARTTx(unsigned char byte)
{
    while(!(IFG2 & UCA0TXIFG));                             //waiting for ready buffer
    UCA0TXBUF = byte;                                       //tranfer
}

void ADCconfig()
{
    ADC10CTL1 = INCH_5 |ADC10SSEL_0;
    ADC10AE0 = BIT5;
    ADC10CTL0 = SREF_0;
    ADC10CTL0 |= ADC10ON + ENC;
}

unsigned char gettemp()
{
    ADC10CTL0 |= ADC10SC;
    while (ADC10CTL1 & 1);
    return ADC10MEM;
}

int amt1001_gethumidity(float voltage) {
    if(voltage > AMT1001_HUMIDITYVMIN && voltage < AMT1001_HUMIDITYVMAX)
        return (int)(AMT1001_HUMIDITYSLOPE*voltage);
    else
        return -1;
}

/*
 * get temperature based on read voltage
 */


const float amt1001_lookuptable[amt1001_lookuptablesize] = {
        -86.99 , -59.05 , -49.91 , -43.96 , -39.45 , -35.76 , -32.61 , -29.84 , -27.37 , -25.11 , -23.03 , -21.1 , -19.29 , -17.58 , -15.95 , -14.41 , -12.92 , -11.5 , -10.12 , -8.79 , -7.5 , -6.25 , -5.03 , -3.83 , -2.66 , -1.52 , -0.4 , 0.71 , 1.8 , 2.87 , 3.93 , 4.97 , 6.01 , 7.03 , 8.05 , 9.05 , 10.06 , 11.05 , 12.04 , 13.03 , 14.02 , 15 , 15.98 , 16.96 , 17.95 , 18.93 , 19.92 , 20.9 , 21.9 , 22.89 , 23.89 , 24.9 , 25.91 , 26.93 , 27.96 , 29 , 30.05 , 31.11 , 32.19 , 33.27 , 34.37 , 35.49 , 36.63 , 37.78 , 38.95 , 40.14 , 41.36 , 42.6 , 43.87 , 45.17 , 46.5 , 47.86 , 49.26 , 50.7 , 52.18 , 53.71 , 55.29 , 56.92 , 58.62 , 60.38 , 62.22 , 64.14 , 66.15 , 68.26 , 70.49 , 72.84 , 75.34 , 78.01 , 80.87 , 83.95 , 87.3 , 90.96 , 95 , 99.52 , 104.62 , 110.48 , 117.36 , 125.67 , 136.09 , 149.94 , 170.2 , 206.11 , 330.42
};

int amt1001_gettemperature(int adcvalue) {


    float t = 0.0;
    float mint = 0;
    float maxt = 0;

    //return error for invalid adcvalues
    if(adcvalue<amt1001_lookupadcfirst || adcvalue>amt1001_lookupadcfirst+amt1001_lookupadcstep*(amt1001_lookuptablesize-1)) {
        return -1;
    }

    int i = 0;
    int a = amt1001_lookupadcfirst;
    for(i=0; i<amt1001_lookuptablesize; i++) {
        if(adcvalue < a)
            break;
        a += amt1001_lookupadcstep;
    }

    maxt = (amt1001_lookuptable[i]); //highest interval value
    if(i==0)
        mint = maxt;
    else
        mint =(amt1001_lookuptable[i-1]); //smallest interval value
    //do interpolation
    a = a-amt1001_lookupadcstep;
    t = mint + ((maxt-mint)/amt1001_lookupadcstep) * (adcvalue-a);

    return t;
}
