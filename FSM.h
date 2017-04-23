#include <string>
#include <vector>


//program will ask user to define # of states, # of input bits, and Mealy/Moore
//before requesting further input

class FSM
{
	public:
		FSM(int, int, std::string);
		void fillStates();
		void addNode(std::string);

	private:
		int states;
		int inBits;
		int maxArcs;
		std::string typeFSM;
		std::vector<Node*> nodes;
		std::vector<Arc*> arcs;
};
 
class Node
{
	public:
		Node(std::string);
	private:
		std::string name;
};

class Arc
{
	public:
		Arc(Node*, Node*, std::string);
	private:
		std::string node1;
		std::string node2;
		Node * pair[2];
		std::string inputs;
};

class MooreNode : public Node
{
	public:
		MooreNode(std::string, std::string);
	private:
		std::string output;
};

class MooreArc : public Arc
{
	public:
		MooreArc()
	private:

};

class MealyNode : public Node
{


};

class MealyArc : public Arc
{
	public:
		MealyArc(Node*, Node*, std::string, std::string);
	private:
		std::string output;
};
