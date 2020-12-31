//Brandon Ho DSA1 Program 1
// The following program asks the user for the name of an input text file and output text file. The input file will contain a list of commands (one per each line), and each command will tell the program to either create a stack or queue, pop a value from a stack or queue(dequeue), or push a value into a stack or queue (enqueue). The program will then read through each line of the input file and either execute it or output an specific error message to indicate one of the few problems that may occur while attempting to run the program. The program will then write the output of the program onto an output text file specificed by the user.  
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

template <typename Data>
class SimpleList
{
	class Node
	{
		Data data;
		Node* next;
	public:
		Node(Data d, Node* n = NULL) { data = d, next = n; };
		Data getData() { return data; }
		Node* getNext() { return next; }
		void setNext(Node *n) { next = n; }
	};
	string name;
	Node* head; //Pointer head points to the start of the node
	Node* tail; //Pointer tail points to the end of the node
public:
	SimpleList() { head = NULL; tail = NULL; name = "Temp Name"; };
	SimpleList(string initName) { head = NULL; tail = NULL; name = initName; };
	virtual void push(Data d) = 0;
	virtual Data pop() = 0;
	string getName() { return name; }
	bool isEmpty();
protected:
	void insertStart(Data d);
	void insertEnd(Data d);
	void remove(); 
	Node* getHead() { return head; }
	Node* getTail() { return tail; }
};

//Insert a node at the end of SimpleList 
template <typename Data>
void SimpleList<Data>::insertEnd(Data d)
{
	SimpleList::Node* newNode = new SimpleList::Node(d);
	if (!head)
		head = newNode;
	else
		tail->setNext(newNode);
	tail = newNode;
}

//Insert a node at the start of SimpleList 
template <typename Data>
void SimpleList<Data>::insertStart(Data d)
{
	SimpleList::Node* newNode = new SimpleList::Node(d);
	newNode->setNext(head);
	head = newNode;
}

//Remove a Node at the start of SimpleList
template <typename Data>
void SimpleList<Data>::remove()
{
	if (head && head->getNext())
	{
		Node* tmpNode = head;
		head = head->getNext();
		delete tmpNode;
	}
	else
	{
		head = NULL;
		tail = NULL;
	}
}

//Check if SimpleList is empty or not
template <typename Data>
bool SimpleList<Data>::isEmpty()
{
	if (!head && !tail)
		return true;
	else
		return false;
}

//Properties of a Stack in SimpleList
template <typename Data>
class Stack : public SimpleList<Data>
{
public:
	Stack() : SimpleList<Data>::SimpleName() {}
	Stack(string initName) : SimpleList<Data>::SimpleList(initName) {}
	void push(Data d)
	{
		SimpleList<Data>::insertStart(d);
	}
	Data pop()
	{
		Data tmp = this->getHead()->getData();
		this->remove();
		return tmp;
	}
};


//Properties of a Queue in SimpleList
template <typename Data>
class Queue : public SimpleList<Data>
{
public:
	Queue() : SimpleList<Data>::SimpleName() {}
	Queue(string initName) : SimpleList<Data>::SimpleList(initName) {}
	void push(Data d)
	{
		SimpleList<Data>::insertEnd(d);
	}
	Data pop()
	{
		Data tmp = this->getHead()->getData();
		this->remove();
		return tmp;
	}
};

/*
-----These template functions below are not part of SimpleList----- 
*/

//Check if a specific name exists in list of Simplelist or if a specific Simplelist in list is empty.
template <typename Data>
bool check(list<SimpleList<Data>*> lists, string part1, string name)
{
	typename list<SimpleList<Data>*>::iterator it;
	for (it = lists.begin(); it != lists.end(); ++it)
		if ((*it)->getName() == name)
			if (part1 == "exist")
				return true;
			else if (part1 == "empty")
				return (*it)->isEmpty();
	return false;
}

//Check if a specific name exists in list of Simplelist if so push a value into that specific SimpleList,
template <typename Data>
void pushPrint(list<SimpleList<Data>*> lists, string name, Data val)
{
	typename list<SimpleList<Data>*>::iterator it;
	for (it = lists.begin(); it != lists.end(); ++it)
		if ((*it)->getName() == name)
				(*it)->push(val);
}

//Find a specific name in the list of SimpleList and return the value being popped where it is going to be printed in the output file.
template <typename Data>
void pushPrint(list<SimpleList<Data>*> lists, string name, ofstream& outputF)
{
	typename list<SimpleList<Data>*>::iterator it;
	for (it = lists.begin(); it != lists.end(); ++it)
	{
		if ((*it)->getName() == name)
			outputF << "Value popped: " << (*it)->pop() << endl;
	}
}

//lists of simplelists based on data type (integer, double, or string)
list<SimpleList<int>*> listSLi;
list<SimpleList<double>*> listSLd;
list<SimpleList<string>*> listSLs;

