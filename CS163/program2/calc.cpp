//calc.cpp

#include "calc.h"

//calculation
calculation::calculation()
{
	operation = ' ';
	operand = 0;	
}

calculation::~calculation()
{
	
}

//takes in a calc struct, performs operation on called
int calculation::calculate(calculation toDo)
{
	toDo.calculate(operand);	
}

//performs calculation on the operand that is passed in, based on this object's operation
double calculation::calculate(double & first_operand)
{
	switch (operation) {
		case '*':
			return (first_operand *= operand);
		case '/':
			return (first_operand /= operand);
		case '+':
			return (first_operand += operand);
		case '-':
			return (first_operand -= operand);
	}
}

//accessor
int calculation::passback(char & direction_hold, char & operation_hold, double & operand_hold)
{
	direction_hold = direction;
	operation_hold = operation;
	operand_hold = operand;
}

//copies information into a calculation
int calculation::create(char new_direction, char  new_operation, double new_operand)
{
	direction = new_direction;
	if(new_operation != ' ')
		operation = new_operation;
	if(new_operand != 0)
		operand = new_operand;
}

//overly-complicated chain of functions to get info from one calulation to another
int calculation::copy(const calculation &toAdd)
{
	toAdd.retrieve(*this);	
}

//calls the create function to pass copy info into the found struct and back out
int calculation::retrieve(calculation &found) const
{
	found.create(direction, operation, operand);
}

//compares the values passed with those in the object
//returns number of matching pairs of data
int calculation::compare(char c_operation, double c_operand)
{
	int count = 0;

	if(operation == c_operation)
		++count;
	if(operand == c_operand)
		++count;

	return count;
}

int calculation::display()
{
	if(direction == 'U')
		cout << "undo:";
	cout << " " << operation << " " << operand;
}

//queue functions
queue::queue()
{
	rear = NULL;
}

queue::~queue()
{
	if(rear)
	{
		node * current = rear->next;
		node * previous = rear->next;
		rear->next = NULL;
		rear = NULL;
		while(current)
		{
			current = current->next;
			delete previous;
			previous = current;
		}
	}
}

//adds a new node to the rear of the list, and copies in information from toAdd
int queue::enqueue(const calculation toAdd)
{
	if(!rear)
	{
		rear = new node;
		rear->next = rear;
	} else {
		node * temp = rear->next;
		rear->next = new node;
		rear = rear->next;
		rear->next = temp;
	}

	rear->calc.copy(toAdd);

	return 1;
}

//removes node from the front of the list
int queue::dequeue(const calculation &toDo)
{
	if(!rear)
		return 0;

	node * temp = rear->next;
	rear->next = temp->next;
	if(rear = temp)
		rear = NULL;
	delete temp;

	return 1;
}

//traverses the queue, displaying each entry
int queue::displayall()
{
	node * temp = rear->next;

	if(!rear)
		return 0;

	cout << "\nCommand history: ";

	do {
		cout << endl;
		temp->calc.display();
		temp = temp->next;
	} while (temp != rear->next);

	return 1;
}

//stack functions
stack::stack(void)
{
	head = NULL;
}

stack::~stack(void)
{
	if(head)
	{
		node * previous = head;
		while(head)
		{
			head = head->next;
			delete previous;
			previous = head;
		}
	}
}

//adds node to the top of the stack, copies info in toAdd
int stack::push(const calculation toAdd)
{
	node * temp = new node;
	temp->next = head;
	head = temp;

	head->calc.copy(toAdd);

	return 1;
}

//removes top item from stack
int stack::pop(void)
{
	if(!head)
		return 0;

	node * temp = head->next;
	delete head;
	head = temp;

	return 0;    
}

//returns data from the top item in the stack
int stack::peek(calculation &toShow) const
{
	if(!head)
		return 0;

	if(!head->calc.retrieve(toShow))
		return 0;

	return 1;	    
}

//wrapper function for function below
node * stack::flip()
{
	(this->flip(head))->next = NULL;
	return fhead;
}

//inverts the list, returning the pointer to the previous node
node * stack::flip(node * head)
{
	if(!head)
	{
		fhead = new node;
		return fhead;
	}
	
	//cout << "\ntest: recursion call";
	node * temp = flip(head->next);
	temp->calc.copy(head->calc);
	temp->next = new node;
	return temp->next;
}


