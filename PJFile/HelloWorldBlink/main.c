#include "msp430g2553.h"  //Contains all definitions for registers and built-in functions
#define delayCircleNum 20000

void delay(int n);

int main(void)  //Main program
{
   WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
   P1DIR |= 11000001; // Set P1.0 to output and P1.3 to input direction

   while(1) //Loop forever, we'll do our job in the interrupt routine...
   {
       int LoopB1=2;

      while(LoopB1!=0)
      {
       int B11=delayCircleNum;
       while(B11!=0)
       {
       P1OUT |= 00000001;
       B11--;
       }

       int B12=delayCircleNum;
       while(B12!=0)
       {
       P1OUT &= 00000000;
       B12--;
       }
       LoopB1--;
      }

       int B21=delayCircleNum;
       while(B21!=0)
       {
       P1OUT |= 11000001;
       B21--;
       }

       int B22=delayCircleNum;
       while(B22!=0)
       {
        P1OUT &= 00000000;
        B22--;
       }

   }
}