//Open up the Input File
 void Input(ifstream& inputF)
{
	string input; //"input.txt"- string input (user input)
	cout << "Enter the name of input file: ";
	cin >> input;
	//Prints an error message for possible failure in opening input file.
	try
	{
		inputF.open(input);
	}
	catch (ifstream::failure & e)
	{
		cerr << "ERROR: FAILURE TO OPEN INPUT FILE" << typeid(e).name() << endl;
		exit(20);
	}
}

 //Open up the Output File
void Output(ofstream& outputF)
{
	string output; //"output.txt"- string output (program output)
	cout << "Enter the name of output file: ";
	cin >> output;
	//Prints an error message for possible failure in opening output file.
	try
	{
		outputF.open(output);
	}
	catch (ofstream::failure & e)
	{
		cerr << "ERROR: Failure opening output file." << typeid(e).name() << endl;
		exit(20);
	}
}

//Read through the command lines of the input file and output what is given from the command line
void application(ifstream &inputF, ofstream &outputF)
{
	string part1, part2, part3;  // part1, part2, part3 -1st word, 2nd word, 3rd word on the line respectively
	while (inputF >> part1 >> part2) //Input the 1st two words into part1 and part2 because the program is not sure if there is a third word or not on the line depending on the given command
	{
		outputF << "PROCESSING COMMAND: " << part1 << " " << part2;

		//Program proceeds to check part1 on each line.	
		if (part1 == "create")
		{
			inputF >> part3;
			outputF << " " << part3 << endl;
			if (!(check(listSLi, "exist", part2) || check(listSLd, "exist", part2) || check(listSLs, "exist", part2)))  //Check if either all 3 lists have the given name if so Error message
			{
				if (part3 == "stack")  //Program creates stack based on data type (integer, double, or string)
				{
					if (part2.substr(0, 1) == "i")
					{
						SimpleList<int> *pSLi;
						pSLi = new Stack<int>(part2);
						listSLi.push_front(pSLi);
					}
					else if (part2.substr(0, 1) == "d")
					{
						SimpleList<double> *pSLd;
						pSLd = new Stack<double>(part2);
						listSLd.push_front(pSLd);
					}
					else if (part2.substr(0, 1) == "s")
					{
						SimpleList<string> *pSLs;
						pSLs = new Stack<string>(part2);
						listSLs.push_front(pSLs);
					}
				}
				else if (part3 == "queue")  //Program creates queue based on data type (integer, double, or string)
					if (part2.substr(0, 1) == "i")
					{
						SimpleList<int> *pSLi;
						pSLi = new Queue<int>(part2);
						listSLi.push_front(pSLi);
					}
					else if (part2.substr(0, 1) == "d")
					{
						SimpleList<double> *pSLd;
						pSLd = new Queue<double>(part2);
						listSLd.push_front(pSLd);
					}
					else if (part2.substr(0, 1) == "s")
					{
						SimpleList<string> *pSLs;
						pSLs = new Queue<string>(part2);
						listSLs.push_front(pSLs);
					}
			}
			else
				outputF << "ERROR: This name already exists!" << endl;
		}
		else if (part1 == "push")
		{
			inputF >> part3;
			outputF << " " << part3 << endl;

			//Check if one of the lists contains the given name of a simplelist if so push the value into that simplelist
			if (check(listSLi, "exist", part2))
			{
				pushPrint(listSLi, part2, stoi(part3));
			}
			else if (check(listSLd, "exist", part2))
			{
				pushPrint(listSLd, part2, stod(part3));
			}
			else if (check(listSLs, "exist", part2))
			{
				pushPrint(listSLs, part2, part3);
			}
			else
				outputF << "ERROR: This name does not exist!" << endl;

		}
		else if (part1 == "pop")
		{
			outputF << endl;
			//Check if one of the lists contains the given name of a simplelist if so check if that simplelist is empty if so print the popped value of that simplelist
			if (check(listSLi, "exist", part2))
			{
				if (!check(listSLi, "empty", part2))
					pushPrint(listSLi, part2, outputF);
				else
					outputF << "ERROR: This list is empty!" << endl;
			}
			else if (check(listSLd, "exist", part2))
			{
				if (!check(listSLd, "empty", part2))
					pushPrint(listSLd, part2, outputF);
				else
					outputF << "ERROR: This list is empty!" << endl;
			}
			else if (check(listSLs, "exist", part2))
			{
				if (!check(listSLs, "empty", part2))
					pushPrint(listSLs, part2, outputF);
				else
					outputF << "ERROR: This list is empty!" << endl;
			}
			else
				outputF << "ERROR: This name does not exist!" << endl;
		}
	}
}

int main()
{
	//Create Stream class from the input and output file
	ifstream inputF; 
	ofstream outputF;

	//User-program interaction
	Input(inputF); 
	Output(outputF);

	//Read through the command lines of the input file and output what is given from the command line
	application(inputF, outputF);  

	//Close both input and output file
	inputF.close();
	outputF.close();
	return 0;
}

