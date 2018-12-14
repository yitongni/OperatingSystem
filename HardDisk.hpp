#ifndef HardDisk_HPP
#define HardDisk_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "Process.hpp"

using namespace std; 

class HardDisk
{
public:
    HardDisk(){}//Default
    HardDisk(int IDnumber)
    {
        ID=IDnumber;
    }
    ~HardDisk(){}; //Destructor

    void assignprocesstoHardDisk(); //Assign Process to Hard Disk
    void addprocesstoqueue(Process a_process); //Add Process to I/O queue

    int GetID()
    {
        return ID;
    }

    queue<Process> GetQueue()
    {
        return IOqueue;
    }

    Process GetProcessUsingHD()
    {
        return processUsingHardDisk;
    }
    
    void clearHardDisk()
    {
        processUsingHardDisk.clear();
        assignprocesstoHardDisk();
    }

    //Output
    friend ostream& operator<<(ostream &out, HardDisk &a_HardDisk);

private:
    int ID;
    queue<Process> IOqueue;
    Process processUsingHardDisk;
};

#endif