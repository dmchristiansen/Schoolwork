//calc.h
//prototypes for class object, as well as stack and queue structures

#include <iostream>
using namespace std;

class calculation {
	public:
		calculation();
		~calculation();
		int calculate(calculation toDo);
		double calculate(double & first_operand);
		int passback(char & direction, char & operation, double & operand);
		int create(char new_direction, char new_operation, double new_operand);
		int copy(const calculation &calc);
		int retrieve(calculation &found) const;	
		int compare(char c_operation, double operand);
		int display();

	private:
		char direction; //do or undo
		char operation;
		double operand;
};

struct node {
	calculation calc;
	node * next;
};

class queue {
	public:
		queue();
		~queue();
		int enqueue(const calculation toAdd);
		int dequeue(const calculation &toDo);	
		int displayall();

	private:
		node * rear;
};

class stack {
	public:
		stack(void);
		~stack(void);
		int push(const calculation toAdd);
		int pop(void);
		int peek(calculation &toShow) const;
		node * flip();
		node * flip(node * head);
	private:
		node * head;
		node * fhead;
};
