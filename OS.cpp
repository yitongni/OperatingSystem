#ifndef OS_CPP
#define OS_CPP

#include <iostream>
#include "OS.hpp"

//Creates the number of HardDisk
void OS::createHardDisk(int numOfHD)
{
    for(int i=0; i<numOfHD; i++)
    {
        HardDisk a_HardDisk(i); //Create Hard Disk
        harddiskqueue.push_back(a_HardDisk);
    }
}

//Creates the memory
void OS::createRam(long Ram)
{
    Manager.MemBlockresize(0, Ram);
}

//This function is called whenever a process is added to the ready queue.
void OS::checkforpreempt()
{
    if(ProcessinCPU.isEmpty()==false)
    {
        if(priorityqueue.top().GetPriority() > ProcessinCPU.GetPriority()) //If new process has a higher priority than process in CPU
        {
            priorityqueue.push(ProcessinCPU); //Put process currently using CPU back into ready queue
            ProcessinCPU=priorityqueue.top(); //Assign the first process to cpu
            priorityqueue.pop(); //Remove the assigned process from ready queue.
        }
    }
    else //This means CPU is empty
    {
        assignProcesstoaCPU(); 
    }
}

// This function is called whenever the CPU is empty
void OS::assignProcesstoaCPU()
{
    if(ProcessinCPU.isEmpty()==true && !priorityqueue.empty()) //If CPU not being used and there is at least 1 process in ready queue
    {
        ProcessinCPU=priorityqueue.top(); //Assign the first process to CPU
        priorityqueue.pop(); //Remove process from ready queue
    }
}

//This function is called when creating a new process
void OS::createProcess(int priority_num, long memorySize)
{
    if(Manager.AllocateMemory(memorySize, pid)==false)
    {
        cout<<"Not Enough RAM"<<endl;
        return;
    }
    else
    {
        Process a_process(pid, priority_num, memorySize);//Creates Process
        pid++; //increment PID
        allProcesses.push_back(a_process); // Push process into a list of all process
        priorityqueue.push(a_process); //Add process to ready queue
        checkforpreempt(); //Process is entering ready queue so we might have to preempt
    }
}

void OS::moveProcessToIOqueue(int hardDiskNumber, string filename)
{
    if(ProcessinCPU.isEmpty()==false) //Makes sure their is a process using the CPU
    {
        ProcessinCPU.assignFile(filename); //Give the file to process
        harddiskqueue[hardDiskNumber].addprocesstoqueue(ProcessinCPU); //Process in CPU is added to Hard Disk # queue
        ProcessinCPU.clear(); //Process leaves CPU
        assignProcesstoaCPU(); //Assigns a new process to CPU
    }
}

//This function is called whenever the hard disk has finished the work for one process.
void OS::ProcessFinishIOqueue(int hardDiskNumber)
{
    if(harddiskqueue[hardDiskNumber].GetProcessUsingHD().isEmpty()==false) //Makes sure a process is using Hard Disk
    {
        priorityqueue.push(harddiskqueue[hardDiskNumber].GetProcessUsingHD()); //Move the process in Hard Disk into ready queue
        harddiskqueue[hardDiskNumber].clearHardDisk(); //Process leaves Hard Disk
        checkforpreempt(); //Since process entered ready queue
    }
}

void OS::showProcessinReadyQueueandCPU()
{
    cout<<"Using CPU: "<<endl;
    if(ProcessinCPU.isEmpty()==false)
    {
        cout<<ProcessinCPU<<endl; // Cout Process in CPU
    }
    cout<<"In Ready Queue:"<<endl;
    priority_queue<Process, vector<Process>, Comparator> tempqueue=priorityqueue; //Copy queue into temp queue
    while(!tempqueue.empty()) //While temp queue isnt empty
    {
        cout<<tempqueue.top()<<endl; //Cout the top
        tempqueue.pop(); //Pop
    }
}

void OS::showProcessinIOQueueandHardDisk()
{
    for(unsigned int i=0; i<harddiskqueue.size(); i++)
    {
        cout<<harddiskqueue[i]<<endl; // Cout all process in Ready Queue
    }
}

void OS::showMemory()
{   
    cout<<Manager; //Show the Memory
}

//Terminates the currently running process
void OS::terminateProcess()
{
    if(ProcessinCPU.isEmpty()==false) //Makes sure a process is in the CPU
    {
        for(unsigned int i=0; i<allProcesses.size(); i++)
        {
            if(allProcesses[i].GetPID()==ProcessinCPU.GetPID())
            {
                Manager.deleteRam(ProcessinCPU.GetPID());
                ProcessinCPU.clear(); //Process terminated In CPU
                allProcesses.erase(allProcesses.begin()+i); //Erase process from process table
                break;
            }
        }
    }
    assignProcesstoaCPU(); //Since Process left CPU we need to assign new process to CPU
}


#endif