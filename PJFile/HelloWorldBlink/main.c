
#include "myFunction.h"

volatile unsigned char UARTRecvdata;


void main()
{
    WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer

    interuptconfig();
    IOconfig();
    clockconfig();
    timerconfig();
    UARTconfig();
    ADCconfig();

    UARTTx('a');                //check if UART function work well
    volatile int testingvar;
    volatile float testingvar2;
    while(1)
    {
        //double volt = gettemp() * (3.3 / 254.0);
        testingvar = amt1001_gethumidity( gettemp() * (3.3 / 254.0));
        testingvar2 = gettemp() * (3.3 / 254.0);

    }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A_1 (void)
{
   switch(TA0IV)
   {
   case 2:  break;
   case 4:  break;
   case 10: P1OUT ^= BIT0;
               break;
   }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port(void)
{
    P1OUT ^= BIT0 + BIT6;
    P1IFG &= ~BIT3;
    UARTTx(gettemp());
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    //UCA0TXBUF = UCA0RXBUF;                    //for debug only
    UARTRecvdata = UCA0RXBUF;

    if(UARTRecvdata == 'a')
    {
        P1OUT ^= BIT0 + BIT6 ;
    }
}


