#ifndef MEMORYBLOCK_HPP
#define MEMORYBLOCK_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class MemoryBlock
{
public: 
    MemoryBlock(){}
    MemoryBlock(long min, long max)
    {
        baseValue=min;
        maxValue=max;
    }
    MemoryBlock(long min, long max, int pid)
    {
        baseValue=min;
        maxValue=max;
        PID=pid;
    }

    long getBaseValue()
    {
        return baseValue;
    }

    long getMaxValue()
    {
        return maxValue;
    }

    void changeMin(long num)
    {
        baseValue=num;
    }

    void changeMax(long num)
    {
        maxValue=num;
    }

    void changePID(int pid)
    {
        PID=pid;
    }

    int getPID()
    {
        return PID;
    }
    
private:
    long baseValue;
    long maxValue;
    int PID=0;
};

#endif