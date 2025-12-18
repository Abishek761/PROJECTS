/*
 * File:   gearindiactiontx.c
 * Author: abish
 *
 * Created on 16 December, 2025, 11:28 AM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
void transmit(char a)
{
    TXREG=a;
    while(TXIF==0);
    TXIF=0;
}

void main(void) {
    PORTB=PORTC=TRISC=0X00;
    TRISB=0X3F;
    ANSEL=ANSELH=0X00;
    TXSTA=0X26;
    RCSTA=0X90;
    SPBRG=25;
    while(1)
    {
        if(RB0==1)
        {
            transmit('A');
            while(RB0==1);
            transmit('N');
        }
        if(RB1==1)
        {
            transmit('B');
            while(RB1==1);
            transmit('N');
        }
        if(RB2==1)
        {
            transmit('C');
            while(RB2==1);
            transmit('N');
        }
        if(RB3==1)
        {
            transmit('D');
            while(RB3==1);
            transmit('N');
        }
        if(RB4==1)
        {
            transmit('E');
            while(RB4==1);
            transmit('N');
        }
        if(RB5==1)
        {
            transmit('F');
            while(RB5==1);
            transmit('N');
        }
    }
    return;
}
