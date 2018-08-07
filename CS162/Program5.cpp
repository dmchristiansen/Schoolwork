//Daniel Christiansen
//CS 162
//Program 5

/*
Algorithm:

begin program

display welcome message

do{
	display menu, return choice
		if choice is add:
			input required info
			input optional info
			create new node
			traverse to end of list
			append new node
		if choice is rate
			traverse through list
				if optional info is missing
					display filled in information
					input and store blank elements
		if chouce is display
			reaverse through list
				display each element
while (choice is not exit)

delete list

end program

 */

#include "Weather.h"

//clears screen and displays a welcome message
void Welcome()
{
	for (int j = 0; j < 75; ++j)
		cout << "\n";

	cout << "\nWelcome to the forecast aggregator."
		<< "\nYou have the option to store and rate daily forecasts.";
}

//displays menu, returns choice as a character
char Menu()
{
	char choice = ' ';

	cout << "\n\nPlease choose one of the following:"
		<< "\nAdd a new forecast (A)"
		<< "\nRate forecasts (R)"
		<< "\nDisplay all forecasts (D)"
		<< "\nExit Program (X)";
	do {
		cout << "\nPlease enter your choice (A/R/D/X): ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);
	} while(!(choice == 'A' || choice == 'R' || choice == 'D' || choice == 'X'));
	return choice;
}

//destructor
Weather::~Weather()
{
	Forecast * current = head;
	Forecast * previous = head;

	if (!head) //if the list is already empty...
		return;

	//traverses the list, deleting behind it
	while (current)
	{
		current = current->next;
		cout << "\nDeleting: " << previous->source;
		delete previous;
		previous = current;
	}
	head = NULL;
}

//constructor
Weather::Weather()
{
	head = NULL;
	count = 0;
}

//displays a single element
void Weather::Display(Forecast forecast)
{
	cout << "\n\nDaily high: " << forecast.high
		<< "\nDaily low: " << forecast.low
		<< "\nChance of precipitation: " << forecast.prec
		<< "\nOther information: " << forecast.info;
	//this is so this function can be reused for the 'RateList()' function
	if (whole)
		cout << "\nSource of forecast: " << forecast.source
			<< "\nForecast's rating: " << forecast.rating;
}

//traverses the list, passing each element to the 'Display()' function
void Weather::DisplayList()
{
	Forecast * current = head;
	whole = true; //tells the 'Display()' function to display 'source' and 'rating'
	cout << "\nThere are " << count << " entries to display.";

	while (current)
	{
		Display(*current);
		current = current->next;
	}
}

//Recieves input from 'Input()' and populates a new node
void Weather::Add(Forecast & toAdd)
{
	Forecast * current = head;
	Forecast * temp = new Forecast;

	//assigns values to new node;
	temp->high = toAdd.high;
	temp->low = toAdd.low;
	temp->prec = toAdd.prec;
	strcpy(temp->info, toAdd.info);
	strcpy(temp->source, toAdd.source);
	strcpy(temp->rating, toAdd.rating);
	temp->next = NULL;

	//if the list is empty
	if (!head)
	{
		head = temp;
		++count;
		return;
	}

	//traverses the list
	while (current->next)
		current = current->next;

	//appends the new node to the end of the list
	current->next = temp;

	//increments the counter variable
	++count;
}

//recieves iser input for the optional 'source' and 'rating' fields
void Weather::Rate(char source[], char rating[])
{
	cout << "\nSouce of forecast (leave blank to skip) : ";
	cin.get(source, SIZE, '\n');
	if(cin.fail()) cin.clear();
	cin.ignore(100, '\n');
	cout << "\nRating (leave blank to skip) : ";
	cin.get(rating, SIZE, '\n');
	if(cin.fail()) cin.clear();
	cin.ignore(100, '\n');

	source[0] = toupper(source[0]);
}

//traverses list, displaying each element
void Weather::RateList()
{
	Forecast * current = head;
	char source[SIZE] = {'\0'};
	char rating[SIZE] = {'\0'};

	whole = false; //tells 'Display()' to only display part of an entry

	while (current)
	{
		if ((current->source[0] == '\0') || (current->rating[0] == '\0'))
		{
			Display(*current); //displays partial entry
			Rate(source, rating); //gets user input
			strcpy(current->source, source); //completes entry w/
			strcpy(current->rating, rating); //user input
		}
		current = current->next; //traverses
	}
}

//Recieves user input and passes it to 'Add()'
void Weather::Input()
{
	Forecast toAdd;
	toAdd.source[0] = '\0';
	toAdd.rating[0] = '\0';

	cout << "\nPlease enter the following information about the forecast:";
	cout << "\nDaily high (xx.x): ";
	cin >> toAdd.high;
	cin.ignore(100, '\n');
	cout << "\nDaily low (xx.x): ";
	cin >> toAdd.low;
	cin.ignore(100, '\n');
	cout << "\nChance of precipitation (xx.x): ";
	cin >> toAdd.prec;
	cin.ignore(100, '\n');
	cout << "\nOther information: ";
	cin.get(toAdd.info, SIZE, '\n');
	cin.ignore(100, '\n');

	Rate(toAdd.source, toAdd.rating);
	Add(toAdd);
}

int main()
{
	Weather list;
	char choice;

	Welcome();

	do {
		choice = Menu();
		switch (choice) {
		case 'A':
			list.Input();
			break;
		case 'R':
			list.RateList();
			break;
		case 'D':
			list.DisplayList();
			break;
		}
	} while (choice != 'X');

	return 0;
}


