#ifndef OS_CPP
#define OS_CPP

#include <iostream>
#include "OS.hpp"

using namespace std;
OS::~OS()
{
    cout<<"Hi"<<endl;
    for(int i=0; i<allProcesses.size(); i++)
	{
		delete allProcesses[i];
	}
    while(!priorityqueue.empty())
    {
        delete priorityqueue.front();
    }
}
void OS::simulateOS()
{
    string command="";
    while(command!="EXIT")
    {
        command=commandinput(); //Gets next input
        if(command[0]=='A')
        {
            createProcess(command);
            pid++; //increment PID
        }
        else if(command=="S r")
        {
            showProcessinReadyQueueandCPU();
        }
    }
}

void OS::assignProcesstoaCPU(Process* a_process)
{
    if(processUsingCPU==nullptr) //If CPU is empty 
    {
        sort(priorityqueue.begin(), priorityqueue.end(), sortbypriority); //Sort Process by order of priority descending
        processUsingCPU=priorityqueue[0]; 
        priorityqueue[0]->isUsingCPU();
    }
    else
    {
        if(processUsingCPU->GetPriority() < a_process->GetPriority()) //If new process has a greater priority
        {
            a_process->isUsingCPU(); //New Process is using CPU
            processUsingCPU->isNotUsingCPU(); //Old Process isn't using CPU
            processUsingCPU=a_process; //Preempt
            
        }
    }
}

void OS::createProcess(string command)
{
    string stringseg;
	vector<string> processinfo;
    stringstream test(command);
	while(getline(test, stringseg, ' ')) //Split the string by whitespace
	{
		processinfo.push_back(stringseg); //Push each segment into a vector
	}
    Process* a_process=new Process(pid, stoi(processinfo[1]), stoi(processinfo[2]));//Creates Process
    allProcesses.push_back(a_process); // Push process into a list of all process
    priorityqueue.push_back(a_process); // Push process into priority queue
    assignProcesstoaCPU(a_process); //Assign Process to CPU
}

void OS::showProcessinReadyQueueandCPU()
{
    for(int i=0; i<priorityqueue.size(); i++)
    {
        if(priorityqueue[i]->isitUsingCPU()==true) //If Process is in CPU
        {
            cout<<(*priorityqueue[i])<<" (Currently using CPU)"<<endl;
        }
        else //If Process is in ready queue
        {
            cout<<(*priorityqueue[i])<<" (In Ready Queue)"<<endl;
        }
    }
}

bool OS::sortbypriority(Process* p1, Process* p2) //Sort by Priority
{
	return p1->GetPriority()>p2->GetPriority(); //Sort Process by order of priority descending
}

string OS::commandinput()
{
    string command;
	cout<<"> ";
	getline(cin,command);
	return command;
}

#endif