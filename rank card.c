#include<stdio.h>
struct student
{
    char name[30];
    int registerno;
    int english;
    int tamil;
    int maths;
    int science;
    int social;
};
void main()
{
    struct student s[4];
    int i ,sum,c,j,temp,temp1;
    char temp2[30];
    int avg[5],reg[5];
    char name[5][30];
    for(i=1;i<5;i++)
    {
        printf("enter student%d details:\n",i);
        printf("enter your name:");
        scanf("%s",&s[i].name);
        printf("register no:");
        scanf("%d",&s[i].registerno);
        printf("english mark:");
        scanf("%d",&s[i].english);
        printf("tamil mark:");
        scanf("%d",&s[i].tamil);
        printf("maths mark:");
        scanf("%d",&s[i].maths);
        printf("science mark:");
        scanf("%d",&s[i].science);
        printf("social mark:");
        scanf("%d",&s[i].social);
    }
    printf("\n\n\n");
    for(i=1;i<5;i++)
    {
    printf("student%d profile:\n",i);
    printf("name of the student:%s\n",s[i].name);
    printf("register no:%d\n",s[i].registerno);
    sum=s[i].english+s[i].tamil+s[i].maths+s[i].science+s[i].social;
    c=sum/5;
    printf("average mark of the %s:%d\n",s[i].name,c);
    avg[i]=c;
    reg[i]=s[i].registerno;
    strcpy(name[i],s[i].name);
    }
    for(i=1;i<5;i++)
    {
        for(j=i+1;j<5;j++)
        {
            if(avg[i]<avg[j])
            {
                temp=avg[i];
                avg[i]=avg[j];
                avg[j]=temp;

                temp1=reg[i];
                reg[i]=reg[j];
                reg[j]=temp1;

                strcpy(temp2,name[i]);
                strcpy(name[i],name[j]);
                strcpy(name[j],temp2);

            }
        }
    }
    printf("\n                RANK LIST           \n");
    printf("1st RANK:\n Name:%s\n register no:%d \n average:%d\n",name[1],reg[1],avg[1]);
    printf("2nd RANK:\n Name:%s\n register no:%d \n average:%d\n",name[2],reg[2],avg[2]);
    printf("3rd RANK:\n Name:%s \nregister no:%d \naverage:%d\n",name[3],reg[3],avg[3]);
    printf("4th RANK:\n Name:%s \nregister no:%d  \naverage:%d\n",name[4],reg[4],avg[4]);

}
