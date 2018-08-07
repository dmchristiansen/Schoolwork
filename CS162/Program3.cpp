//Daniel Christiansen
//CS 162
//Program 3

/*
Algorithm:

begin

	Welcome message
	Load data from external file
	do {
		display menu/read in choice, do one of the following:
			Input new record element;
			Display function:
				Display menu/read choice:
					DisplayByActivity
					DisplayByCourse
					DisplayAll
			Delete an element
		}
	} while (option isn't 'exit');

	Write data to file

end
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int SIZE = 120;

struct dateType {
	int month;
	int day;
	int year;
};

struct reminder {
	char activity[SIZE];
	char course[SIZE];
	char priority[SIZE];
	char info[SIZE];
	dateType date;
};

struct file {
	char fileName[SIZE];
};


//Prototypes for file I/O
void ReadFile(reminder schedule[], int & count);
void WriteFile(reminder schedule[], int & count);

//Large blocks of text
void Welcome();
char Menu();

//Display functions
void ReadDisplay(reminder schedule[], int & count);
void Display(reminder & schedule);
void DisplayAll(reminder schedule[], int & count);
void DisplayActivity(reminder schedule[], int & count);
void DisplayCourse(reminder schedule[], int & count);

//Delete functions
void ReadDelete(reminder schedule[], int & count);
void Delete(reminder schedule[], int & count, int i);

//User-input functions
void ReadReminder(reminder schedule[], int & count);
void ReadActivity(reminder schedule[], int & count);
void ReadCourse(reminder schedule[], int & count);
void ReadDate(reminder schedule[], int & count);
void ReadPriority(reminder schedule[], int & count);
void ReadInfo(reminder schedule[], int & count);

int main()
{
	reminder schedule[20];
	int count = 0; //Counter for # of reminders
	char opt = ' ';

	Welcome(); //Welcome message
	ReadFile(schedule, count); //Load previous data;
	do {
		opt = Menu();//Display menu, return choice
		switch (opt) {
			case 'N':
				ReadReminder(schedule, count);
				break;
			case 'D':
				ReadDisplay(schedule, count);
				break;
			case 'E':
				ReadDelete(schedule, count);
				break;
		}
	} while (opt != 'X');

	WriteFile(schedule, count); //Data is saved upon exit

	return 0;
}

//Display menu function
void ReadDisplay(reminder schedule[], int & count)
{
	char choice = ' ';
	cout << endl
		<< "\nPlease choose one of the following:"
		<< "\nDisplay all (A)"
		<< "\nDisplay by activity name (N)"
		<< "\nDisplay by course name (C)"
		<< "\nPlease choose (A/N/C): ";
	cin >> choice;
	cin.ignore(100, '\n');
	choice = toupper(choice);

	switch (choice) {
		case 'A':
			DisplayAll(schedule, count);
			break;
		case 'N':
			DisplayActivity(schedule, count);
			break;
		case 'E':
			DisplayCourse(schedule, count);
			break;
	}
}

//Display all
void DisplayAll(reminder schedule[], int & count)
{
	cout << "\n\nYour list of reminders is as follows:"
		<< "\n======================================";
	for (int i = 0; i < count; ++i)
		Display(schedule[i]);
	cout << "\n\n======================================\n";
}

//Display by activity
void DisplayActivity(reminder schedule[], int & count)
{
	char act[SIZE];

	cout << "\n\nPlease enter the acticity you wish to display: ";
	cin.get(act, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "\n\nDisplaying all reminders for '" << act << "'";

	for (int i = 0; i < count; ++i)
	{
		if (strcmp(schedule[i].activity, act) ==  0)
			Display(schedule[i]);
	}
}

//Display by course
void DisplayCourse(reminder schedule[], int & count)
{
	char crs[SIZE];

	cout << "\n\nPlease enter the acticity you wish to display: ";
	cin.get(crs, SIZE, '\n');
	cin.ignore(100, '\n');

	cout << "\n\nDisplaying all reminders for '" << crs << "'";

	for (int i = 0; i < count; ++i)
	{
		if (strcmp(schedule[i].course, crs) ==  0)
			Display(schedule[i]);
	}
}

//Function that does the actual displaying
void Display(reminder & schedule)
{
	cout << "\n\nActivity: " << schedule.activity;
	cout << "\nCourse: " << schedule.course;
	cout << "\nDue Date: " << schedule.date.month << "/"
		<< schedule.date.day << "/" << schedule.date.year;
	cout << "\nPriority: " << schedule.priority;
	cout << "\nDescription: " << schedule.info;

}

//Delete menu function
void ReadDelete(reminder schedule[], int & count)
{
	char name[SIZE], in;

	cout << "\n\nPlease enter the activity you would like to delete: ";
	cin.get(name, SIZE, '\n');
	cin.ignore(100, '\n');

	for (int i = 0; i < count; ++i)
	{
		if (strcmp(schedule[i].activity, name) == 0)
		{
			cout << "\nWould you like to delete the following activity:\n\n";
			Display(schedule[i]);
			cout << "Enter (Y/N): ";
			cin >> in;
			if (toupper(in) == 'Y')
			{
				Delete(schedule, count, i);
			}
		}
	}
}

//Function for deleting
void Delete(reminder schedule[], int & count, int i)
{
	for(i; i < count - 1; ++i)
	{
		strcpy(schedule[i].activity, schedule[i+1].activity);
		strcpy(schedule[i].course, schedule[i+1].course);
		strcpy(schedule[i].priority, schedule[i+1].priority);
		strcpy(schedule[i].info, schedule[i+1].info);
		schedule[i].date.month = schedule[i+1].date.month;
		schedule[i].date.day = schedule[i+1].date.day;
		schedule[i].date.year = schedule[i+1].date.year;
	}
	--count;
}

//Input function
void ReadReminder(reminder schedule[], int & count)
{
	char again;
	do {
		ReadActivity(schedule, count);
		ReadCourse(schedule, count);
		ReadDate(schedule, count);
		ReadPriority(schedule, count);
		ReadInfo(schedule, count);
		++count;
		cout << "\nWould you like to enter another reminder? (Y/N): ";
		cin >> again;
		cin.ignore(100, '\n');
		again = toupper(again);
	} while (again == 'Y');
}

//Main menu
char Menu()
{
	char opt = ' ';

	cout << "\n\nWhat would you like to do?"
		<< "\nPlease choose one of the following:"
		<< "\nRead in a new reminder (N)"
		<< "\nDisplay reminders (D)"
		<< "\nDelete reminder (E)"
		<< "\nExit program (X)";
	do {
		cout << "\n\nEnter choice (N/D/E/X): ";
		cin >> opt;
		cin.ignore(100, '\n');
		opt = toupper(opt);
	} while (!(opt == 'N' || opt == 'D' || opt == 'E' || opt == 'X'));
	return opt;
}

//Loading data from file...
void ReadFile(reminder schedule[], int & count)
{
	ifstream infile;

	infile.open("list.txt");
	cout << "\nFile open\n";

	if(infile)
	{
		infile.get(schedule[count].activity, SIZE, '\t');
		while(!infile.eof() && count < 20)
		{
			infile.ignore(100, '\t');
			infile.get(schedule[count].course, SIZE, '\t');
			infile.ignore(100, '\t');
			infile.get(schedule[count].priority, SIZE, '\t');
			infile.ignore(100, '\t');
			infile.get(schedule[count].info, SIZE, '\t');
			infile.ignore(100, '\t');
			infile >> schedule[count].date.month;
			infile.ignore(100, '\t');
			infile >> schedule[count].date.day;
			infile.ignore(100, '\t');
			infile >> schedule[count].date.year;
			infile.ignore(100, '\n');
			++count;
			infile.get(schedule[count].activity, SIZE, '\t');
		}
	}

	infile.close();

	cout << "\n" << count << " tasks read in.";
}

//Writing data to file...
void WriteFile(reminder schedule[], int & count)
{
	ofstream outfile;

	outfile.open("list.txt");

	cout << count;

	for(int i = 0; i < count; ++i)
	{
		outfile << schedule[i].activity << "\t"
			<< schedule[i].course << "\t"
			<< schedule[i].priority << "\t"
			<< schedule[i].info << "\t"
			<< schedule[i].date.month << "\t"
			<< schedule[i].date.day << "\t"
			<< schedule[i].date.year << "\n";
	}

	outfile.close();
}

//Welcome message display
void Welcome()
{
	for (int i = 0; i < 70; ++i)
		cout << "\n";
	cout << "\nWelcome to your homework organizer!"
		<< "\nYou can save up to twenty tasks.";
}

//Activity input
void ReadActivity(reminder schedule[], int & count)
{
	cout << "\nPlease enter the activity you wish to save: ";
	cin.get(schedule[count].activity, SIZE, '\n');
	cin.ignore(100, '\n');
}

//Course input
void ReadCourse(reminder schedule[], int & count)
{
	cout << "\nPlease enter the name of the course you wish to save: ";
	cin.get(schedule[count].course, SIZE, '\n');
	cin.ignore(100, '\n');

}

//Date input
void ReadDate(reminder schedule[], int & count)
{
	cout << "\nPlease enter the due date (MM/DD/YY): ";
	cin >> schedule[count].date.month;
	cin.ignore(100, '/');
	cin >> schedule[count].date.day;
	cin.ignore(100, '/');
	cin >> schedule[count].date.year;
	cin.ignore(100, '\n');
}

//Priority input
void ReadPriority(reminder schedule[], int & count)
{
	cout << "\nPlease enter the priority of the activity: ";
	cin.get(schedule[count].priority, SIZE, '\n');
	cin.ignore(100, '\n');

}

//Misc input
void ReadInfo(reminder schedule[], int & count)
{
	cout << "\nPlease enter any information about the activity: ";
	cin.get(schedule[count].info, SIZE, '\n');
	cin.ignore(100, '\n');

}
