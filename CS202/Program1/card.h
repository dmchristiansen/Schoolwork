/*
Daniel Christiansen
CS202
Program 1
*/

//card.h

//Class prototypes for the card, node, and deck classes

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//card class
//contains rank and suit information
class card {
	public:
		card();
		card(int rank, char suit);
		card(const card & source);
		~card();
		int display();
		int compare(int value);
	protected:
		int rank; // 1 through 13 (Ace through King)
		char suit; // C, D, H, or S (Clubs, Diamonds, etc.)
};

//node class
//used to manage a DLL of cards
class node: public card {
	public:
		node();
		node(int rank, char suit);
		node(const card & new_card);
		~node();
		node *& get_previous();
		node *& get_next();
		void set_previous(node * connection);
		void set_next(node * connection);
	protected:
		node * previous;
		node * next;
};

//deck class
//deck contains a DLL of node objects, each one a card
class deck {
	public:
		deck();
		deck(const deck & source);
		~deck();
		void reset(); //resets class members
		void build(int deck_count); //build deck in unsorted order
		void add_card(int rank, char suit, int index); //adds a single card to the tail of a deck list
		void add_card(node * new_card, int index);
		void move_card(node * new_card, int index); //moves an existing card to the tail of a deck list
		void shuffle(); //shuffles deck
		node * deal(); //returns pointer to node object (single card), and removes from itself
		void clear(); //empties deck's card list
		void display();
		int deck_size(); //returns the number of cards left in the deck
	private:
		node * head[4]; //array of head pointers
		node * tail[4]; //array of tail pointers
		int card_count; //current size of deck
};


