//Daniel Christiansen
//CS 162
//Program 2
//10/28/14

/*
Algorithm:
Welcome user to program
Ask for date
do{
	would you like to enter a phrase?
	enter phrase
	sanitize phrase
} while (count < 4 & continue)

do{
	would you like to output a phrase/what order?
	output
} while (continue)

*/

#include <iostream>
#include <cstring>

using namespace std;

const int PHRASE = 132;//130 for the phrase, a period, and a terminating character

void welcome(); //welcomes users to the program
void create_date(char[]);
void read_phrase(char [], int & i, bool &);
void capitalize(char[]);
void period(char[]);
void clean_space(char[]);
void disp_order(char[]);
bool display(char[], char[], char[], char[], char[], char[], int);
bool check_len();

int main()
{
	char p1[PHRASE] = {}, p2[PHRASE] = {}, p3[PHRASE] = {}, p4[PHRASE] = {}; //Arrays to hold phrases
	char date[9] = "00/00/00";
	char order[6]; //Array to gold order of phrase output
	bool cont = true;
	bool again = true;
	int i = 0;

	welcome();
	create_date(date);

	//Calling the function four times turned out to be easier
	//than passing a 2D char array.
	read_phrase(p1, i, cont);
	read_phrase(p2, i, cont);
	read_phrase(p3, i, cont);
	read_phrase(p4, i, cont);

	//Loop allowing the user to output their phrases
	do {
		disp_order(order);
		again = display(order, date, p1, p2, p3, p4, i);
	} while (again);

	return 0;
}

void welcome()
{
	for (int j = 1; j < 70; ++j)
		cout << "\n";
	cout << "\nWelcome to Laz-E-Phrase, the phrase saver!\n"
		<< "\nYou may enter a date and up to four phrases to"
		<< " be read out on command.\n\n";
}

void create_date(char date[])
{
	char enter;
	cout << "\nWould you like to enter a date to be stored? (Y/N)";
	cin >> enter;
	cin.ignore(100, '\n');
	if (toupper(enter) == 'Y')
	{
		cout << "\nPlease enter a date to be stored (MM/DD/YY): ";
		cin.get(date, 8, '\n');
		cin.ignore(100, '\n');
	}
}

//Function to read in a phrase
void read_phrase(char phrase[], int & i, bool & cont)
{
	char enter;
	bool redo = false;

	if (cont)
	{
		cout << "\nWould you like to enter a";
		if (i > 0)
			cout << "nother";
		cout << " phrase? (Y/N) ";
		cin >> enter;
		cin.ignore(100, '\n');

		if (toupper(enter) == 'Y')
		{
			do {
				cout << "\nPlease enter a phrase of no more than " << PHRASE - 2 << " characters:\n";
				cin.get(phrase, PHRASE, '\n');
				redo = check_len();
				cin.ignore(100 , '\n');
			} while (redo);
			capitalize(phrase);
			period(phrase);
			clean_space(phrase);
			cout << "\n\nPhrase #" << i + 1 << " reads:\n\n" << phrase << "\n";
			++i;
		}
		if (toupper(enter) == 'N')
			cont = false;
	}
}

bool check_len()
{
	if (cin.peek() == '\n')
		return false;
	else
		return true;
}

void capitalize(char phrase[])
{
	phrase[0] = toupper(phrase[0]);
}

void period(char phrase[])
{
	if (phrase[strlen(phrase) - 1] != '.')
	{
		strncat(phrase, ".", 1);
	}
}

void clean_space(char phrase[])
{
	int j = 0;
	char hold[PHRASE]; //Array to hold an array being worked on
	strcpy(hold, "");
	for (int i = 0; i < strlen(phrase); ++i)
	{
		if (!(phrase[i] == ' ' && phrase[i+1] == ' '))
		{
			hold[j] = phrase[i];
			++j;
		}
	}
	hold[j] = '\0';
	strcpy(phrase, hold);
}

void disp_order(char order[])
{
	cout << "\n\nPlease enter the order in which you would "
		<< "like your phrases to be read out.\n"
		<< "(\"D1234\" prints out the date, then the phrases 1 - 4)"
		<< "Enter order: ";
	cin >> order;
}

bool display(char order[], char date[], char p1[], char p2[], char p3[], char p4[], int count)
{
	char ask;

	cout << endl;
	for (int i = 0; i < strlen(order); ++i)
	{
		switch (order[i]) {
		case 'D':
		case 'd':
			cout << "\n\n" << date;
			break;
		case '1':
			if (count > 0)
				cout << "\n\n" << p1;
			break;
		case '2':
			if (count > 1)
				cout << "\n\n" << p2;
			break;
		case '3':
			if (count > 2)
				cout << "\n\n" << p3;
			break;
		case '4':
			if (count > 3)
				cout << "\n\n" << p4;
			break;
		default:
			break;
		}
	}
	cout << "\n\nWould you like to display your phrases again? (Y/N): ";
	cin >> ask;
	if (toupper(ask) == 'Y')
		return true;
	else
		return false;
}
