
#include "myFunction.h"



void main()
{
    WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer

    interuptconfig();
    IOconfig();
    clockconfig();

    while(1)
    {
        //ledRedOff;
        //ledGreenOn;
        //_delay_cycles(1000);
        //ledRedOn;
        //ledGreenOff;
        //_delay_cycles(1000);
    }

}

#pragma vector=PORT1_VECTOR
__interrupt void Port(void)
{

    P1OUT ^= BIT0 + BIT6;
    P1IFG &= ~BIT3;
}
