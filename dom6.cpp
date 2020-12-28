#include <iostream>
using namespace std;

int main()
{
    unsigned short a;
    int d1,d2,d3,d4,d5;
    cin>>a;

    if (a>=10000)
    {
        d5=a%10;
        d4=(a/10)%10;
        d3=(a/100)%10;
        d2=(a/1000)%10;
        d1=(a/10000)%10;

        cout<<0<<d2<<d3<<d4<<d5;
    }
    else

    if (a>=1000)
    {
        d5=a%10;
        d4=(a/10)%10;
        d3=(a/100)%10;
        d2=(a/1000)%10;

        cout<<0<<d3<<d4<<d5;
    }
    else

    if (a>=100)
    {
        d5=a%10;
        d4=(a/10)%10;
        d3=(a/100)%10;

        cout<<0<<d4<<d5;
    }
    else

    if (a>=10)
    {
        d5=a%10;
        d4=(a/10)%10;

        cout<<0<<d5;
    }
    else
    {
        cout<<0;
    }

    return 0;
}

