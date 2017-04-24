#include "FSM.h"
#include <iostream>
#include <math.h>

using namespace std;

FSM::FSM(int numStates, int numInBits, string machType)
{
	states = numStates;
	inBits = numInBits;
	typeFSM = machType; 
}

FSM::~FSM() 
{
	for (vector< Node* >::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    	delete (*it);
   	} 
   	nodes.clear();
	
	for (vector< Arc* >::iterator it = arcs.begin(); it != arcs.end(); ++it) {
    	delete (*it);
   	} 
   	arcs.clear();
	
}

void FSM::fillStates()
{
	string temp;
	for(int i = 0; i < states; i++)
	{
		cout << "Input state name: ";
		cin >> temp;
	
		bool valLen = false;
		bool valAlNum = false;
		int j;
		while(!valLen && !valAlNum)
		{
			valLen = true;
			valAlNum = true;

			if(temp.size() < 0 || temp.size() > 8)
			{
				valLen = false;
				cout << "Invalid state name length.\nInput state name: ";
				cin >> temp;
			}

			j = 0;
			while(j < temp.size() && valAlNum)
			{
				if(isalnum(temp[j]) == false)
				{
					valAlNum = false;
					cout << "Invalid state name. Contains non alpha-numeric characters.\nInput state name: ";
					cin >> temp;
				}
				else j++;
			}
		}
		addNode(temp);
	}
}

void FSM::addNode(string nodeName)
{
	bool valLen = false;
	bool valAlNum = false;
	int j;

	Node* tempPtr;

	if(typeFSM == "mealy")
	{
		tempPtr = new MealyNode(nodeName);
		nodes.push_back(tempPtr);
	}
	else
	{
		string temp;
		cout << "Input the node output: ";
		cin >> temp;
		
		while(!valLen && !valAlNum)
		{
			valLen = true;
			valAlNum = true;

			if(temp.size() < 0 || temp.size() > 5)
			{
				valLen = false;
				cout << "Invalid output length.\nInput the node output: ";
				cin >> temp;
			}

			j = 0;
			while(j < temp.size() && valAlNum)
			{
				if(isalnum(temp[j]) == false)
				{
					valAlNum = false;
					cout << "Invalid output. Contains non alpha-numeric characters.\nInput the node output: ";
					cin >> temp;
				}
				else j++;
			}
		}
		tempPtr = new MooreNode(nodeName, temp);
		nodes.push_back(tempPtr);
	}
}

void FSM::addArc(Node* start, Node* end, string in)
{
	Arc* tempPtr;
	if(typeFSM == "moore")
	{
		tempPtr = new MooreArc(start, end, in);
		arcs.push_back(tempPtr);
	}
	else
	{
		bool valLen = false;
		bool valAlNum = false;
		int j;

		string temp;
		cout << "Input the arc output: ";
		cin >> temp;

		while(!valLen && !valAlNum)
		{
			valLen = true;
			valAlNum = true;

			if(temp.size() < 0 || temp.size() > 5)
			{
				valLen = false;
				cout << "Invalid output length.\nInput the node output: ";
				cin >> temp;
			}

			j = 0;
			while(j < temp.size() && valAlNum)
			{
				if(isalnum(temp[j]) == false)
				{
					valAlNum = false;
					cout << "Invalid output. Contains non alpha-numeric characters.\nInput the node output: ";
					cin >> temp;
				}
				else j++;
			}
		}
		tempPtr = new MealyArc(start, end, in, temp);
		arcs.push_back(tempPtr);
		
	}
}

bool FSM::inputOverlap(string str1, string str2)
{
	bool overlap = true;
	int i = 0;
	while(i < str1.size() && overlap)
	{
		if(str1[i] != str2[i] || (str1[i] != 'x' || str1[i] != 'X' || str2[i] != 'x' || str2[i] != 'X'))
		{
			overlap = false;
		}
		i++;
	}
	return overlap;
}

