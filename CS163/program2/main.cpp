/*
Daniel Christiansen
CS 163
Program 2
*/

//main.cpp
//super cool calculator program

#include "calc.h"

void welcome();
char menu();

int Add(stack & last, queue & history);
int Subtract(stack & last, queue & history);
int Multiply(stack & last, queue & history);
int Divide(stack & last, queue & history);
int UndoLast(stack & last, queue & history);
int UndoUntil(stack & last, queue & history);
int Calculate(stack & last, queue & history);
node * Calculate(node * head, char one, char two);
int DisplayLast(stack & last, queue & history);
int DisplayHistory(stack & last, queue & history);

int main()
{
	stack last;
	queue history;

	char choice;

	welcome();

	do {
		choice = menu();

		switch (choice) {
			case '+':
				Add(last, history);
				break;
			case '-':
				Subtract(last, history);
				break;
			case '*':
				Multiply(last, history);
				break;
			case '/':
				Divide(last, history);
				break;
			case 'U':
				UndoLast(last, history);
				break;
			case 'T':
				UndoUntil(last, history);
				break;
			case 'C':
				Calculate(last, history);
				break;
			case 'L':
				DisplayLast(last, history);
				break;
			case 'H':
				DisplayHistory(last, history);
				break;
		}
	} while (choice != 'X');

	return 0;
}

void welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << "\n";

	cout << "Welcome to your personal calculator program.\n"
		<< "\nCalculations will operate on a starting value of zero.\n";
}

//displays menu and returns user's choice
char menu()
{
	char choice;

	cout << "\nPlease chose one of the following: "
		<< "\n(+) - Add"
		<< "\n(-) - Subtract"
		<< "\n(*) - Multiply"
		<< "\n(/) - Divide"
		<< "\n(U) - Undo last x operations"
		<< "\n(T) - Undo back to a certain operation"
		<< "\n(C) - Calculate"
		<< "\n(L) - Display last command"
		<< "\n(H) - Display command history"
		<< "\n(X) - Exit"
		<< "\n : ";

	cin >> choice;
	cin.ignore(100, '\n');

	return toupper(choice);
}

//gets new operation/operand pair.  adds to stack and queue
int Add(stack & last, queue & history)
{
	double addend;
	calculation toAdd;

	//get addend
	cout << "\nPlease enter the addend: ";
	cin >> addend;
	cin.ignore(100, '\n');

	//create struct
	toAdd.create('d', '+', addend);

	//push
	last.push(toAdd);

	//enqueue
	history.enqueue(toAdd);

	//display message
	cout << "\n\n \"+" << addend << "\" added\n";
}

//get new operation/operand combo.  adds to stack and queue
int Subtract(stack & last, queue & history)
{
	double subtrahend;
	calculation toAdd;

	//get subtrahend
	cout << "\nPlease enter the subtrahend: ";
	cin >> subtrahend;
	cin.ignore(100, '\n');

	//create struct
	toAdd.create('D', '-', subtrahend);

	//push
	last.push(toAdd);
	
	//enqueue
	history.enqueue(toAdd);

	//display message
	cout << "\n\n \"-" << subtrahend << "\" added\n";
}

//get new operation/operand combo.  adds to stack and queue
int Multiply(stack & last, queue & history)
{
	double multiplier;
	calculation toAdd;

	//get multiplier
	cout << "\nPlease enter the multiplier: ";
	cin >> multiplier;
	cin.ignore(100, '\n');

	//create struct
	toAdd.create('D', '*', multiplier);

	//push
	last.push(toAdd);
	
	//enqueue
	history.enqueue(toAdd);

	//display message
	cout << "\n\n \"*" << multiplier << "\" added\n";
}

//get new operation/operand combo.  adds to stack and queue
int Divide(stack & last, queue & history)
{
	int divisor;
	calculation toAdd;

	//get divisor
	do {
		cout << "\nPlease enter the divisor: ";
		cin >> divisor;	
		cin.ignore(100, '\n');
		if(divisor == 0)
			cout << "\nYou can't divide by zero!";
	} while (divisor == 0);

	//create struct
	toAdd.create('D', '/', divisor);

	//push
	last.push(toAdd);

	//enqueue
	history.enqueue(toAdd);

	//display message
	cout << "\n\n \"/" << divisor << "\" added\n";
}

//undoes the last x operations, popping them off the stack, but adding an 'undo' entry to the queue
int UndoLast(stack & last, queue & history)
{
	int count;
	calculation toAdd;

	//get info(number of steps to undo)
	cout << "\nPlease enter the number of steps to undo: ";
	cin >> count;
	cin.ignore(100, '\n');

	for(int i = 0; i < count; ++i)
	{
		last.peek(toAdd); //grab the info about the last operation...
		last.pop(); //before popping it off the stack
		toAdd.create('U', ' ', 0); //replace do with undo
		history.enqueue(toAdd); //add undo operation to queue
		cout << "\n";
		toAdd.display();
	}
	cout << endl;
	return 1;
}

//undoes until a matching pair is found.  pops off the stack, adds an undo entry to the queue for each
int UndoUntil(stack & last, queue & history)
{
	calculation toAdd;
	char operation;
	double operand;

	//get info(operation to undo until)
	cout << "\nPlease enter the calculation to delete through."
		<< "\noperation: ";
	cin >> operation;
	cin.ignore(100, '\n');
	cout << "\noperand: ";
	cin >> operand;
	cin.ignore(100, '\n');

	cout << "\n";
	do {
		last.peek(toAdd);
		toAdd.create('U', ' ', 0);
		cout << "\n";
		toAdd.display();
		last.pop();
	} while(toAdd.compare(operation, operand) != 2);
	cout << "\n";
	return 1;
}

//calculates the operations on the stack, starting with an implicit zero
int Calculate(stack & last, queue & history)
{
	char dir, opn;
	double opd;

	//create new LLL recursively, gets new head pointer
	node * head = last.flip();

	//displays list before resolving, all in one line
	node * current = head;
	cout << "\n 0 ";
	while(current->next)
	{
		current->calc.display();
		current = current->next;
	}
	cout << " = ";

	//removes leading * and / operations
	current = head;
	while(current && (current->calc.compare('*', 0) || current->calc.compare('/', 0)))
	{
		head = current->next;
		delete current;
		current = head;
	}

	//takes two passes through to resolve calculation in correct order	
	head = Calculate(head, '*', '/');
	head = Calculate(head, '+', '-');

	head->calc.passback(dir, opn, opd);
	cout << " " << opd << endl;	
}

//passes through the LLL and resolves operations one and two
node * Calculate(node * head, char one, char two)
{
	if(!head)
		return head;
	node * current = head->next;
	node * previous = head;

	while(current->next)
	{
		if((current->calc.compare(one, 0)) || (current->calc.compare(two, 0)))
		{
			previous->calc.calculate(current->calc);
			current = current->next;
			delete previous->next;
			previous->next = current;
		} else {
			previous = current;
			current = current->next;
		}
	}

	return head;
}

int DisplayLast(stack & last, queue & history)
{
	calculation toShow;

	//peek at the stack, display result
	cout << "\nThe last command entered was ";
	last.peek(toShow);
	toShow.display();
	cout << "\n";
}

int DisplayHistory(stack & last, queue & history)
{
	//traverse through queue, displaying
	history.displayall();
}





