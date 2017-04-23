#include "FSM.h"
#include <iostream>

using namespace std;

FSM::FSM(int numStates, int numInBits, string machType)
{
	states = numStates;
	inBits = numInBits;
	typeFSM = machType; 
}

void FSM::fillStates()
{
	string temp;
	for(int i = 0; i < states; i++)
	{
		cout << "Input state name: ";
		cin >> temp;
		while(temp.size() > 0 && temp.size() < 9)
		{
			cout << "Invalid state name length.\nInput state name: ";
			cin >> temp;
		}
		int j = 0;
		while(j < temp.size())
		{
			if(isalnum(temp[j]) == false)
			{
				j = 0;
				cout << "Invalid state name. Contains non alpha-numeric characters.\nInput state name: ";
				cin >> temp;
			}
			j++;
		}
		addNode(temp);
	}
}

void FSM::addNode(string nodeName)
{
	if(typeFSM == "mealy" || typeFSM == "Mealy")
	{
		MealyNode(nodeName);
	}
	else
	{
		string temp;
		cout << "Input the node output: ";
		cin >> temp;
		while(temp.size() > 0 && temp.size() < 6)
		{
			cout << "Invalid output length.\nInput the node output: ";
			cin >> temp;
		}

		int j = 0;
		while(j < temp.size())
		{
			if(isalnum(temp[j]) == false)
			{
				j = 0;
				cout << "Invalid output. Contains non alphanumeric characters.\nInput the node output: ";
				cin >> temp;
			}
			j++;
		}

		MooreNode(nodeName, temp);
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