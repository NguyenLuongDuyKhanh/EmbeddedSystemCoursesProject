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
    //_BIS_SR(GIE);
    P1IE |= BIT3;                       //Enable interupt on P1.3, the same way on P2IE. =0 is disable
    P1IES |= BIT3;                      //=1 falling egde, =0 interupt at raising edge
    P1IFG &=~ BIT3;                     //clear flag interupt on button, it can't cleajn by itseft so we must do that every time ISR jumb

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
    BCSCTL3 |= XT2S_0 + LFXT1S_2;
    IFG1 &= ~OFIFG;
    BCSCTL2 |= SELM_3;
}
