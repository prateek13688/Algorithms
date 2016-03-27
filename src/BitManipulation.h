#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H

#include<iostream>
#include<vector>

typedef long long int uint32_t;
class BitManipulation
{
    public:
        BitManipulation();
        void printNumber(int);
        int Merge_Numbers(int, int, int, int);
        uint32_t reverseBits(uint32_t );
        int getNextNumberWithSame1(int);
        int getPrevNumberWithSame1(int);
        virtual ~BitManipulation();
    protected:
    private:
};

#endif // BITMANIPULATION_H
