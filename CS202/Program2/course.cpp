/*
Daniel Christiansen
CS202
Program 2
*/

//course.cpp

#include "course.h"

/* Course member functions */

//default constructor
Course::Course()
{
		name = NULL;
		subject = NULL;
		CRN = 0;
		credits = 0;
		completed = false;
		earned_credits = 0;
}

//other constructor
Course::Course(char * name, char * subject, int CRN, int credits, bool completed, float earned_credits)
{
	if(name)
	{
		this->name = new char[strlen(name)+1];
		strcpy(this->name, name);
	} else {
		this->name = NULL;
	}

	if(subject)
	{
		this->subject = new char[strlen(subject)+1];
		strcpy(this->subject, subject);
	} else {
		this->subject = NULL;
	}

	if(CRN >= 0)
		this->CRN = CRN;
	else
		this->CRN = 0;

	if(credits >= 0)
		this->credits = credits;
	else
		this->credits = 0;

	this->completed = completed;

	if(earned_credits >= 0)
		this->earned_credits = earned_credits;
	else
		this->earned_credits = 0;
}

//copy constructor
Course::Course(const Course & source)
{
	if(name)
	{
		delete name;
		name = NULL;
	}
	if(source.name)
	{
		name = new char[strlen(source.name)+1];
		strcpy(name, source.name);
	}

	if(subject)
	{
		delete subject;
		subject = NULL;
	}
	if(source.subject)
	{
		subject = new char[strlen(source.subject)+1];
		strcpy(subject, source.subject);
	}

	if(source.CRN >= 0)
		CRN = 0;
	else
		CRN = 0;

	if(source.credits >= 0)
		credits = source.credits;
	else
		credits = 0;

	completed = source.completed;

	if(source.earned_credits >= 0)
		earned_credits = source.earned_credits;
	else
		earned_credits = 0;
}

//destructor
Course::~Course()
{
	if(name)
		delete name;
	name = NULL;

	if(subject)
		delete subject;
	subject = NULL;
}

//basic display function
void Course::Display()
{
}

//function to return credits earned
void Course::ReturnCredits(float & actual_credits, float & attempted_credits)
{
	actual_credits += earned_credits;
	attempted_credits += credits;
}

/* NonRequired member functions */

//default constructor
NonRequired::NonRequired()
{

}

//copy constructor
NonRequired::NonRequired(const Course & source) : Course(source)
{
}

//destructor
NonRequired::~NonRequired()
{
}

//display function
void NonRequired::Display()
{
	cout << "\nNon-Required class" 
		<< "\nCourse name: " << name
		<< "\nCourse code: " << subject
		<< "\nCRN: " << CRN
		<< "\nCredit value: " << credits
		<< "\nCompleted: " << (completed ? "Yes" : "No")
		<< "\nCredits earned: " << earned_credits << endl; 
}

//returns core credits (it's a non core class, return 0)
void NonRequired::ReturnCoreCredits(float & earned_credits, float & attempted_credits) {}

/* Required member functions */

//default constructor
Required::Required()
{
}

//copy constructor
Required::Required(const Course & source) : Course(source)
{
}

//destructor
Required::~Required()
{
}


/* Core member functions */

//degault constructor
Core::Core()
{
}

//copy constructor
Core::Core(const Course & source) : Required(source)
{
}

//destructor
Core::~Core()
{
}

//display function
void Core::Display()
{
	cout << "\nRequired/Core class" 
		<< "\nCourse name: " << name
		<< "\nCourse code: " << subject
		<< "\nCRN: " << CRN
		<< "\nCredit value: " << credits
		<< "\nCompleted: " << (completed ? "Yes" : "No")
		<< "\nCredits earned: " << earned_credits << endl; 
}

//function to gather earned/atempted credit values
void Core::ReturnCoreCredits(float & actual_credits, float & attempted_credits)
{
	actual_credits += earned_credits;
	attempted_credits += credits;
}

/* NonCore member functions */

//default constructor
NonCore::NonCore()
{
}

//copy constructor
NonCore::NonCore(const Course & source) : Required(source)
{
}

//destructor
NonCore::~NonCore()
{
}

//basic display function
void NonCore::Display()
{
	cout << "\nRequired/Non-Core class" 
		<< "\nCourse name: " << name
		<< "\nCourse code: " << subject
		<< "\nCRN: " << CRN
		<< "\nCredit value: " << credits
		<< "\nCompleted: " << (completed ? "Yes" : "No")
		<< "\nCredits earned: " << earned_credits << endl; 
}

//blank function for overloading
void NonCore::ReturnCoreCredits(float & actual_credits, float & attempted_credits) {}

