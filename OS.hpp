#ifndef OS_HPP
#define OS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include "Process.hpp"
#include "HardDisk.hpp"
#include "MemoryBlock.hpp"
#include "MemoryManager.hpp"
//#include "CPU.hpp"

using namespace std;

class OS
{
public:
    OS(){}//Constructor
    ~OS(){}//Destructor

    //Startup functions
    void createHardDisk(int numOfHD); //Creates the number of HardDisk
    void createRam(long Ram); //Creates the memory

    //Terminal Functions
    void createProcess(int priority_num, long memorySize); //Creates process
    void moveProcessToIOqueue(int hardDiskNumber, string filename); //This function is called whenever process currently in CPU requests the hard disk 
    void ProcessFinishIOqueue(int hardDiskNumber);//This function is called whenever the hard disk has finished the work for one process.
    void showProcessinReadyQueueandCPU(); //Shows all process in the CPU and in ready Queue
    void showProcessinIOQueueandHardDisk(); //Show the Hard disk
    void terminateProcess(); // Terminates the current process using CPU
    void showMemory();//Shows the state of the memory
    

    //Helper Functions
    void checkforpreempt(); //Determines if we need to preempt
    void assignProcesstoaCPU(); //Assigns Process to CPU when CPU is not empty
    
private:
    struct Comparator{
        bool operator()(const Process a, const Process b)
        {
            return a.GetPriority() < b.GetPriority();
        }
    };
    vector<Process> allProcesses;
    int pid=1;
    priority_queue<Process, vector<Process>, Comparator> priorityqueue;
    Process ProcessinCPU;
    vector<HardDisk> harddiskqueue;
    MemoryManager Manager;
    //CPU theCPU;
    
};

#endif