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
		cout << "Input the start node of the new arc: ";
		cin  >> stateName;
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
	string nodeName;
	string currentNode;
	vector < Node* > temp = nodes;
	while (nodes.size() > 0) {
		vector< Node,* >::iterator i;
		for(vector< Node,* >::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			currentNode = (*it)->getName();
			if (it == nodes.begin()) {
				nodeName = currentNode;
			} else if (currentNode < nodeName) {
				nodeName = currentNode;
				i = it;
			}
		}

		delete (*i);
		erase (i);
		nodes.shrink_to_fit();

		cout << nodeName << "\n\t";

		for(vector< Arc* >::iterator it = arcs.begin(); it != arcs.end(); ++it) {
			currentNode = (*it)->getStartNode();
			if (currentNode == nodeName) {
				(*it)->printArc();
				cout << "\t";
			}
		}
	}
}

void FSM::printTable()
{

}

Node::Node(string nodeName)
{
	name = nodeName;
}

string Node::getName()
{
	return name;
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

string Arc::getInputs()
{
	return inputs;
}

MooreNode::MooreNode(string nodeName, string out) : Node(nodeName)
{
	output = out;
}

MooreArc::MooreArc(Node* n1Ptr, Node* n2Ptr, std::string inputBits) : Arc(n1Ptr, n2Ptr, inputBits)
{
	//calls parent constuctor
}

void MooreArc::printArc() {
	cout << toNode << " " << inputs << "\n";
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
	cout << toNode << " " << inputs << " / " << output << "\n";
}