#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <string>
#include <cctype>
#include "OS.hpp"

using namespace std;

class Simulation
{
public:
    Simulation(){}
	~Simulation(){}

    void simulateOS(); //Starts the OS
    int getNumberOfHardDisk(); //Prompts user to enter number of hard disk for the simulation
    long getNumberOfRam(); //Prompts user to enter a number for ram memory
    string commandinput(); //Gets the next command input
    vector<string> splitCommandsUp(string command); //Split up the commands into sections
    bool isANum(string number); //Determines if the string is a number
};

#endif