#include "MemoryManager.hpp"

void MemoryManager::MemBlockresize(long base, long max)
{
    MemoryBlock a_block(base, max-1);
    Ram.push_back(a_block);
    RamSize=max;
}

//Determines the smallest "hole" that can fit the process
long MemoryManager::fineSizeForBestFit(long bytes)
{
    long bestFit=-1; //Set default value
    //long bestFit=std::numeric_limits<long>::max(); //Set to infinite for now
    for(unsigned int i=0; i<Ram.size(); i++)
    {
        if(Ram[i].getPID()==0) //If ram block is unused
        {
            if(bytes-1<=Ram[i].getMaxValue()-Ram[i].getBaseValue()) //If bytes is less than or equal to mem block range
            {
                if(bestFit==-1) //This is the first best fit we find
                {
                    bestFit=Ram[i].getMaxValue()-Ram[i].getBaseValue();
                }
                else if(bestFit>Ram[i].getMaxValue()-Ram[i].getBaseValue()) //If the new best fit is less than previous best fit, make it the new best fit
                {
                    bestFit=Ram[i].getMaxValue()-Ram[i].getBaseValue();
                }
            }
        }
    }
    return bestFit; // will return is the smallest "hole"
}

//Allocates Memory
bool MemoryManager::AllocateMemory(long bytes, int pid)
{
    if(RamSize<bytes) //Makes sure enough space is available
    {
        return false;
    }
    else
    {
        long SmallestBlockSize=fineSizeForBestFit(bytes);
        if(SmallestBlockSize==-1) //If no best fit is found
        {
            return false;
        }
        else
        {
            for(unsigned int i=0; i<Ram.size(); i++)
            {
                if(Ram[i].getPID()==0 && Ram[i].getMaxValue()-Ram[i].getBaseValue()==SmallestBlockSize) //Find best fit block thats unused
                {
                    if(bytes-1<Ram[i].getMaxValue()-Ram[i].getBaseValue()) //Checks to see if there is Excess Ram/leftover Ram will be made
                    {
                        MemoryBlock a_block(Ram[i].getBaseValue()+bytes ,Ram[i].getMaxValue()); //Create a second memory block that is the excess
                        Ram.insert(Ram.begin()+i+1, a_block); //Add it into the Ram
                    }
                    Ram[i].changeMax(Ram[i].getBaseValue()+bytes-1); //Change the best fit block 
                    Ram[i].changePID(pid); //Change the PID so we know it is allocated to Process
                }
            }
            RamSize-=bytes; //Decrease our Ram size
            return true;
        } 
    }  
}

//Merges with the right "hole"
void MemoryManager::mergeWithRightHole(int origin, int right)
{
    Ram[origin].changeMax(Ram[right].getMaxValue());
    Ram.erase(Ram.begin()+right);
}

//Merges with the left "hole"
void MemoryManager::mergeWithLeftHole(int origin, int left)
{
    Ram[origin].changeMin(Ram[left].getBaseValue());
    Ram.erase(Ram.begin()+left);
}

//Whenever process is terminated we need to free up the ram space
void MemoryManager::deleteRam(int pid)
{
    for(unsigned int i=0; i<Ram.size(); i++)
    {
        if(Ram[i].getPID()==pid) //Find the the ram space of deleted process
        {
            Ram[i].changePID(0); //Change the ram to unused
            RamSize+=Ram[i].getMaxValue()-Ram[i].getBaseValue()+1; //Restore Ram size
            if(i==0) //If its the first block
            {
                if(Ram.size()!=1) //If it isnt the only block
                {
                    if(Ram[i+1].getPID()==0) //If right mem block is also unused
                    {
                        mergeWithRightHole(i, i+1);
                    }
                }
            }
            else if(i==Ram.size()-1 && i!=0) //Check if its last memory block in vector
            {
                if(Ram[i-1].getPID()==0) //If the left mem block is unused
                {
                    mergeWithLeftHole(i, i-1);
                }
            }
            else
            {
                if(Ram[i+1].getPID()==0) //If right mem block is also unused
                {
                    mergeWithRightHole(i, i+1);
                }
                if(Ram[i-1].getPID()==0) //If the left mem block is unused
                {
                    mergeWithLeftHole(i, i-1);
                }
            }
            break;
        }
    }
}

//Output the ram state
ostream& operator<<(ostream &out, MemoryManager a_mem)
{
    for(unsigned int i=0; i<a_mem.returnRam().size(); i++)
    {
        out<<a_mem.returnRam()[i].getBaseValue()<<"---"<<a_mem.returnRam()[i].getMaxValue();
        if(a_mem.returnRam()[i].getPID()==0)
        {
            out<<" Unused"<<endl;
        }
        else
        {
            out<<" P"<<a_mem.returnRam()[i].getPID()<<endl;
        }
    }
    return out;
}