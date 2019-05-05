
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

    PacketNum=0;
    SecondsIn=1;
    MinutesIn=0;

    Count1s=0;
    Seconds=0;
    Minutes=0;

    UARTTx('a');                //check if UART function work well

    while(1)
    {

    }
}

