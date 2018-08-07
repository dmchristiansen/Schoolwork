//table.cpp
//public functions for 'job' and 'table' classes

#include "table.h"

//job class functions

//job constructor
job::job()
{
	name = NULL;
	location = NULL;
	title = NULL; 
	description= NULL;
	rate = NULL;
	experience = NULL;
	skills = 0;
}

//job destructor
job::~job()
{
	delete name;
	delete location;
	delete title;
	delete description;
	delete rate;
	delete [] experience;
}

//copies data passed in into a blank 'job' object
int job::create_entry(char Name[], char Location[], char Title[], char Description[],
						 char Rate[], char * Experience[], int Skills)
{
	name = new char[strlen(Name)+1];
	strcpy(name, Name);
	location = new char[strlen(Location)+1];
	strcpy(location, Location);
	title = new char[strlen(Title)+1];
	strcpy(title, Title);
	description = new char[strlen(Description)+1];
	strcpy(description, Description);
	rate = new char[strlen(Rate)+1];
	strcpy(rate, Rate);
	skills = Skills;

	experience = new char*[skills];
	for(int i = 0; i < skills; ++i)
	{	
		experience[i] = new char[strlen(Experience[i]+1)];
		strcpy(experience[i], Experience[i]);
	}

	return 1;
}

//displays the contents of a single job object to the screen
int job::display()
{
	cout << "\nCompany Name: " << name
		<< "\nCompany location: " << location
		<< "\nJob title: " << title
		<< "\nJob description: " << description
		<< "\nPay rate: " << rate;

	if(skills)
	{
		cout << "\nExperience required: "
			<< experience[0];
		for(int i = 1; i < skills; ++i)
			cout << ", " << experience[i];
		cout << endl;
	}

	cout << endl;

	return 1;
}

//takes in an array of skills and compares it to the 'job' object's array of skills
//returns 1 if any of the skills match, else returns 0
int job::match(char *compExperience[], int compSkills)
{
	for(int i = 0; i < skills; ++i)
	{
		for(int j = 0; j < compSkills; ++j)
		{
			if(!strcmp(experience[i], compExperience[j]))
			{
				return 1;
			}
		}
	}
	return 0;
}

//table class functions

//table constructor
table::table()
{
	tablesize = 5;

	list = new node*[tablesize];
	for(int i = 0; i > tablesize; ++i)
		list[i] = NULL;
}

//table destructor
table::~table()
{
	node * current;
	node * previous;
	for(int i = 0; i < tablesize; ++i)
	{
		current = list[i];
		previous = current;
		while(current)
		{
			current = current->next;
			delete previous;
			previous = current;
		}
	}
}

//takes in search parameters, searches through appropriate table element, and returns an array of
//pointers to job objects mathing search criteria
int table::retrieve(char keyValue[], char *experience[], int skills, job ** &results, int &matches)
{
	int i = 0;
	matches = 0;

	int key = hash(keyValue);
	node * current = list[key];

	//searches through a table entry, counting the number of mathces...
	while(current)
	{
		if(current->listing.match(experience, skills))
			++matches;
		current = current->next;
	}

	//allocates an array of the appropriate size...
	results = new job*[matches];
	cout << "\nMatches: " << matches;
	//searches through the table entry again,
	//assembling an array of pointers to job objects
	current = list[key];
	while(current)
	{
		if(current->listing.match(experience, skills))
		{
			results[i] = &(current->listing);
			++i;
		}
		current = current->next;
	}

	//returns 1 of there was at least one match
	if(matches)
		return 1;
	else
		return 0;
}

//displays everything in the table
int table::displayAll()
{
	node * current;

	cout << "\nA complete list of all listings: ";
	for(int i = 0; i < tablesize; ++i)
	{
		current = list[i];
		while(current)
		{
			current->listing.display();
			current = current->next;
		}
	}

	return 1;
}

//functions that adds individual items to the table.  used by 'table::load'
int table::add(char * keyVal, node * toAdd)
{
	int key = hash(keyVal);
	node * current = list[key];
	toAdd->next = current;
	list[key] = toAdd;
}

//loads table from file, constructing table
int table::load()
{
	char number[100];
	char name[100];
	char location[100];
	char title[100];
	char description[100];
	char rate[100];
	char* experience[100];
	int skills;
	node * toAdd;
	
	ifstream infile;
	infile.open("jobs.txt");
	if(!infile)
	{
		return 0;
	} else {
		infile.getline(number, 100, '\n');
		while(!infile.eof())
		{
			infile.getline(name, 100, '\n');
			infile.getline(location, 100, '\n');
			infile.getline(title, 100, '\n');
			infile.getline(description, 100, '\n');
			infile.getline(rate, 100, '\n');
			infile >> skills;
			infile.ignore(100, '\n');
			for(int i = 0; i < skills; ++i)
			{
				experience[i] = new char[100];
				infile.getline(experience[i], 100, '\n');
			}
			infile.ignore(100, '\n');
			toAdd = new node;
			toAdd->listing.create_entry
				(name, location, title, description, rate, experience, skills);
			add(title, toAdd);
			infile.getline(number, 100, '\n');
		}		
	}
}

//takes in a char array, hashes, and returns a key
int table::hash(char * keyVal)
{
	int key = 0;

	for(int i = 0; i < strlen(keyVal); ++i)
	{
		key += (keyVal[i] << 1);
	}

	key = key % tablesize;
	return key;
}
