#include "FSM.h"
#include <iostream>

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

Node::Node(string nodeName)
{
	name = nodeName;
	hasBeenUsed = false;
}

bool Node::getHasBeenUsed() 
{
	return hasBeenUsed;
}

void Node::setHasBeenUsed(bool used)
{
	hasBeenUsed = used;
}

string Node::getName()
{
	return name;
}

Arc::Arc(Node* n1Ptr, Node* n2Ptr, string inputBits)
{
	pair[0] = n1Ptr;
	pair[1] = n2Ptr;
	inputs = inputBits;
}

MooreNode::MooreNode(string nodeName, string out) : Node(nodeName)
{
	output = out;
}

MooreArc::MooreArc(Node* n1Ptr, Node* n2Ptr, std::string inputBits) : Arc(n1Ptr, n2Ptr, inputBits)
{
	//calls parent constuctor
}

MealyNode::MealyNode(std::string nodeName) : Node(nodeName)
{
	//calls parent constructor
}

MealyArc::MealyArc(Node* n1Ptr, Node* n2Ptr, string inputBits, string out) : Arc(n1Ptr, n2Ptr, inputBits)
{
	output = out;	
}