#ifndef SIMULATION_CPP
#define SIMULATION_CPP

#include "Simulation.hpp"

//Splits the input command
vector<string> Simulation::splitCommandsUp(string command)
{
    string stringseg;
	vector<string> info;
    stringstream test(command);
	while(getline(test, stringseg, ' ')) //Split the string by whitespace
	{
		info.push_back(stringseg); //Push each segment into a vector
	}
    return info;
}

//Makes sure the user input a number
bool Simulation::isANum(string number)
{
    for(unsigned int i=0; i<number.length(); i++)
    {
        if (!isdigit(number[i]))
        {
            return false;
        }
    }
    return true;
}

//Gets next input command
string Simulation::commandinput()
{
    string command;
	cout<<"> ";
	getline(cin,command); //Gets the next user input
	return command; //Return that user input
}

//Prompts user to enter number of hard disk for the simulation
int Simulation::getNumberOfHardDisk()
{
    string numOfHD;
    cout<<"How many hard disks does the simulated computer have?"<<endl; //Prompts user to enter numbers
    getline(cin, numOfHD); //Prompts user input
    while(isANum(numOfHD)==false || stoi(numOfHD)==0 || numOfHD[0]=='0') //Makes sure input is a number and is greater than 0 and does not start with 0
    {
        cout<<"Please enter a number"<<endl;
        getline(cin, numOfHD);
    }
    return stoi(numOfHD);
}

//Prompts user to enter a number for ram memory
long Simulation::getNumberOfRam()
{
    string ramSize;
    cout<<"How much RAM memory is there on the simulated computer?"<<endl; //Prompts user to enter numbers
    getline(cin, ramSize); //Prompts user input
    while(isANum(ramSize)==false || stol(ramSize)==0 || ramSize[0]=='0') //Makes sure input is a number and is greater than 0 and does not start with 0
    {
        cout<<"Please enter a number"<<endl;
        getline(cin, ramSize);
    }
    return stol(ramSize);
}

void Simulation::simulateOS()
{
    int numberOfHardDisk=getNumberOfHardDisk(); //Gets number of Hard Disk
    long ramSize=getNumberOfRam(); //Gets Ram Size
    OS myOS;
    myOS.createHardDisk(numberOfHardDisk); //Creates OS with the number of Hard Disk
    myOS.createRam(ramSize); //Creates OS with number of Ram
    string command="";
    while(command!="EXIT")
    {
        command=commandinput(); //Gets next input
        vector<string> commandinfo=splitCommandsUp(command); //Splits up the command by white spaces
        if(commandinfo.size()==3 && commandinfo[0]=="A" && isANum(commandinfo[1]) == true && isANum(commandinfo[2]) == true && stoi(commandinfo[1])!=0 && stoi(commandinfo[2])!=0)
        {
            myOS.createProcess(stoi(commandinfo[1]), stol(commandinfo[2])); // Creates Process
        }
        else if(commandinfo.size()==3 && commandinfo[0]=="d" && isANum(commandinfo[1]) == true && stoi(commandinfo[1]) < numberOfHardDisk)
        {
            myOS.moveProcessToIOqueue(stoi(commandinfo[1]), commandinfo[2]);//Process request Hard Disk
        }
        else if(commandinfo.size()==2 && commandinfo[0]=="D" && isANum(commandinfo[1]) == true && stoi(commandinfo[1]) < numberOfHardDisk)
        {
            myOS.ProcessFinishIOqueue(stoi(commandinfo[1])); //Process has finished work in Hard Disk
        }
        else if(command=="S r")
        {
            myOS.showProcessinReadyQueueandCPU(); //Shows all process in the CPU and in ready Queue
        }
        else if(command=="S i")
        {
            myOS.showProcessinIOQueueandHardDisk(); //Shows all process using CPU and in I/O Queue
        }
        else if(command=="S m")
        {
            myOS.showMemory();//Shows the state of memory.
        }
        else if(command=="t")
        {
            myOS.terminateProcess();//Terminate currently running process
        }
        else
        {
            cout<<"Invalid command"<<endl;
        }
    }
}

#endif