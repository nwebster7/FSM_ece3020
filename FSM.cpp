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
			while(j < temp.size() || valAlNum)
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

	if(typeFSM == "mealy")
	{
		nodes.push_back(MealyNode(nodeName))
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
				cout << "Invalid state name length.\nInput state name: ";
				cin >> temp;
			}

			j = 0;
			while(j < temp.size() || valAlNum)
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
		nodes.push_back(MooreNode(nodeName, temp));
	}
}

Node::Node(string nodeName)
{
	name = nodeName;
}

Arc::Arc(Node node1, Node node2, string inputBits)
{
	pair[0] = node1;
	pair[1] = node2;
	inputs = inputBits;
}

MooreNode::MooreNode(string nodeName, string out) : Node(nodeName)
{
	output = out;
}

MooreArc::MooreArc(Node node1, Node node2, std::string inputBits) : Arc(node1, node2, inputBits)
{
	//calls parent constuctor
}

MealyNode::MealyNode(std::string nodeName) : Node(nodeName)
{
	//calls parent constructor
}

MealyArc::MealyArc(Node node1, Node node2, string inputBits, string out) : Arc(node1, node2, inputBits)
{
	output = out;	
}