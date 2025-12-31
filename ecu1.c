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
char secs=0,mins=0,hours=0;
char sec =0,min=0,hour=0,s=0,m=0,h=0;
int count=0;
char a=1,b=2,c=3;
char  count1=0;     
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

void start()
{
    SEN = 1;
    while(SSPIF == 0);
    SSPIF = 0;
}
void repeatstart()
{
    RSEN=1;
    while(SSPIF==0);
    SSPIF=0;
}
void address(char add)
{
    SSPBUF = add;
    while(BF == 1);
    while(ACKSTAT == 1);
    SSPIF = 0;
}

void write(char data)
{
    SSPBUF = data;
    while(SSPIF == 0);
    SSPIF = 0;
}
char read(unsigned char ack)
{
    char d;
    RCEN=1;
    ACKDT=ack;
    while(BF==0);
    d=SSPBUF;
    ACKEN=1;
    while(SSPIF==0);
    SSPIF=0;
    return d; 
}

void stop()
{
    PEN = 1;
    while(SSPIF == 0);
    SSPIF = 0;
}

void timer1(int limit)
{
    count = 0;
    while(count < 2 * limit)
    {
        if(TMR1IF)
        {
            count++;
            TMR1 = 3035;
            TMR1IF = 0;
        }
    }
}
void main(void)
{
    PORTA = PORTD = PORTE = TRISD = TRISE = 0x00;
    TRISA = 0x03;     
    PORTC = 0x00;
    TRISC = 0x18;
    ANSEL = ANSELH = 0x00;
    T1CON = 0x31;
    TMR1 = 3035;
    SSPCON = 0x28;
    SSPSTAT = 0x80;
    SSPCON2 = 0x00;
    start();
    address(0XD0);
    address(0X00);
    write(0X10);
    write(0X20);
    write(0X12);
    stop();
    delay(100);
    lcd(0, 0x38);
    lcd(0, 0x0E);
    lcd(0, 0x01);
    while(1)
    {
        start();
        address(0XD0);
        address(0X00);
        repeatstart();
        address(0XD1);
        s=read(0);
        m=read(0);
        h=read(1);
        stop();
        delay(100);
        lcd(0,0x88);
        lcd(1,((h&0XF0)>>4)+48);
        lcd(1,(h&0X0F)+48);
        lcd(1,':');
        lcd(1,((m&0XF0)>>4)+48);
        lcd(1,(m&0X0F)+48);
        lcd(1,':');
        lcd(1,((s&0XF0)>>4)+48);
        lcd(1,(s&0X0F)+48);
        if(RA0 == 1)
        {
            if(count1 == 0)     
            {
                sec = min = hour = 0;
                RC0=1;
                hour = eeprom_read(a);
                min  = eeprom_read(b);
                sec  = eeprom_read(c);
                count1 = 1;         
            }
            else if(count1 == 1)    
            {
                eeprom_write(a, hour);
                eeprom_write(b, min);
                eeprom_write(c, sec);
                count1 = 2;        
            }
            else if(count1 == 2)   
            {
                hour = eeprom_read(a);
                min  = eeprom_read(b);
                sec  = eeprom_read(c);
                count1 = 1;         
            }        
        }
        if(RA1==1)
        {
            eeprom_write(a, hours);
            eeprom_write(b, mins);
            eeprom_write(c, secs);
        }
        lcd(0, 0x80);
        if(count1 == 1)
        {
            string("RUNNING");
        }
        else if(count1 == 2)
        {
            string("PAUSED ");
        }
        else
        {
            string("STOPPED");
        }
        lcd(0, 0xC0);
        lcd(1, (hour/10) + '0');
        lcd(1, (hour%10) + '0');
        lcd(1, ':');
        lcd(1, (min/10) + '0');
        lcd(1, (min%10) + '0');
        lcd(1, ':');
        lcd(1, (sec/10) + '0');
        lcd(1, (sec%10) + '0');
        if(count1 == 1)
        {
            timer1(1);
            sec++;
            if(sec > 59)
            {
                sec = 0;
                min++;
                if(min > 59)
                {
                    min = 0;
                    hour++;
                    if(hour > 23)
                        hour = 0;
                }
            }
        }
    }
}
