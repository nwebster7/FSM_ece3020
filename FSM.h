#include <string>
#include <vector>


//program will ask user to define # of states, # of input bits, and Mealy/Moore
//before requesting further input

<<<<<<< HEAD
class FSM
{
	public:
		FSM(int , int , std::string );
		~FSM();
		void fillStates();
		void addNode(std::string );
		void fillArcs();

	private:
		int states;
		int inBits;
		int maxArcs;
		std::string typeFSM;
		std::vector<Node*> nodes;
		std::vector<Arc*> arcs;
};
 
=======
>>>>>>> 5a7ea07af108333cc6829b0808290229cbec38a0
class Node
{
	public:
		Node(std::string );
	private:
		std::string name;
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
		void fillStates();
		void addNode(std::string );
		void fillArcs();

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
