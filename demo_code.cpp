#include<bits/stdc++.h>
using namespace std;

int main()
{
    // int mask = 1011011; is wrong as compiler assumes it as decimal
    int mask = 0b1001011;
    // to find ith digit
    // 1st digit , mask&1
    for(int i=1;i<=7;i++)
    {
        // right shift by i-1 places and and with 1 to get LSB
        cout << i << " th digit is " << ((mask>>(i-1)) & 1) << endl;
    }
    return 0;
}