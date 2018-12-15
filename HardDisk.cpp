#ifndef HardDisk_CPP
#define HardDisk_CPP

#include "HardDisk.hpp"

void HardDisk::assignprocesstoHardDisk()
{
    if(processUsingHardDisk.isEmpty()==true && !IOqueue.empty()) //If hard Disk isnt being used
    {
       processUsingHardDisk=IOqueue.front(); //Make the first thing in queue use Hard Disk
       IOqueue.pop(); //Remove it from queue
    }
}

void HardDisk::addprocesstoqueue(Process a_process)
{
    IOqueue.push(a_process); //Add to I/O queue.
    assignprocesstoHardDisk(); //Assign process to hard disk
}

ostream& operator<<(ostream &out, HardDisk &a_HardDisk)
{
    out<<"HardDisk #"<<a_HardDisk.GetID()<<endl;
    out<<"Process Using Hard Disk: "<<endl;
    if(a_HardDisk.GetProcessUsingHD().isEmpty()==false) //Checks to see if process is using hard disk
    {
        out<<a_HardDisk.GetProcessUsingHD()<<" File: "<<a_HardDisk.GetProcessUsingHD().GetFilename()<<endl; //Out put process using HD
    }
    out<<"Process in I/O Queue: "<<endl;
    queue<Process> tempqueue=a_HardDisk.GetQueue();
    while(!tempqueue.empty()) //While temp queue isnt empty
    {
        out<<tempqueue.front()<<" File: "<<tempqueue.front().GetFilename()<<endl; //Cout the top
        tempqueue.pop(); //Pop
    }
    out<<"------------------------------------------------------------";
    return out;
}

#endif