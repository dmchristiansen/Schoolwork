/*
Daniel Christiansen
CS202
Program 2
*/

//main.cpp

//This is a program to gather information about course requirements for entry to a degree program.

#include "tree.h"

void Welcome();
char Menu();
bool Again();

void AddCourses(Tree &);
void SetReqs(Tree &);
void DisplayGPA(Tree &);
void DisplayCourses(Tree &);

int main()
{
	char choice;
	Tree ReqList;

	Welcome();

	do {
		choice = Menu();
		switch (choice) {
		case 'C':
			AddCourses(ReqList);
			break;
		case 'R':
			SetReqs(ReqList);
			break;
		case 'D':
			DisplayCourses(ReqList);
			break;
		case 'G':
			DisplayGPA(ReqList);
			break;
		default:
			break;
		}
	} while (choice != 'X');
	
	return 0;
}

void Welcome()
{
	cout << "\nThis program will help you keep track of degree requirements.";
}

char Menu()
{ 

	char choice;
	
	cout << "\n\nPlease chose one of the following:"
		<< "\n[C] Enter required courses(s)."
		<< "\n[R] Enter credit requirements."
		<< "\n[D] Display current requirement list."
		<< "\n[G] Display GPA."
		<< "\n[X] Exit.";

	do {
		cout << "\n(C/R/D/G/X) : ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);
	} while (!(choice == 'C' || choice == 'R' || choice == 'D' || choice == 'G' || choice == 'X'));

	return choice;
}

bool Again()
{
	char choice;
	cout << "\nWould you like to enter another course? (Y/N) ";
	cin >> choice;
	cin.ignore(100, '\n');
	choice = toupper(choice);
	if(choice == 'Y')
		return true;
	if(choice == 'N')
		return false;
	else
		return Again();
}

void AddCourses(Tree & ReqsList)
{
	char required, core, completed;
	char name[100], subject[100];
	int CRN, credits, quarter;
	float earned_credits;
	Course * tempCourse, * newCourse;

	//loop that reads in course info and adds to the tree every time
	do {
		cout << "\nCourse name: ";
		cin.get(name, 100, '\n');
		cin.ignore(100, '\n');

		cout << "\nCourse code (CS202, MTH251, etc): ";
		cin.get(subject, 100, '\n');
		cin.ignore(100, '\n');

		cout << "\nCRN: ";
		cin >> CRN;
		cin.ignore(100, '\n');

		cout << "\nCredits: ";
		cin >> credits;
		cin.ignore(100, '\n');		

		cout << "\nHas this course been completed? (Y/N) ";
		cin >> completed;
		cin.ignore(100, '\n');
		completed = toupper(completed);
		if(completed == 'Y')
		{
			cout << "\nCredits earned: ";
			cin >> earned_credits;
			cin.ignore(100, '\n');
			
			cout << "\nWhat year/quarter was this class taken? (YYQ) ";
			cin >> quarter;
			cin.ignore(100, '\n');
		} else {
			earned_credits = 0;
			quarter = 0;
		}

		cout << "\nIs this a required course? (Y/N) ";
		cin >> required;
		cin.ignore(100, '\n');
		required = toupper(required);
		if(required == 'Y')
		{
			cout << "\nIs this a core class? (Y/N) ";
			cin >> core;
			cin.ignore(100, '\n');
			core = toupper(core);
		} else {
			core == 'N';
		}

		//creates the appropriate class object, and passes it into the insert function
		tempCourse = new Course(name, subject, CRN, credits, (completed == 'Y'), earned_credits);
		if(required == 'Y')
		{
			if(core == 'Y')
			{
				newCourse = new Core(*tempCourse);
			} else {
				newCourse = new NonCore(*tempCourse);
			}
		} else {
			newCourse = new NonRequired(*tempCourse);
		}
		delete tempCourse;
		tempCourse = NULL;
		ReqsList.Insert(newCourse, quarter);
	} while (Again());
}

void SetReqs(Tree & ReqsList)
{
	float overall, core;
	cout << "\nPlease enter the minimum overall GPA required: ";
	cin >> overall;
	cin.ignore(100, '\n');
	cout << "\nPlease enter the minimum GPA for core classes: ";
	cin >> core;
	cin.ignore(100, '\n');
	ReqsList.SetReqs(overall, core);
}

void DisplayGPA(Tree & ReqsList)
{
	ReqsList.DisplayGPA();
}

void DisplayCourses(Tree & ReqsList)
{
	cout << "\n\nComplete course listing, by term.";
	ReqsList.DisplayAll();
}

