//table.h
//class declarations for 'job' and 'table' classes

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class job {
	public:
		job();
		~job();
		int create_entry(char Name[], char Location[], char Title[], char Description[],
							 char Rate[], char ** experience, int skills);
		int retrieve();
		int display();
		int match(char *compExperience[], int compSkills);
	private:
		char * name;
		char * location;
		char * title;
		char * description;
		char * rate; //pay rate
		char ** experience; //skills required
		int skills; //number of items in experience
};

struct node {
		job listing;
		node * next;
};

class table {
	public:
		table();
		table(char * file, int & success);
		~table();
		int retrieve(char title[], char *experience[], int skills, job ** &results, int &matches);
		int add(char * keyVal, node * toAdd);
		int load();
		int hash(char * keyval);
		int displayAll();
	private:
		node ** list;
		int tablesize;
};
