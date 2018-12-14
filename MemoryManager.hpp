#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <iostream>
#include <vector>
#include "MemoryBlock.hpp"

using namespace std;

class MemoryManager
{
public:
    MemoryManager(){}

    void MemBlockresize(long base, long max); //Start by creating 1 mem block
    long fineSizeForBestFit(long bytes); //Finds the best fit block
    bool AllocateMemory(long bytes, int pid); //Allocate memory
    void mergeWithRightHole(int origin, int right); //Merge with right "hole" in Ram
    void mergeWithLeftHole(int origin, int left); //Merge with left "hole" in Ram
    void deleteRam(int pid); //When process is deleted, make ram space available again
    
    vector<MemoryBlock> returnRam()
    {
        return Ram;
    }

    friend ostream& operator<<(ostream &out, MemoryManager a_mem);
    
private:
    vector<MemoryBlock> Ram;
    long RamSize;
};

#endif