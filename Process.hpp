#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>

using namespace std;

class Process
{
public:
    Process(int id, int priority, int memory_size)
    {
        pid=id;
        memorySize=memory_size;
        priority_number=priority;
        cout<<"Process "<<pid<<" created with priority "<<priority_number<<" and memory size "<<memorySize<<endl;
    }
    ~Process(){}

    int GetPID()
    {
        return pid;
    }

    int GetPriority()
    {
        return priority_number;
    }

    void isUsingCPU()
    {
        usingCPU=true;
    }

    void isNotUsingCPU()
    {
        usingCPU=false;
    }
    bool isitUsingCPU()
    {
        return usingCPU;
    }

    friend ostream& operator<<(ostream &out, Process &a_process)
    {
        out<<"PID: "<<a_process.GetPID()<<" Priority: "<<a_process.GetPriority();
        return out;
    }

private:
    int memorySize;
    int pid;
    int priority_number;
    bool usingCPU=false;
};

#endif
