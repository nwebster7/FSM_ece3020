/********************************************************/
	//main.cc
/********************************************************/

#include "FSM.h"
#include <math.h>
#include <iostream>

using namespace std;

int main() {
	string machineType;
	int numOfStates;
	int numOfInputBits;
	
	//Gets the machine type
	cout << "Please input type of finite state machine (Mealy or Moore): ";
	cin  >> machineType;

	while (machineType != "Mealy" && machineType != "mealy" && machineType != "Moore" && machineType != "moore") {
		cout << "Invalid type of finite state machine. \nPlease input type of finite state machine (Mealy or Moore): ";
		cin  >> machineType;
	}    

	//Gets the number of states
	cout << "Please input the total number of states (Between 1 and 25 inclusive): ";
	cin  >> numOfStates;

	while (numOfStates > 25 || numOfStates < 1) {
		cout << "Invalid number of states. \nPlease input the total number of states (Between 1 and 25 inclusive): ";
		cin  >> numOfStates;
	}

	//Gets the number of input bits
	cout << "Please input the number of input bits: (Between 1 and 4 inclusive): ";
	cin  >> numOfInputBits;

	while (numOfInputBits > 4 || numOfInputBits < 1) {
		cout << "Invalid number of input bits. \nPlease input the number of input bits: (Between 1 and 4 inclusive): ";
		cin  >> numOfInputBits;
	}

	//Converts machine type to lower case
	int i = 0;
	while (i < machineType.size()) {
		machineType[i] -= 32;
		i++;
	}

	//FSM that will be worked on
	FSM myFSM(numOfStates, numOfInputBits, machineType);
	
	//User fills all states
	myFSM.fillStates();

}