/*
Daniel Christiansen
CS 163
Program5
*/

//main.cpp
//this program implements a graph data structure to simulate rides ar Disney Land and the paths between them.
//it loads the information from a file, displays a list of rides, a list of adjacencies,
//and finds a path between rides

#include "graph.h"

void Welcome();
char Menu();
int DisplayRides(graph & rides);
int DisplayPaths(graph & rides);
int FindRoute(graph & rides);

int main()
{
	graph rides;
	char choice;

	//loads from file
	if(!rides.Load())
	{
		cout << "\nError loading ride information from file.";
		return 0;
	}

	Welcome();

	//main loop, displaying meny and getting input from user
	do {
		choice = Menu();
		switch (choice)
		{	
			case 'D':
				DisplayRides(rides);
				break;
			case 'P':
				DisplayPaths(rides);
				break;
			case 'R':
				FindRoute(rides);
				break;
		}
	} while (choice != 'X');
	return 0;
}

//displays welcome message
void Welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << "\n";
	cout << "\nThis program stores and displays information about rides at Disney Land.";
}

//displays menu, gets and returns option selected by user
char Menu()
{
	char choice;

	cout << "\n\nPlease choose from one of the following:"
		<< "\n(D) Display all rides."
		<< "\n(P) Display all paths for a ride."
		<< "\n(R) Find a route between two rides."
		<< "\n(X) Exit program."
		<< "\n: ";
	cin >> choice;
	cin.ignore(100, '\n');

	return toupper(choice);
}

//interface function for displaying the complete list of rides
int DisplayRides(graph & rides)
{
	cout << "\nThe complete list of rides is as follows:\n";
	if(!rides.DisplayRides())
	{
		cout << "\nThere was an error displaying the list.";
		return 0;
	}

	return 1;
}

//interface function for displaying a list of adjacent rides
int DisplayPaths(graph & rides)
{
	int index;

	cout << "\nPlease enter a ride number to display the rides it is adjacent to: ";
	cin >> index;
	cin.ignore(100, '\n');

	if(!rides.DisplayPaths(index - 1))
	{
		cout << "\nThere was an error displaying the list.";
		return 0;
	}

	return 1;
}

//interface function for finding a path from one ride to the next
int FindRoute(graph & rides)
{
	int from, to;

	cout << "\nPlease enter the ride number that you are starting at: ";
	cin >> from;
	cin.ignore(100, '\n');
	cout << "\nPlease enter the ride number that you would like to go to: ";
	cin >> to;
	cin.ignore(100, '\n');
	
	if(!rides.FindRoute(from - 1, to - 1))
	{
		cout << "\nThere was a problem finding a route.";
		return 0;
	}

	return 1;
}

