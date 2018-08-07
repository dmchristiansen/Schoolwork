//powers.h

#include <iostream>
#include <cstring>

using namespace std;

const int SIZE = 100;

class power_entry {
	public:
		power_entry();
		~power_entry();
		void add_power(char power[], char use[]);
		int fetch(char *, char *, int &);
		void increment();
	private:
		char * power;
		char * use;
		int noHero; //number of heroes who have this power
};

class hero_entry {
	public:
		hero_entry();
		~hero_entry();
		void add_hero(char name[], char desc[]);
		void copy(hero_entry);
		int fetch(char *, char *);
	private:
		char * name; 
		char * desc;
};
