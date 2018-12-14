#ifndef PROCESS_CPP
#define PROCESS_CPP

#include "Process.hpp"

Process::Process(int id, int priority, long memory_size)
{
    pid=id;
    memorySize=memory_size;
    priority_number=priority;
}

bool Process::isEmpty()
{
    if(memorySize==0 && pid==0 && priority_number==0) //If process ram size, pid and priority is all 0 it is considered empty.
    {
        return true;
    }
    else{
        return false;
    }
}

void Process::clear()
{
    memorySize=0; //Set mem back to 0
    pid=0; //Set pid back to 0
    priority_number=0; //Set priority back to 0
    filename="";
}
#endif