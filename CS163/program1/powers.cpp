//powers.cpp

#include "powers.h"
//#include <iostream>

using namespace std;

//power_entry class functions

power_entry::power_entry(void)
{
	power = NULL;
	use = NULL;
	noHero = 0;
}

power_entry::~power_entry(void)
{

}

//xopies power/use into newlu allocated arrays
void power_entry::add_power(char newPower[], char newUse[])
{
	power = new char[strlen(newPower)+1];
	strcpy(power, newPower);

	use = new char[strlen(newUse)+1];
	strcpy(use, newUse);
}

void power_entry::increment()
{
	++noHero;
}

//passes in a dummy struct by reference, copies private info
int power_entry::fetch(char * currPower, char * currUse, int & currNo)
{
	strcpy(currPower, power);
	strcpy(currUse, use);
	currNo = noHero;
}

//hero_entry class functions

hero_entry::hero_entry()
{
	name = NULL;
	desc = NULL;
}

hero_entry::~hero_entry()
{

}

//copies name/desc into newly allocated arrays
void hero_entry::add_hero(char newName[], char newDesc[])
{
	name = new char[strlen(newName)+1];
	strcpy(name, newName);

	desc = new char[strlen(newDesc)+1];
	strcpy(desc, newDesc);
}

void hero_entry::copy(hero_entry toCopy)
{
	name = toCopy.name;
	desc = toCopy.desc;
}

int hero_entry::fetch(char * currName, char * currDesc)
{
	strcpy(currName, name);
	strcpy(currDesc, desc);
}
