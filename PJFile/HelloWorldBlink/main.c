#include "msp430g2553.h"  //Contains all definitions for registers and built-in functions
#include <ctype.h>
#include <stdlib.h>
//#include "morse.h"

#define delayperSig  300000
#define delayperChar 600000
#define delayperWord 1000000

//#define delayperSig  1
//#define delayperChar 1
//#define delayperWord 1

#define setLedRed P1OUT|=(1<<0)
#define clrLedRed P1OUT&=~(1<<0)
#define setLedGreen P1OUT|=(1<<6)
#define clrLedGreen P1OUT&=~(1<<6)

//void delay(int n);

char name[]={'N','G','U','Y','E','N',' ','L','U','O','N','G',' ','D','U','Y',' ','K','H','A','N','H'};

//char name[]={'A',' ','B',' ','C'};
unsigned int morse[][6]=
    {   //col 0->6
        { 2, 1, 0, 0, 0, 0}, //A
        { 4, 0, 1, 1, 1, 0}, //B
        { 4, 0, 1, 0, 1, 0}, //C
        { 3, 0, 1, 1, 0, 0}, //D
        { 1, 1, 0, 0, 0, 0}, //E
        { 4, 1, 1, 0, 1, 0}, //F
        { 3, 0, 0, 1, 0, 0}, //G
        { 4, 1, 1, 1, 1, 0}, //H
        { 2, 1, 1, 0, 0, 0}, //I
        { 4, 1, 0, 0, 0, 0}, //J
        { 3, 0, 1, 0, 0, 0}, //K
        { 4, 1, 0, 1, 1, 0}, //L
        { 2, 0, 0, 0, 0, 0}, //M
        { 2, 0, 1, 0, 0, 0}, //N
        { 3, 0, 0, 0, 0, 0}, //O
        { 4, 1, 0, 0, 1, 0}, //P
        { 4, 0, 0, 1, 0, 0}, //Q
        { 3, 1, 0, 1, 0, 0}, //R
        { 3, 1, 1, 1, 0, 0}, //S
        { 1, 0, 0, 0, 0, 0}, //T
        { 3, 1, 1, 0, 0, 0}, //U
        { 4, 1, 1, 1, 0, 0}, //V
        { 3, 1, 0, 0, 0, 0}, //W
        { 4, 0, 1, 1, 0, 0}, //X
        { 4, 0, 1, 0, 0, 0}, //Y
        { 4, 0, 0, 1, 1, 0}, //Z
    };

int main(void)  //Main program
{

   WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
   P1DIR |= 0b01000001; // Set P1.0, P1.6 to output and P1.3 to input direction
   //Test Led
   setLedRed;
   setLedGreen;
   clrLedRed;
   clrLedGreen;
   ///////////

 //  while(1) //Loop forever, we'll do our job in the interrupt routine...
   {

       int charNumofName;
       for (charNumofName = 0 ; charNumofName < sizeof(name) ; charNumofName++)
       {
           if(name[charNumofName]==' ')
                         {
                             int delay=delayperWord;
                             while(delay!=0)
                             {
                                 setLedGreen;
                                 delay--;
                             }
                             clrLedGreen;
                         }
           else
           {
           int sigNum;
           for (sigNum=0 ; sigNum < morse[name[charNumofName]-65][0]; sigNum++ )
           {

               if (morse[name[charNumofName]-65][sigNum+1] == 1)
               {
                   int delay=delayperSig;
                   while(delay!=0)
                   {
                   setLedRed;
                   delay--;
                   }
               }
               if (morse[name[charNumofName]-65][sigNum+1] == 0)
               {

                   int delay=delayperSig;
                   while(delay!=0)
                   {
                       clrLedRed;
                       delay--;
                   }
               }
           }
               int delay=delayperChar;
               while(delay!=0)
               {
                   clrLedRed;
                   clrLedGreen;
                   delay--;
               }

           }
       }
   }
}
