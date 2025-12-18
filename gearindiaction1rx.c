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
int i=0,count=0;
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
void pwm(int i)
{
    CCPR1L=i>>2;
    CCP1CON|=(i&0X30)<<4;
}
char receiver()
{
    while(RCIF==0);
    char a=RCREG;
    RCIF=0;
    if(a=='A')
    {
        lcd(0,0X80);
        lcd(0,0X01);
        string("first gear");
        pwm(150);
        RC0=0;
    }
    if(a=='B')
    {
        lcd(0,0X01);
        lcd(0,0X80);
        string("second gear");
        pwm(250);
        RC0=0;
    }
    if(a=='C')
    {
        lcd(0,0X01);
        lcd(0,0X80);
        string("third gear");
        pwm(500);
        RC0=0;
    }
    if(a=='D')
    {
        lcd(0,0X01);
        lcd(0,0X80);
        string("fourth gear");
        pwm(750);
        RC0=0;
    }
    if(a=='E')
    {
        lcd(0,0X01);
        lcd(0,0X80);
        string("fifth gear");
        pwm(1023);
        RC0=0;
    }
    if(a=='F')
    {
        lcd(0,0X01);
        lcd(0,0X80);
        string("reverse gear");
        RC0=1;
    }
    if(a=='N')
    {
        lcd(0,0X01);
        lcd(0,0xC0);
        CCPR1=0X00;
        string("netural");
        RC0=0;RC2=0;
    }  
}
void main(void) {
    PORTC=PORTD=PORTE=TRISD=TRISE=0X00;
    TRISC=0X80;
    ANSEL=ANSELH=0X00;
    TXSTA=0X26;
    RCSTA=0X90;
    SPBRG=25;
    PR2=124;
    T2CON=0X05;
    CCPR1=0X00;
    CCP1CON=0X0C;
    lcd(0,0X38);
    lcd(0,0X0E);
    while(1)
    {
        receiver();
    }
    
    return;
}
