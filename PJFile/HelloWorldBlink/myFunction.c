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
