/*
 * File:   liftproject1.c
 * Author: abish
 *
 * Created on 16 October, 2025, 12:42 PM
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
void delay(unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1=1;delay(1000);
    RE1=0;delay(1000);
}
void lcd(char rs,char data)
{
    RE0=rs;
    PORTD=data;
    enable();
}
void string(char *ptr)
{
    while(*ptr)
    {
        lcd(1,*ptr++);
    }
}
void main(void) {
    PORTA=PORTB=PORTC=PORTD=PORTE=TRISC=TRISD=TRISE=0X00;
    TRISA=0X0F;
    TRISB=0X0F;
    ANSEL=ANSELH=0X00;
    int S,F;
    lcd(0,0X38);
    lcd(0,0X0E);
    while(1)
    {
       
         if(RA0==1)
         {
            F=0;
            lcd(0,0XC0);
            string("ground floor");
            while(RA0==1);
         }
        if(RA1==1)
        {
            F=1;
            lcd(0,0XC0);
            string("first floor");
            while(RA1==1);
        }
        if(RA2==1)
        {
            F=2;
            lcd(0,0XC0);
            string("second floor");
            while(RA2==1);
        }
        if(RA3==1)
        {
            F=3;
            lcd(0,0XC0);
            string("third floor");
            while(RA3==1);
        }
        if(RB0==0)
         {
            S=0;
            lcd(0,0X80);
            string("ground floor");
            //while(RA4==1);
         }
        if(RB1==0)
         {
            S=1;
            lcd(0,0X80);
            string("first floor");
            //while(RA5==1);
         }
        if(RB2==0)
         {
            S=2;
            lcd(0,0X80);
            string("second floor");
           //while(RA6==1);
         }
        if(RB3==0)
         {
            S=3;
            lcd(0,0X80);
            string("third floor");
           // while(RA7==1);
         }
        if(F==S)
        {
            RC0=RC1=0;
        }
        if(F>S)
        {
            RC0=1;RC1=0;
        }
        if(F<S)
        {
            RC0=0;RC1=1;
        }
    }
    return;
}
