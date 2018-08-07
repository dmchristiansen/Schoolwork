//Daniel Christiansen
//CS 162
//Program 4

/*
Algorithm:

begin program

display welcome message

do{
	display menu, return choice
		if choice is add:
			input required info
			input optional info
			create new array
			copy old array over
			add new element
		if choice is rate
			loop through array of elements
				if optional info is missing
					display filled in information
					input and store blank elements
		if chouce is display
			loop through array of elements
				display element
while (choice is not exit)

delete array of elements

end program

*/

#include "Weather.h"
using namespace std;

void Welcome()
{
	for (int j = 0; j < 75; ++j)
		cout << "\n";
	cout << "\nWelcome to the forecast aggregator."
		<< "\nYou have the option to store and rate daily forecasts.";
}

char  Menu()
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

Weather::Weather() //constructor
{
	forecast = NULL;
	temp = NULL;
	count = 0;
}

Weather::~Weather()
{
	if(forecast)
	{
		delete [] forecast;
		forecast = NULL;
	}
}

void Weather::Add(Forecast & toAdd)
{
	temp = forecast;  //temp holds onto the old array
	forecast = new Forecast[count + 1]; //forecast creates an array larger by one
	if(temp) //make sure the old list isn't empty...
	{
		for(i = 0; i < count; ++i) //copy temp into the new array
		{
			forecast[i] = temp[i];
		}
	}
	forecast[count] = toAdd; //adds new element to array
	delete [] temp;
	temp = NULL;
	++count;
}

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

void Weather::RateList()
{
	char source[SIZE] = {'\0'};
	char rating[SIZE] = {'\0'};

	whole = false;

	for (i = 0; i < count; ++i)
	{
		if ((forecast[i].source[0] == '\0') || (forecast[i].rating[0] == '\0'))
		{
			Display();
			Rate(source, rating);
			strcpy(forecast[i].source, source);
			strcpy(forecast[i].rating, rating);
		}
	}
}

void Weather::DisplayList()
{
	whole = true;

	cout << "\n\nThere ";
	if(count == 1) cout << "is ";
	else cout << "are ";
	cout << count << " forecast";
	if(count != 1) cout << "s";
	cout << " to display.";

	for (i = 0; i < count; ++i)
		Display();
}

void Weather::Display()
{
	cout << "\n\nDaily High: " << forecast[i].high
		<< "\nDaily Low: " << forecast[i].low
		<< "\nChance of precipitation: " << forecast[i].prec
		<< "\nOther information: " << forecast[i].info;
	if(whole)
		cout << "\nSource of forecast: " << forecast[i].source
		<< "\nForecast's rating: " << forecast[i].rating;
}

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
	} while(choice != 'X');


	return 0;
}
