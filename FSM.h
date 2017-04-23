#include <string>
#include <vector>


//program will ask user to define # of states, # of input bits, and Mealy/Moore
//before requesting further input

class Node
{
	public:
		Node(std::string );
		bool getHasBeenUsed();
		void setHasBeenUsed(bool );
		std::string getName();
	private:
		std::string name;
		bool hasBeenUsed;
};

class Arc
{
	public:
		Arc(Node* , Node* , std::string );
	private:
		std::string fromNode;
		std::string toNode;
		Node * pair[2];
		std::string inputs;
};

class FSM
{
	public:
		FSM(int , int , std::string );
		~FSM();
		void fillStates();
		void addNode(std::string );
		void fillArcs();
		void addArc(Node*, Node*, std::string);

	private:
		int states;
		int inBits;
		int maxArcs;
		std::string typeFSM;
		std::vector<Node*> nodes;
		std::vector<Arc*> arcs;
};


/************************************************
	Moore Classes
************************************************/
class MooreNode : public Node
{
	public:
		MooreNode(std::string , std::string );
	private:
		std::string name;
		std::string output;
};

class MooreArc : public Arc
{
	public:
		MooreArc(Node* , Node* , std::string ); 
	private:
		std::string inputs;
};


/************************************************
	Mealy Classes	
************************************************/
class MealyNode : public Node
{
	public:
		MealyNode(std::string );
	private:
		std::string name;
};

class MealyArc : public Arc
{
	public:
		MealyArc(Node* , Node* , std::string , std::string );
	private:
		std::string inputs;
		std::string output;
};
