#ifndef OS_HPP
#define OS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "Process.hpp"

using namespace std;

class OS
{
public:
    OS()
    {
        cout<<"Starting OS"<<endl;
    } //Constructor
    ~OS();//Destructor
    
    void simulateOS();
    void createProcess(string command); //Creates Process
    string commandinput(); //Gets the next command input
    void assignProcesstoaCPU(Process* a_process); // Assigns Process to CPU
    void showProcessinReadyQueueandCPU(); //Shows all process in the CPU and in ready Queue
    static bool sortbypriority(Process* p1, Process* p2); //Sorts Process by priority descending
private:

    vector<Process*> allProcesses;
    int pid=1;
    vector<Process*> priorityqueue;
    Process* processUsingCPU=nullptr;
};

#endif