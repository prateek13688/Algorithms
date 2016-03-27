#include "BitManipulation.h"

using namespace std;
typedef long long int uint32_t;
BitManipulation::BitManipulation()
{
    //ctor
}

BitManipulation::~BitManipulation()
{
    //dtor
}

int BitManipulation::Merge_Numbers(int m, int n, int i, int j)
{
    int allOne = ~0;
    int left = allOne << (j + 1);
    int right = ((1 << i) - 1);

    int mask = left | right;
    int nCleared = n & mask;
    int m_Shifted = m << i;
    return (nCleared | m_Shifted);
}
void BitManipulation::printNumber(int m)
{
    vector<int> bitNumbers;
    while(m > 0)
    {
        bitNumbers.push_back(m%2);
        m = m / 2;
    }
    for(int i = bitNumbers.size()-1; i >=0; i--)
        cout<<bitNumbers[i];
    cout<<endl;
}

uint32_t BitManipulation::reverseBits(uint32_t n){
    uint32_t m = 0;
    for(int i = 0; i <32; i++, n /=2)
    {
        m = (m << 1) + (n%2);
    }
    return m;
}

int BitManipulation::getNextNumberWithSame1(int n)
{
    int c = n;
    int c0 = 0, c1 = 0;
    while(c != 0 && ((c & 1) == 0)) // Counting the Number of 0 right to rightmost 0 with trailing 1
    {
        c0 ++;
        c >>= 1;
    }
    while((c & 1) == 1)  // Counting the Number of 1 to the right of rightmost 0 with trailing 1
    {
        c1 ++;
        c >>= 1;
    }
    int p = c0 + c1;   // position of the rightmost 0 with trailing 1
    if(p == 31 || p == 0)
        return -1;
    n |= (1 << p);  //Flip the pth bit from 0 to 1
    n &= ~((1 << p) - 1); // Reset all bits to right of p
    n |= (1 << (c1-1)) - 1;// Add (c1 - 1) to the extreme right
    return n;
}

int BitManipulation::getPrevNumberWithSame1(int n)
{
    int c = n;
    int c0 = 0, c1 = 0;
    while((c & 1) == 1)            // Counting the Number of 0 right to rightmost 1 with trailing 0
    {
        c1 ++;
        c >>= 1;
    }
    while(c != 0 && ((c & 1) == 0)) // Counting the Number of 0 right to rightmost 1 with trailing 0
    {
        c0 ++;
        c >>= 1;
    }
    int p = c0 + c1;
    n &= (1 << (p+1));  // Flip the pth bit from 1 to 0 and set all bits after p to 0.
    int mask = (1 << (c1 + 1))-1; // Add (c1+1) 1's just to the right of p.
    mask = mask << (c0 - 1); // Add (c0 - 1) 0's to the right of newly added 1's
    n |= mask;
    return n;
}