void FSM::fillArcs()
{
	string stateName;
	string inputName;
	Node* startPtr;
	Node* endPtr;
	int xCount;
	int numArcs = 0;
	int totalPossibleArcs = states * pow(2, inBits);
	bool isReal = false;
	
	while (numArcs < totalPossibleArcs) {
		xCount = 0;
		cout << "Input the start node of the new arc (type CANCEL to stop adding): ";
		cin  >> stateName;
		if(stateName == "CANCEL")
		{
			cout << "Arc additions terminated." << endl;
			break;
		}
		while (!isReal) {
			for (vector< Node* >::iterator it = nodes.begin(); it != nodes.end(); ++it) {
				if ((*it)->getName() == stateName) {
					if((*it)->getArcs() < pow(2, inBits))
					{
						isReal = true;
						startPtr = (*it);
						break;
					}
					else 
						cout << "Arc list full for input node.";
				}
			}

			if (!isReal) {
				cout << "Invalid node. \nInput the start node of the new arc: ";
				cin >> stateName;
			}

		}
		isReal = false;

		cout << "Input the end node of the new arc: ";
		cin  >> stateName;
		while (!isReal) {
			for (vector< Node* >::iterator it = nodes.begin(); it != nodes.end(); ++it) {
				if ((*it)->getName() == stateName) {
					isReal = true;
					endPtr = (*it);
					break;
				}
			}

			if (!isReal) {
				cout << "Invalid node. \nInput the end node of the new arc: ";
				cin  >> stateName;
			}
		}

		isReal = false;

		cout << "Input the input of the new arc: ";
		cin  >> inputName;
		while (!isReal) {
			if (inputName.size() != inBits) {
				cout << "Invalid input. \nPlease input the input of the new arc: ";
				cin  >> inputName;

			} else {
		
				isReal = false;
				while (!isReal) {
					for (int i = 0; i < inputName.size(); i++) {
						if (inputName[i] != '1' && inputName[i] != '0' && inputName[i] != 'x' && inputName[i] != 'X') {
							isReal = false;
							break;
						} else {
							isReal = true;
						}
					}
					if (!isReal) {
						cout << "Invalid input. \nPlease input the input of the new arc: ";
						cin >> inputName;
					} else {
						for (vector< Arc* >::iterator it = arcs.begin(); it != arcs.end(); ++it) {
							if ((*it)->getFromNode() == stateName && inputOverlap(inputName, (*it)->getInputs())) {
								cout << "Invalid input. Overlaps with " << (*it)->getInputs() << ".\nPlease input the input of the new arc:";
								cin >> inputName;
							}
						}
					}
				}
			}
		}
		addArc(startPtr, endPtr, inputName);
		for(int j = 0; j < inputName.size(); j++)
		{
			if(inputName[j] == 'x' || inputName[j] == 'X')
				xCount++;
		}
		numArcs +=	pow(2, xCount);
		startPtr->setArcs(pow(2, xCount));
	}
}

void FSM::printGraph() 
{
	string nodeName = "";
	string currentNode;
	int nodesPrinted = 0;
	while (nodesPrinted < states)  {
		vector< Node* >::iterator i;
		for(vector< Node* >::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			currentNode = (*it)->getName();
			bool isTrue = (*it)->marked;
			if (currentNode < nodeName && !isTrue && nodeName != "") {
				nodeName = currentNode;
				cout << nodeName << "\n";
				i = it;
			} else if (nodeName == ""){
				nodeName = currentNode;
				i = it;
			} 
		}
		nodesPrinted++;
		cout << nodeName << "\n\t";

		for(vector< Arc* >::iterator it = arcs.begin(); it != arcs.end(); ++it) {
			currentNode = (*it)->getStartNode();
			cout << nodeName << "\n";
			if (currentNode == nodeName) {
				(*it)->printArc();
				cout << "\t";
			}
		}
		cout << "\r";
		if (nodesPrinted < states) {
			(*i)->marked = true;
		} else {
			break;
		}
	}
	cout << "\n";
}

