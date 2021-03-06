#include <string>
#include <vector>


//program will ask user to define # of states, # of input bits, and Mealy/Moore
//before requesting further input

class Node
{
	public:
		Node(std::string );
		Node(const Node &obj);
		std::string getName();
		int getArcs();
		void setArcs(int );
		bool marked;
		virtual std::string getOut() =0;

	private:
		std::string name;
		int arcs = 0;
};

class Arc
{
	public:
		Arc(Node* , Node* , std::string );
		std::string getFromNode();
		std::string getToNode();
		std::string getInputs();
		std::string getStartNode();
		Node* getToPtr();
		virtual void printArc() =0;
		virtual std::string getOut() =0;
	protected:
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
		bool inputOverlap(std::string, std::string );
		void printGraph();
		void printTable();

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
		std::string getOut();
	private:
		std::string name;
		std::string output;
};

class MooreArc : public Arc
{
	public:
		MooreArc(Node* , Node* , std::string );
		void printArc(); 
		std::string getOut();
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
		std::string getOut();
	private:
		std::string name;
};

class MealyArc : public Arc
{
	public:
		MealyArc(Node* , Node* , std::string , std::string );
		void printArc();
		std::string getOut();
	private:
		std::string inputs;
		std::string output;
};
