//list.h

#include "powers.h"

struct node {
	power_entry * power;
	hero_entry * hero;
	node * next;
};

class hero_match {
	public:
		hero_match();
		~hero_match();
		int add_hero(char super_power[], const hero_entry &);
		int load_heroes(char power_file_name[], char hero_file_name[]);
		int remove_power(char super_power[]);
		int display(); //display all
		int display(char super_power[]); //display by power
		int find(char situation[], power_entry & found_power);
	private:
		node * head;
};


