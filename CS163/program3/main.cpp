/*
	Daniel Christiansen
	CS 163
	Program 3
*/

//This program implements a hash table data structure to store job postings.
//It loads data from a 'jobs.txt' file, and allows a user to search through them based
//on job title, and experience required.

//main.cpp

#include "table.h"

void Welcome();
char Menu();
int Search(table listings);
int DisplayAll(table & listings);

int main()
{
	table listings;
	char choice = ' ';

	Welcome();
	
	//opening file and populating the table
	if(!listings.load())
	{
		cout << "\nUnable to lead job listings!";
		return 0;
	}
	
	//menu loop
	do {
		choice = Menu();
		switch (choice) {
			case 'S':
				Search(listings);
				break;
			case 'D':
				DisplayAll(listings);
				break;
			default:
				break;
		}		
	} while (choice != 'X');


	return 0;
}

void Welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << "\n";

	cout << "\nWelcome to your job search application"
		<< "\n";

}

char Menu()
{
	char choice = ' ';

	cout << "\nPlease choose one of the following:"
		<< "\n(S) Search listings"
		<< "\n(D) Display all"
		<< "\n(X) Exit program"
		<< "\n: ";

	cin >> choice;
	cin.ignore(100, '\n');

	return toupper(choice);
}

//
int Search(table listings)
{
	char title[100], hold[100];
	char *experience[100];
	int matches, skills = 0;
	char choice;
	job ** results;

	cout << "\nPlease enter the job title you would like to search for: ";
	cin.get(title, 100, '\n');
	cin.ignore(100, '\n');
	cout << "\nPlease enter skills one at a time to search for\n";
	do {
		cout << "Enter a skill: ";
		cin.get(hold, 100, '\n');
		experience[skills] = new char[strlen(hold)+1];
		strcpy(experience[skills], hold);
		cin.ignore(100, '\n');
		++skills;
		cout << "\nWould you like to enter another skill? (Y/N) :";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);		
	} while (choice == 'Y');

	//passes in the search parameters and gets a pointer to an array of results
	if(listings.retrieve(title, experience, skills, results, matches))
	{
		cout << "\nThe following items matched your search parameters:\n";
		for(int i = 0; i < matches; ++i)
		{
			results[i]->display();	
		}
	} else {
		cout << "\nNo matches found.\n";
	}
}

int DisplayAll(table & listings)
{
	listings.displayAll();
}


