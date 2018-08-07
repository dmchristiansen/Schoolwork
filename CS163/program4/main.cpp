/*
	Daniel Christiansen
	CS163
	Program 4
*/

//main.cpp
//This program is intended to keep track of Oscar nominees and various pieces of information
//about their nomination.  You can add or remove nominees, as well as search the list.

#include "BST.h"

void Welcome();
char Menu();
int Add(BST & BestActor);
int Remove(BST & BestActor);
int Vote(BST & BestActor);
int Search(BST & BestActor);
int Display(BST & BestActor);

int main()
{
	BST BestActor;
	char choice;

	Welcome();	

	do{
		choice = Menu();
		switch (choice) {	
			case 'A':
				Add(BestActor);
				break;
			case 'R':
				Remove(BestActor);
				break;
			case 'V':
				Vote(BestActor);
				break;
			case 'S':
				Search(BestActor);
				break;
			case 'D':
				Display(BestActor);
				break;
		}
	} while(choice != 'X');
	return 0;
}

//clears screen and prints a welcome message
void Welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << "\n";
	cout << "This is a program that tracks Oscar nominations.";
}

//prints menu and gets choice from user
char Menu()
{
	char choice;
	cout << "\n\nPlease choose from one of the following: "
			<< "\n(A) Add a nominee"
			<< "\n(R) Remove a nominee"
			<< "\n(V) Vote for a nominee"
			<< "\n(S) Search for a nominee"
			<< "\n(D) Display all nominees"
			<< "\n(X) Exit program"
			<< "\n: ";
	cin >> choice;
	cin.ignore(100, '\n');
	return toupper(choice);
}

//gets information to be added, passes information to BST::Insert
int Add(BST & BestActor)
{
	char name[100], movie[100];
	nominee toAdd;

	cout << "\nPlease provide the following information";
	cout << "\nName: ";
	cin.get(name, 100, '\n');
	cin.ignore(100, '\n');
	cout << "\nMovie: ";
	cin.get(movie, 100, '\n');
	cin.ignore(100, '\n');

//	...in case I make multiple categories.
//	cout << "\nCategory: ";
//	cin.ignore(100, '\n'); 
	
	toAdd.CreateEntry(name, movie, 0);
	if(BestActor.Insert(name, toAdd))
		return 1;

	return 0;			
}

//function for node removal
int Remove(BST & BestActor)
{
	char name[100];

	cout << "\nPlease enter the name of the nominee to be deleted: ";
	cin.get(name, 100, '\n');
	cin.ignore(100, '\n');

	if(BestActor.Remove(name))
		cout << "\nNomination removed.";
	else
		cout << "\nNomination not found.";

	return 1;
}

//function for searching and displaying for a single entry
int Search(BST & BestActor)
{
	char hold[100];
	char * name = NULL;
	char * movie = NULL;
	int votes = 0;

	//gets name to search for, copies into dynamic array
	cout << "\nPlease enter the name of the actor you wish to see: ";
	cin.get(hold, 100, '\n');
	cin.ignore(100, '\n');
	name = new char[strlen(hold)+1];
	strcpy(name, hold);

	//uses 'BST::search' to retrieve information
	if(BestActor.Search(name, movie, votes))
		cout << "\n" << name << " has " << votes << " votes for the movie " << movie << endl;
	else
		cout << "\nThere was no match for " << name << ".\n";

	//clean up	
	if(name)
	{
		delete name;
		name = NULL;
	}
	if(movie)
	{
		delete movie;
		movie = NULL;
	}	

	return 1;
}

//function for voting for a nominee
int Vote(BST & BestActor)
{
	char hold[100];
	char * name = NULL;
	char * movie = NULL;
	int votes = 0;

	//gets name to vote for, copies into dynamic array
	cout << "\nPlease enter the name of the actor you wish to vote for: ";
	cin.get(hold, 100, '\n');
	cin.ignore(100, '\n');
	name = new char[strlen(hold)+1];
	strcpy(name, hold);

	if(BestActor.Vote(name, movie, votes))
		cout << "\n" << name << " now has " << votes << " votes for the movie " << movie << ".\n";
	else
		cout << "\nThere is no nominee under that name!\n";

	if(name)
	{
		delete name;
		name = NULL;
	}
	if(movie)
	{
		delete movie;
		movie = NULL;
	}

	return 1;
}

//function for diaplaying all nominees
int Display(BST & BestActor)
{
	cout << "\nThe nominees are as follows: ";
	if(!BestActor.DisplayAll())
		cout << "\nNo nominees to display!";
	cout << "\n";
}



