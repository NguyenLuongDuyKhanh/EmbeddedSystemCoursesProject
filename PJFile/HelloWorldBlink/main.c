#include <msp430.h> 


/**
 * main.c
 */

int i = 0;
char lenh[];
int CheckLedOn(char string[])
{
    int i;
    char ledon[] = "LED_ON";
    for(i=0;i<=6;i++)
    {
        if(string[i] != ledon[i])
        {
            return 0;
        }
    }
    return 1;
}
int CheckLedOff(char string[])
{
    int i;
    char ledoff[] = "LED_OFF";
    for (i = 0;i <= 7;i++)
    {
        if(string[i] != ledoff[i])
        {
            return 0;
        }
    }
    return 1;
}
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

void UART_Write_Char(unsigned char data)
{
    while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
    UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}

char UART_Read_Char()
{
    while (!(IFG2&UCA0RXIFG)); // Doi gui xong ky tu truoc
    return UCA0RXBUF; // Moi cho phep nhan ky tu tiep theo
}

void UART_Write_String(char *string)
{
    while(*string) // Het chuoi ky tu thi thoat
        {
        while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
        UCA0TXBUF= *string; // Moi cho phep gui ky tu tiep theo
        string ++; // Lay ky tu tiep theo
        }
    UART_Write_Char(0);
}

void UART_Read_String(char *s)
{
    *s = UART_Read_Char();
    while(*s!='\0')
    {
        s++;
        *s = UART_Read_Char();
    }
}
void main(void)
{
    char *data = "Hello UART !!";
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	CauhinhClock();
	CauhinhLed();
	CauhinhUART();
	UART_Write_Char(10);
	UART_Write_String(data);
	UART_Write_Char(10);
	while(1)
	{

	}
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    //UCA0TXBUF = UCA0RXBUF; //Xuat ra man hinh ki tu vua nhan
    lenh[i] = UCA0RXBUF;
    //UARTSendByte(i);
    //P1OUT ^= BIT0 + BIT6;
    //_delay_cycles(8000000);
    i++;
    if(i == 6)
    {
        char *ok = "OK";
        char *error = "ERROR";
        int a = CheckLedOn(lenh);
        if(a == 1)
        {
            P1OUT |= BIT0 + BIT6;
            UART_Write_String(ok);
        }
        else
        {
            UART_Write_String(error);
        }
    }

}
