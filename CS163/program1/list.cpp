//list.cpp

#include "list.h"

//hero_match class functions

hero_match::hero_match(void)
{
	head = NULL;
}

hero_match::~hero_match(void)
{

}

int hero_match::add_hero(char super_power[], const hero_entry & newHero)
{
	node * current = head;
	node * found = NULL;
	//variables to be passed by reference to retreive info
	char currPower[SIZE];
	char currUse[SIZE];
	int currNo;	

	//traverses until it finds a matching power
	if(head)
	{
		while(current->next)
		{
			(current->power)->fetch(currPower, currUse, currNo);
			if(!strcmp(currPower, super_power))
			{
				found = current;
				break;
			} else {
				current = current->next;
			}
		}
	}

	//if the power doesn't exist, this creates a new power_entry and a new node.
	if(!found)
	{
		power_entry * newPower = new power_entry;
		char newUse[SIZE];

		cout << "\n\n\'" << super_power << "\' is a new power!"
			<< "\nWhen is this power most useful? ";
		cin.get(newUse, SIZE, '\n');
		cin.ignore(100, '\n');

		newPower->add_power(super_power, newUse);
		node * temp = new node;

		temp->power = newPower;
		temp->hero = NULL;
		temp->next = NULL;
cout << "\n!";
		if(!head)
		{
cout << "\n !!";
			head  = temp;
cout << "\n!!!";
		} else {
			current->next = temp;
		}
	}
cout << "\nnode added.";

	//there will now always be a valid node for the hero to be added to at this point...
	//adds hero to appropriate power node.
	(found->power)->increment();
cout << "\nIncremented.";
	(found->power)->fetch(currPower, currUse, currNo);
	hero_entry * hTemp = found->hero;	
	found->hero = new hero_entry[currNo];
	for (int i = 0; i < currNo - 1; ++i)
	{
		(found->hero)[i].copy(hTemp[i]);
	}
	(found->hero)[currNo-1].copy(newHero);
cout << "\ncopied.";
	delete [] hTemp;	
}

int hero_match::load_heroes(char power_file_name[], char hero_file_name[])
{

}

int hero_match::remove_power(char super_power[])
{

}

int hero_match::display() //display all
{
	if(!head)
		return 0;

	node * current = head;
	char currPower[SIZE];
	char currUse[SIZE];
	int currNo;
	char currName[SIZE];
	char currDesc[SIZE];

	while(current->next)
	{
		(current->power)->fetch(currPower, currUse, currNo);
		cout << "\n\nThe power of \'" << currPower << "\' is useful for " << currUse 
			<< "\nIt is possesed by the following heroes:";
		for (int i = 0; i < currNo; ++i)
		{
			(current->hero)[i].fetch(currName, currDesc);
			cout << "\n\nName: " << currName
				<< "\nDescription: " << currDesc;
		}
	}

	return 1;
	

}

int hero_match::display(char super_power[]) //display by power
{

}

int hero_match::find(char situation[], power_entry & found_power)
{

}

