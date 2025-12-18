#include<stdio.h>
int d,f,g,h;
int appoint,option,option1,option2,option3,option4;
int a,b,i;
int age,pay;
char str[10],str1[15],str2[15],str3[10];
void details()
{
    printf("Enter your name:");
    scanf("%s",str);
    printf("Enter your age:");
    scanf("%d",&age);
    date();
}
void date()
{
    printf("Enter your appointment date:");
    scanf("%s",str3);
    int count=0;
    for(i=0;str3[i]!='\0';i++)
    {
        count++;
    }
    if(count==8)
    {

    }
    else{
        date();
    }
}
void selection(int k)
{
    switch(k)
            {
            case 1:
                appointtime();
                break;
            case 2:
                appointtime();
                break;
            case 3:
                appointtime();
                break;
            }

}
void appointtime()
{
    printf("\n Use 24 hours timing to book the appointment");
    printf("\nselect your appointment timing:");
    scanf("%d %d",&a,&b);
    time(a,b);

}
void time(int a, int b)
{
    if(a>=8 && a<=20 && b>=00 && b<=59)
        {
            printf("\nAvailable timing\n");
            details();
            paymentselect();
        }
    else
        {
            printf("\nThis time is not available. Please choice another timing");
            appointtime();
        }
}
void paymentselect()
{
    printf("\nAre you ready for the payment?");
    printf("\n1.yes \n2.No\n");
    scanf("%d",&pay);
    if(pay==1)
    {
        printf("\nPlease confirm the payment");
        payment();
    }
    else{
        printf("\nIts okay , your appointment is cancelled");
        main();
    }

}
void payment()
{
    printf("\n1.UPI mode");
    printf("\n2.Netbanking");
    printf("\nEnter your option:");
    scanf("%d",&d);
    upi(d);

}
void upi(int d)
{
    switch(d)
    {
    case 1:
        printf("\nEnter your UPI id:");
        scanf("%s",str1);
        int e=0;
        for(i=0;str1[i]!='\0';i++)
        {
            e++;
        }
        if(e==10)
        {
        printf("\nEnter the amount for appointment:");
        scanf("%d",&f);
        if(f<100)
        {
            printf("\nMinimum amount for appointment is 100RS");
            upi(1);
        }
        else
        {
            printf("\nyour appointment is confirmed");
            main();
        }
        }
        else{
            printf("\n invalid upi id, please try again\n");
            upi(1);
        }
        break;
    case 2:
        printf("\nEnter your Account number:");
        scanf("%s",str2);
        int g=0;
        for(i=0;str2[i]!='\0';i++)
        {
            g++;
        }
        if(g==8)
        {
        printf("\nEnter the amount for appointment:");
        scanf("%d",&h);
        if(h<100)
        {
            printf("\nMinimum amount for appointment is 100RS");
            upi(2);
        }
        else
        {
            printf("\nyour appointment is confirmed");
            main();
        }
        }
        else
        {
            printf("\n invalid account number, please try again\n");
            upi(2);
        }
        break;
    }
}
void main()
{
    printf("\n              welcome           ");
    printf("\n1.APPOINTMENT");
    printf("\n2.CUSTOMER CARE\n");
    printf("\nEnter your option:");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
        printf("1.ORTHO\n");
        printf("2.ENT\n");
        printf("3.DENENIST\n");
        printf("4.CARDIOLOGIST\n");
        printf("\nEnter your option:");
        scanf("%d",&appoint);
        switch(appoint)
        {
        case 1:
            printf("1.Dr.krishna moorthi\n");
            printf("2.Dr.Bala krishnan\n");
            printf("3.Dr.Baskaran\n");
            printf("Enter your option:");
            scanf("%d",&option1);
            selection(option1);
            break;
        case 2:
            printf("1.Dr.Rajendran\n");
            printf("2.Dr.Deva\n");
            printf("3.Dr.VENKAT\n");
            printf("Enter your option:");
            scanf("%d",&option2);
            selection(option2);
            break;
        case 3:
            printf("1.Dr.Raja\n");
            printf("2.Dr.Ravi\n");
            printf("3.Dr.kamal\n");
            printf("Enter your option:");
            scanf("%d",&option3);
            selection(option3);
            break;
        case 4:
            printf("1.Dr.Vijay\n");
            printf("2.Dr.Ajith\n");
            printf("3.Dr.Simbu\n");
            printf("Enter your option:");
            scanf("%d",&option4);
            selection(option4);
            break;
        default :
            printf("\ninvalid option");
            main();
        }
  }
}