void FSM::printTable()
{
	string inArry[16];
	int size = pow(2, inBits);
	bool add = false;
	cout << "Current	|		Next State / Output" << endl;
	cout << "State  	| ";
	if(inBits == 1)
	{
		inArry[0] = "0";
		inArry[1] = "1";
		cout << "X = 0	X = 1" << endl;
		cout << "---------------------------" << endl;
	}
	else if(inBits == 2)
	{
		inArry[0] = "00";
		inArry[1] = "01"; 
		inArry[2] = "10";
		inArry[3] = "11";
		cout << "X = 00	X = 01	X = 10	X = 11" << endl;
		cout << "---------------------------------------" << endl;
	}
	else if(inBits == 3)
	{
		inArry[0] = "000";
		inArry[1] = "001"; 
		inArry[2] = "010";
		inArry[3] = "011";
		inArry[4] = "100";
		inArry[5] = "101"; 
		inArry[6] = "110";
		inArry[7] = "111";
		cout << "X = 000	X = 001	X = 010	X = 011	X = 100	X = 101	X = 110	X = 111" << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
	}
	else 
	{
		inArry[0] = "0000";
		inArry[1] = "0001"; 
		inArry[2] = "0010";
		inArry[3] = "0011";
		inArry[4] = "0100";
		inArry[5] = "0101"; 
		inArry[6] = "0110";
		inArry[7] = "0111";
		inArry[8] = "1000";
		inArry[9] = "1001"; 
		inArry[10] = "1010";
		inArry[11] = "1011";
		inArry[12] = "1100";
		inArry[13] = "1101"; 
		inArry[14] = "1110";
		inArry[15] = "1111";
		cout << "X = 0000	X = 0001	X = 0010	X = 0011	X = 0100	X = 0101	X = 0110	X = 0111	X = 1000	X = 1001	X = 1010	X = 1011	X = 1100	X = 1101	X = 1110	X = 1111" << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
	for (vector< Node* >::iterator itNd = nodes.begin(); itNd != nodes.end(); ++itNd)
		{
			cout << (*itNd)->getName() << "	| ";
			for(int i = 0; i < size; i++)
			{
				for(vector< Arc* >::iterator itAr = arcs.begin(); itAr != arcs.end(); ++itAr) 
				{
					if((*itNd)->getName() == (*itAr)->getFromNode() && inputOverlap(inArry[i], (*itAr)->getInputs()))
					{
						add = true;
						cout << (*itAr)->getToNode() << " / ";
						if(typeFSM == "moore")
							cout << (*itAr)->getToPtr()->getOut() << "	";
						else
							cout << (*itAr)->getOut() << "	";
					}
				}
				if(!add)
				{
					cout << "x / x	";
				}
				else add = false;
			}
			cout << endl;
		}
}

Node::Node(string nodeName)
{
	name = nodeName;
	marked = false;
}

string Node::getName()
{
	return name;
}

string MealyNode::getOut()
{
	return "An error has occured. Function only called by MealyNode.";
}

int Node::getArcs()
{
	return arcs;
}

void Node::setArcs(int arcAdd)
{
	arcs += arcAdd;
}

Arc::Arc(Node* n1Ptr, Node* n2Ptr, string inputBits)
{
	pair[0] = n1Ptr;
	pair[1] = n2Ptr;
	inputs = inputBits;
	fromNode = n1Ptr->getName();
	toNode = n2Ptr->getName();
}

string Arc::getStartNode() {
	return fromNode;
}

string Arc::getFromNode()
{
	return fromNode;
}

string MooreArc::getOut()
{
	return "An error has occured. Function only called by Moore";
}

string Arc::getToNode()
{
	return toNode;
}

string Arc::getInputs()
{
	return inputs;
}

Node* Arc::getToPtr()
{
	return pair[1];
}

MooreNode::MooreNode(string nodeName, string out) : Node(nodeName)
{
	output = out;
}

string MooreNode::getOut()
{
	return output;
}

MooreArc::MooreArc(Node* n1Ptr, Node* n2Ptr, std::string inputBits) : Arc(n1Ptr, n2Ptr, inputBits)
{
	//calls parent constuctor
}

void MooreArc::printArc() {
	string in = getInputs();
	cout << toNode << " " << in << "\n";
}

MealyNode::MealyNode(std::string nodeName) : Node(nodeName)
{
	//calls parent constructor
}

MealyArc::MealyArc(Node* n1Ptr, Node* n2Ptr, string inputBits, string out) : Arc(n1Ptr, n2Ptr, inputBits)
{
	output = out;	
}

void MealyArc::printArc() {
	string in = getInputs();
	cout << toNode << " " << in << " / " << output << "\n";
}

string MealyArc::getOut()
{
	return output;
}