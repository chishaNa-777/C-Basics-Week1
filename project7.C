#include<stdio.h>
int main()
{
    int A=40,B=45,C=50;
    if(A>B&&A>C)
    {
        printf("%d is the largest number",A);
    }
    if(B>A&&B>C)
    {
        printf("%d is the largest number",B);
    }
    if(C>A&&C>B)
    {
        printf("%d is the largest number",C);
    }
    return 0;
}
