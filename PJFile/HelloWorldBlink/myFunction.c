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

void clockconfig() //chosing clock DCO 1Mhz
{
    DCOCTL = 0; // Select lowest DCOx and MODx settings
       BCSCTL1 = CALBC1_1MHZ; // Set DCO
       DCOCTL = CALDCO_1MHZ;
}

void timerconfig()
{
    TA0CTL |= TASSEL_2 + MC_1 + TAIE;
    TA0CCR0 = 50000;                              //only in MC_1 or MC_3
}

void UARTconfig()
{
    P1SEL = BIT1 + BIT2;        //P1.1 = Rx, P1.2 = Tx
    P1SEL2 = BIT1 + BIT2;       //

    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = 0x08; // 1MHz 115200
    UCA0BR1 = 0x00; // 1MHz 115200
    UCA0MCTL = UCBRS2 + UCBRS0; // Modulation UCBRSx = 5
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
    UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt
}

void UARTTx(unsigned char byte)
{
    while(!(IFG2 & UCA0TXIFG));                             //waiting for ready buffer
    UCA0TXBUF = byte;                                       //tranfer
}

void ADCconfig()
{
    ADC10CTL1 = INCH_5 + CONSEQ_1;            //
    ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE + REF2_5V +REFON;
          ADC10DTC1 = 0x02;                         // 2 conversions
          ADC10AE0 |= BIT5 + BIT4;                         // Disable digital I/O on P1.0 to P1.2
}


unsigned char amt1001_gethumidity(double voltage) {
    if(voltage > AMT1001_HUMIDITYVMIN && voltage < AMT1001_HUMIDITYVMAX)
        return (unsigned char)(AMT1001_HUMIDITYSLOPE*voltage);
    else
        return -1;
}


/*
 * get temperature based on read voltage
 */


const float amt1001_lookuptable[amt1001_lookuptablesize] = {
        -86.99 , -59.05 , -49.91 , -43.96 , -39.45 , -35.76 , -32.61 , -29.84 , -27.37 , -25.11 , -23.03 , -21.1 , -19.29 , -17.58 , -15.95 , -14.41 , -12.92 , -11.5 , -10.12 , -8.79 , -7.5 , -6.25 , -5.03 , -3.83 , -2.66 , -1.52 , -0.4 , 0.71 , 1.8 , 2.87 , 3.93 , 4.97 , 6.01 , 7.03 , 8.05 , 9.05 , 10.06 , 11.05 , 12.04 , 13.03 , 14.02 , 15 , 15.98 , 16.96 , 17.95 , 18.93 , 19.92 , 20.9 , 21.9 , 22.89 , 23.89 , 24.9 , 25.91 , 26.93 , 27.96 , 29 , 30.05 , 31.11 , 32.19 , 33.27 , 34.37 , 35.49 , 36.63 , 37.78 , 38.95 , 40.14 , 41.36 , 42.6 , 43.87 , 45.17 , 46.5 , 47.86 , 49.26 , 50.7 , 52.18 , 53.71 , 55.29 , 56.92 , 58.62 , 60.38 , 62.22 , 64.14 , 66.15 , 68.26 , 70.49 , 72.84 , 75.34 , 78.01 , 80.87 , 83.95 , 87.3 , 90.96 , 95 , 99.52 , 104.62 , 110.48 , 117.36 , 125.67 , 136.09 , 149.94 , 170.2 , 206.11 , 330.42
};

unsigned char amt1001_gettemperature(int adcvalue) {


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

/*
 * DEFINE INTERUPT VECTOR
 */

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A_1 (void)
{
   switch(TA0IV)
   {
   case 2:  break;
   case 4:  break;
   case 10:
       {
           Count1s++;

           if(Count1s==20)
           {
           P1OUT ^= BIT0;
           Count1s=0;
           Seconds++;

           if(Seconds==60)
           {
               Seconds=0;
               Minutes++;
           }

           if( (Seconds == SecondsIn) && (Minutes == MinutesIn))
           {
               PacketNum++;

                   ADC10CTL0 &= ~ENC;
                  while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
                  ADC10SA = (unsigned int)&test;            // Copies data in ADC10SA to unsigned int adc array
                  ADC10CTL0 |= ENC + ADC10SC;             //

               UARTTx(PacketNum);
               UARTTx(amt1001_gethumidity((double)(test[0]*(5/1023.0))));
               UARTTx(amt1001_gettemperature(test[1]));

               Seconds=0;
               Minutes=0;
               //__bis_SR_register(CPUOFF + GIE);
               }
               }
           break;
       }
   }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port(void)
{
    /*
    P1OUT ^= BIT0 + BIT6;
    P1IFG &= ~BIT3;

    ADC10CTL0 |= ADC10SC;
           while (ADC10CTL1 & 1);
           ADC10SA = ((unsigned int)&test);

           am = amt1001_gethumidity( gettemp() * (3.3 / 254.0));
           vol = gettemp() * (3.3 / 1024);
           adc = gettemp();

    UARTTx(test);
    */
}

//const char string[] = { "Hello World\r\n" };

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
    /*
   P1OUT |= TXLED;
     UCA0TXBUF = string[i++]; // TX next character
    if (i == sizeof string - 1) // TX over?
       UC0IE &= ~UCA0TXIE; // Disable USCI_A0 TX interrupt
    P1OUT &= ~TXLED;
    */
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    /*
   P1OUT |= RXLED;
    if (UCA0RXBUF == 'a') // 'a' received?
    {
       i = 0;
       UC0IE |= UCA0TXIE; // Enable USCI_A0 TX interrupt
      UCA0TXBUF = string[i++];
    }
    P1OUT &= ~RXLED;
    */
    //SecondsIn=UCA0RXBUF;
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  //__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
