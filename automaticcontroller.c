/*
 * File:   automaticcontroller.c
 * Author: abish
 *
 * Created on 31 December, 2025, 12:38 PM
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
int a,b,count=0,count1=0,count2=0;
int long temp=0;
int celsius;
int c,d,e,f,g,h;
int l,m,n;
int fahren,x,y,z;
void delay(unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1 = 1;
    delay(1000);
    RE1 = 0;
    delay(1000);
}
void lcd(char rs, char data)
{
    RE0 = rs;
    PORTD = data;
    enable();
}
void string(char *ptr)
{
    while(*ptr)
        lcd(1, *ptr++);
}
void lm35()
{
  //  TRISA=0X01;
    ANSEL=0X01;
    ADCON0=0X81;
   // ADCON1=0X80;
    GO=1;
    while(GO==1);
    a=ADRESL;
    b=ADRESH;
    temp=a+b;
    celsius=temp*0.488;
    if(celsius>=30)
    {
        RC1=1;
    }
    else
    {
        RC1=0;
    }
   
}
void ldr()
{
    TRISA = 0x02;     
    TRISC = 0x00;     
    ANSEL = 0x02; 
    ANSELH = 0x00;
    ADCON0 = 0x85;     
    ADCON1 = 0x80;    
    delay(50);      
    GO = 1;        
    while(GO);        
    a = ADRESL;
    b = ADRESH;
    temp=(b*256)+a;
    if(temp > 400)     
    {
        RC0 = 0;      
    }
    else
    {
        RC0 = 1;     
    }
}

void main(void) {
    PORTA=PORTB=PORTC=PORTD=PORTE=TRISC=TRISD=TRISE=0X00;
    TRISB=0X4E;
    TRISA=0X03;
    ANSEL=0X03;
    ANSELH=0X00;
    ADCON1=0X80;
    lcd(0,0X38);
    lcd(0,0X0E);
    while(1)
    {
        if(RB6==1)
        {
        lcd(0,0X80);
        string("AUTO MODE");
        lm35();
        ldr();
        }
        if(RB6==0)
        {
            RC0=0;RC1=0;
        }
        if(RB1==1)
        {
            count=1;
            lcd(0,0x01);
            string("MANUAL MODE");
        }
        if(RB2==1 && count==1)
        {
            RC1=1;
            while(RB2==1);
        }
        if(RB3==1 && count==1)
        {
            RC0=1;
            while(RB3==1);
        }
    }
    return;
}
