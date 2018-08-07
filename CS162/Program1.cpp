/*
Outline of the program:

1. Welcome message
2. Gather daily goal
3. Gather daily calorie expenditure
4. Calculate points, output points along with coupon if applicable
5. Give user the option to
    a. go to step 2
    b. fo to steo 3
    c. exit program
*/

//Daniel Christiansen
//CS 162
//Program 1
//10/13/14

#include <iostream>
#include <cctype>
#include <cmath>
using namespace std;

int main()
{
	int dailyGoal = 0;
	int dailyCal = 0;
	int pointAward = 0;
	int pointTotal = 0;
	char choice = 'C';
	char correct = 'N';

	//welcome message
	cout << "Welcome to your personal calorie counter.\n\n"
		<< "The purpose of this program is to help you track your daily "
		<< "calorie expenditure and reward meeting your goal.\n\n"
		<< "Please enter calorie values in whole numbers.\n";

	//
	while (choice != 'X')
	{
		choice = 'C';
		correct = 'N';

		//Entering calorie goal
		cout << "\nPlease enter your daily calorie goal: ";
		cin >> dailyGoal;

		//Allows user to reenter their calorie goal
		while (correct != 'Y')
		{
			cout  <<  "\nYou have entered " << dailyGoal
			<< ".\nIs this correct? (Y/N) ";
			cin >> correct;
			correct = toupper(correct);
			if (correct == 'N')
			{
				cout << "\nPlease enter your daily calorie goal: ";
				cin >> dailyGoal;
			}
		}

		//
		while (choice == 'C')
		{
			//Enter you daile calories burned
			correct = 'N';
			cout << "\nPlease enter your calories burned today: ";
			cin >> dailyCal;

			//Echoes  calories burned and gives user the option to reenter
			while (correct != 'Y')
			{
				cout << "\nYou entered " << dailyCal << " calories.\n"
					<< "Is this correct?  (Y/N) ";
				cin >> correct;
				correct = toupper(correct);
				if (correct == 'N')
				{
					cout << "\nPlease enter your calories burned today: ";
					cin >> dailyCal;
				}
			}

			//Awards points
			pointAward = (dailyCal*10) / dailyGoal;
			cout << endl << (dailyCal*10)/dailyGoal;
			pointTotal += pointAward;
			cout << "\nYou have recieved " << pointAward << " point(s)!"
				<< "\nYour point total is now " << pointTotal;

			//Checks point value & displays coupon
			if (pointTotal >= 30)
			{
				pointTotal -= 30;
				cout << "\n\n******************"
					<< "\n******************"
					<< "\n     COUPON!"
					<< "\n******************"
					<< "\n******************\n";
				cout << "\nYour point total is now " << pointTotal << endl;
			}

			//Asks user what they want to do next
			cout << "\n\nPlease choose one of the following:"
				<< "\n(C) Enter another day's calorie value"
				<< "\n(G) Enter a new daily goal"
				<< "\n(X) Exit program\n";
			cin >> choice;
			choice = toupper(choice);
		}
	}

	return 0;
}
