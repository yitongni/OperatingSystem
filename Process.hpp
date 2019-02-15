#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <string>

using namespace std;

class Process
{
public:

    Process(){}//Default
    Process(int id, int priority, long memory_size);
    ~Process(){} //Default Destructor

    int GetPID(){
        return pid;
    }

    int GetPriority() const{
        return priority_number;
    }

    string GetFilename(){
        return filename;
    }

    void assignFile(string file){
        filename=file;
    }

    long getMem()
    {
        return memorySize;
    }

    bool isEmpty(); // Check to see if Process is "empty"
    void clear(); // "Empty" the process of information

    friend ostream& operator<<(ostream &out, Process a_process)
    {
        out<<"PID: "<<a_process.GetPID()<<" Priority: "<<a_process.GetPriority();
        return out;
    }

private:
    long memorySize=0;
    int pid=0;
    int priority_number=0;
    string filename;
};

#endif