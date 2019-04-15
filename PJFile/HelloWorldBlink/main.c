#include <msp430.h>
//#include "UART.h"

/**
 * main.c
 */

char Hello[]={'H','e','l','l','o'};
char Hi[]={'H','i'};

void CauhinhClock(void)
{
    //8MHz
    if(CALBC1_8MHZ == 0xFF)
    {
        while(1);
    }
    DCOCTL = 0;
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;


    BCSCTL2 |= SELM_0;
}

void CauhinhLed(void)
{
    P1DIR |= BIT0 + BIT6;
    P1OUT &= ~BIT0;
    P1OUT &= ~BIT6;
}
void CauhinhUART(void)
{
    P1SEL = BIT1 + BIT2;
    P1SEL2 = BIT1 + BIT2;
    UCA0CTL1 |= UCSWRST;

    UCA0CTL0 = 0x00;



    UCA0CTL1 = UCSSEL_2 | UCSWRST;

    UCA0MCTL = UCBRF_1 | UCBRS_0 | UCOS16;

    UCA0BR0 = 52;
    UCA0BR1 = 00;

    UCA0CTL1 &= ~UCSWRST;

    IE2 |= UCA0RXIE;

    _BIS_SR(GIE);
}

void UARTSendByte(unsigned char byte)
{
    while(!(IFG2 & UCA0TXIFG));

    UCA0TXBUF = byte;
}

void UARTSend_String(unsigned char *pData, unsigned char Length)
{
    unsigned char i = 0;
    for(i = 0 ; i < Length;i++)
    {
        UARTSendByte(pData[i]);
    }
}
unsigned int numofchar=0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    CauhinhClock();
    CauhinhLed();
    CauhinhUART();
    //numofchar=0;
    while(1)
    {
        numofchar=0;
        //UARTSendByte(numofchar);

       // _delay_cycles(8000000);
    }


}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (UCA0RXBUF!= 'a')
    {
        input[]
    }
    UCA0TXBUF = UCA0RXBUF;
    numofchar=numofchar+1;
    UARTSendByte(numofchar);

  //UARTSendByte(numofchar);
 // UARTSendByte('a');
}
