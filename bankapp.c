#include<stdio.h>
struct member
{
    char name[30];
    char dob[10];
    char gender[30];
    char mail[30];
    char phone[20];
    char username[30];
    char password[30];
    char acc_no[20];
    int balance;
};
void dob()
{
    struct member s;
    printf("enter DOB: Date/month/year:");
    scanf("%s",s.dob);
    int i,count=0;
    for(i=0;s.dob[i]!='\0';i++)
    {
        count++;
    }
    if(count==8)
    {
    }
    else{
        printf("invalid pattern.try again\n");
        dob();
    }
}
void mail()
{
     struct member s;
     int count=0,count1=0,len=0,i;
     char email[30]={"xxxxxxxxxx@gmail.com"};
            printf("enter mail id:");
            scanf("%s",s.mail);
            for(i=10;email[i]!='\0';i++)
            {
                count++;
            }
            for(i=10;s.mail[i]!='\0';i++)
            {
                count1++;
            }
            if(count==count1)
            {
                for(i=9;email[i]!='\0';i++)
                {
                    if(email[i]==s.mail[i])
                    {
                        len++;
                    }
                }
            }
            if(len==10)
            {

            }
            else{
                printf("invalid pattern.try again\n");
                mail();
            }
}
void phone()
{
    struct member s;
    int i,count=0;
    printf("enter mobile number:");
    scanf("%s",s.phone);
    for(i=0;s.phone[i]!='\0';i++)
    {
        count++;
    }
    if(count==10)
    {
    }
    else{
        printf("invalid pattern.try again\n");
        phone();
    }
}
void account()
{
    struct member s;
    int i,count=0;
    printf("enter account number:");
    scanf("%s",s.acc_no);
    for(i=0;s.acc_no[i]!='\0';i++)
    {
        count++;
    }
    if(count==8)
    {
    }
    else{
        printf("invalid account number.try again\n");
        account();
    }
}
void main()
{
    struct member s;
    char user[30];
    char pass[30];
    int amount;
    int bankoption,login_option;
    char email[30]={"         @gmail.com"};
    int r,l,e;
    while(1)
    {
        printf("\n          BANK APPLICATION    \n");
        printf("1.Register\n2.Login\n3.exit\n");
        printf("enter your option:");
        scanf("%d",&bankoption);
        switch(bankoption)
        {
        case 1:
            printf("\nRegister as member\n");
            printf("enter Name:");
            scanf("%s",s.name);
            dob();
            mail();
            printf("enter gender:");
            scanf("%s",s.gender);
            account();
            phone();
            printf("create username:");
            scanf("%s",s.username);
            printf("create password:");
            scanf("%s",&s.password);
            printf("\nRegistration successful");
            s.balance=0;
            r=1;
            break;
        case 2:
            if(r==0)
            {
                printf("NO registered member found.please register first");
                break;
            }
            printf("\n         login page      \n");
            printf("\nenter username:");
            scanf("%s",user);
            printf("\nenter password:");
            scanf("%s",pass);
            if(strcmp(user,s.username)==0 && strcmp(pass,s.password)==0)
            {
                printf("\nlogin successful");
                l=1;
                while(l)
                {
                    printf("\n        Banking Menu     ");
                    printf("\n1.view information\n2.deposit\n3.withdraw\n4.logout\n");
                    printf("enter your option:");
                    scanf("%d",&login_option);
                    switch(login_option)
                    {
                    case 1:
                        printf("      Member information    \n");
                        printf("Name:%s\n",s.name);
                        printf("Account number:%s\n",s.acc_no);
                        printf("Balance:%d\n",s.balance);
                        break;
                    case 2:
                        printf("Enter amount to deposit:");
                        scanf("%d",&amount);
                        s.balance+=amount;
                        printf("Deposit successful! New balance:%d",s.balance);
                        break;
                    case 3:
                        printf("Enter amount to withdraw:");
                        scanf("%d",&amount);
                        if(amount>s.balance)
                        {
                            printf("insufficient balance");
                        }
                        else{
                            s.balance-=amount;
                            printf("withdrawal successful! New balance:%d",s.balance);
                            break;
                        }
                    case 4:
                        printf("\nLogged out successfully");
                        l=0;
                        break;
                    default:
                        printf("invalid option\n");
                        break;

                        }
                    }
            }
            else{
                printf("invalid username or password.try again\n");
                }
                break;
        case 3:
            printf("thank you for using the bank application\n");
            break;
        default:
            printf("invalid option.try again\n");

            }

        }
    }




