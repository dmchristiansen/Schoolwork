/*
Daniel Christiansen
CS 202
Program 1
*/

//player.h
//class prototypes for hand, player, computer, and human classes

#include "card.h"

//hand class
//contains a DLL of node objects, each one a card
class hand {
	public:
		hand();
		hand(const hand & source);
		~hand();
		void draw(deck & source); //draws a card from deck object passed in		
		void add_card(node * new_card, int index); //adds a card to the table
		void move_card(node * new_card, int index); //moves an existing card into the table
		void display(); //displays hand
		int hand_size(); //returns the number of cards in the hand
	protected:	
		node * table[13];
		int hand_count;
};

//player class
//generic player class inhereted from 'hand' class
class player: public hand {
	public: 
		player();
		player(hand & new_hand, int new_score);
		player(const player & source);
		~player();
		int check(int index); //checks if the guess is correct
		bool assess(); //checks the state of the player's hand
		void take(player & other_player, int index); //takes cards from another player object
		int score(); //echoes score
	protected:
		int books;
};

//cpu class
//class to act as the CPU player
class computer: public player {
	public:
		computer();
		computer(hand & new_hand, int new_score);
		~computer();
		//these function will probably need to be revised...
		int guess();
};

//human class
//class containing funtions for the player to interface with the game
class human: public player {
	public:
		human();
		human(hand & new_hand, int & new_score);
		~human();
		int guess();
};

