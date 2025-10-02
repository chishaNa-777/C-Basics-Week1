#include<stdio.h>
int main()
{
    int number;
    printf("enter a number");
    scanf("%d", & number);
    printf("enter number",number);
    if(number==2)
        printf("is a odd number");
    else
        printf("is a even number");
    return 0;
}
