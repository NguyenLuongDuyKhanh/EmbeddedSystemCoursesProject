
#include "myFunction.h"

volatile unsigned char UARTRecvdata;
volatile unsigned int am;
volatile unsigned int adc;
volatile float vol;
volatile unsigned int test;

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

    ADC10CTL0 |= ADC10SC;
           while (ADC10CTL1 & 1);
           ADC10SA = ((unsigned int)&test);

           am = amt1001_gethumidity( gettemp() * (3.3 / 254.0));
           vol = gettemp() * (3.3 / 1024);
           adc = gettemp();

    UARTTx(test);
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

