
#include "myFunction.h"



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

    while(1)
    {

    }
}

