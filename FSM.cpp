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
	nodes.clear();
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

Node::Node(string nodeName)
{
	name = nodeName;
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