/*
 * File:   trafficlight.c
 * Author: abish
 *
 * Created on 8 October, 2025, 8:46 PM
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
int count=0;
void delay(unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
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
void timer(float limit)
{
    count=0;
    while(count<2*limit)
    {
        if(TMR1IF==1)
        {
            count++;
            TMR1=3035;
            TMR1IF=0;
        }
       
    }
}

void main(void) {
    PORTA=PORTC=PORTD=PORTE=TRISA=TRISC=TRISD=TRISE=0X00;
    ANSEL=ANSELH=0X00;
    lcd(0,0X38);
    lcd(0,0X0E);
    T1CON=0X31;
    TMR1=3035;
    int arr[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    int i,a,b,count1=0;
    while(1)
    {
            RA2=1;
            string("STOP");
            for(i=10;i>=0;i--)
            {
               a=i/10;b=i%10;
               RA0=0;RA1=1;
               PORTC=arr[a];
               timer(0.5);
               RA0=1;RA1=0;
               PORTC=arr[b];
               timer(0.5);
            }
            RA2=0;
            lcd(0,0X01);
            RA4=1;
            string("GO");
            for(i=10;i>=0;i--)
            {
               a=i/10;b=i%10;
               RA0=0;RA1=1;
               PORTC=arr[a];
               timer(0.5);
               RA0=1;RA1=0;
               PORTC=arr[b];
               timer(0.5);
            }
            RA4=0;
            lcd(0,0X01);
            RA3=1;
            string("ALERT");
            for(i=5;i>=0;i--)
            {
               a=i/10;b=i%10;
               RA0=0;RA1=1;
               PORTC=arr[a];
               timer(0.5);
               RA0=1;RA1=0;
               PORTC=arr[b];
               timer(0.5);
            }
            RA3=0;
            lcd(0,0X01); 
    }
    return;
}
