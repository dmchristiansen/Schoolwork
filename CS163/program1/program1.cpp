//Daniel Christiansen
//CS 163
//1/21/15

#include "list.h"

//main functions
void welcome();
char menu();


void add_hero(hero_match &);
void display(hero_match &);
void displayPower(hero_match &);
void remove(hero_match &);
void find(hero_match &);

int main() 
{
	hero_match heroList;

	char choice;


	welcome();
	do
	{
		choice = menu();
		switch (choice) {
		case 'A':
			add_hero(heroList);
			break;
		case 'D':
			display(heroList);
			break;
		case 'P':
			displayPower(heroList);
			break;
		case 'R':
			remove(heroList);
			break;
		case 'F':
			find(heroList);
			break;
		
		default:
			break;
		}		

	} while(choice != 'X');

	return 0;

}

void welcome()
{
	for(int i = 0; i < 50; ++i)
	{
		cout << "\n";
	}
	cout << "Welcome to your super-hero planner.\n"
		<< "We are here to help with all your super-hero related needs.\n";
}

char menu()
{
	char choice;

	cout << "\n\nPlease choose from one of the following options:\n"
		<< "(A) Add super hero to your list\n"
		<< "(D) Display all super heroes on your list.\n"
		<< "(P) Display all super heroes with a particular power.\n"
		<< "(R) Remove all heroes with a particular power from the list.\n"
		<< "(F) Find the type of powers that would be best suited to a situation.\n"
		<< "(X) Exit program.\n"
		<< ": ";

	cin >> choice;
	cin.ignore(100, '\n');
	choice = toupper(choice);
	return choice;
}

void add_hero(hero_match & heroList)
{
	char name[SIZE];
	char power[SIZE];
	char desc[SIZE];	
	hero_entry toAdd;

	cout << "\n\nPlease enter the name of the hero to be added: ";
	cin.get(name, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "\nPlease enter the super hero's power: ";
	cin.get(power, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "\nPlease enter a description of the hero: ";
	cin.get(desc, SIZE, '\n');
	cin.ignore(100, '\n');

	toAdd.add_hero(name, desc);

	heroList.add_hero(power, toAdd);
}


void display(hero_match & heroList)
{
	if(!heroList.display())
		cout << "\nNo heroes to display!\n";
}

void displayPower(hero_match & heroList)
{

}

void remove(hero_match & heroList)
{

}

void find(hero_match & heroList)
{

}


