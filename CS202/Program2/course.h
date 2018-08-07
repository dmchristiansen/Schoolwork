/*
Daniel Chrisdtiansen
CS202
Program 2
*/

//course.h

//prototypes for Course, NonRequired, Required, Core, and NonCore classes

#include <iostream>
#include <cstring>

using namespace std;

class Course {
	public:
		Course();
		Course(char *, char *, int, int, bool, float);
		Course(const Course &);
		virtual ~Course();
		virtual void Display();
		void ReturnCredits(float &, float &);
		virtual void ReturnCoreCredits(float &, float &) {};
	protected:
		char * name;	
		char * subject;
		int CRN;
		int credits;
		bool completed;
		float earned_credits;
};

class NonRequired : public Course {
	public:
		NonRequired();
		NonRequired(char *, char *, int, int, bool, float);
		NonRequired(const Course &);
		~NonRequired();
		void Display();
		void ReturnCoreCredits(float &, float &);
};

class Required : public Course {
	public:
		Required();
		Required(char *, char *, int, int, bool, float);
		Required(const Course &);
		~Required();
		virtual void Display() {};
		virtual void ReturnCoreCredits(float &, float &) {};
	
};

class Core : public Required {
	public:
		Core();
		Core(char *, char *, int, int, bool, float);
		Core(const Course &);
		~Core();
		void Display();
		void ReturnCoreCredits(float &, float &);
};

class NonCore : public Required {
	public:
		NonCore();
		NonCore(char *, char *, int, int, bool, float);
		NonCore(const Course &);
		~NonCore();
		void Display();
		void ReturnCoreCredits(float &, float &);
};
