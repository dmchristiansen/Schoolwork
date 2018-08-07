/*
Daniel Christiansen
CS202
Program 1
Go Fish
*/

//card.cpp

//class functions for card class

#include "card.h"

/*	'card' class functions	*/

//default constructor
card::card()
{
	rank = 0;
	suit = '\0';
}

//constructor w/ variables
card::card(int rank, char suit)
{
	this->rank = rank;
	this->suit = suit;	
}

//copy constructor
card::card(const card & source)
{
	rank = source.rank;
	suit = source.suit;
}

//destructor
card::~card()
{
//this destructor is empty, as there is no dynamically allocated memory in a 'card' class
}

//function to display the rank and suit of a card.
//returns 0 if the card object contains 0 values.
int card::display()
{
	if(rank == 0 || suit == '\0')
		return 0;

	//displays rank
	if(rank == 1) {
		cout << "A";
	} else if (rank > 1 && rank < 11) {
		cout << rank;
	} else {
		switch (rank) {
		case 11:
			cout << "J";
			break;
		case 12:
			cout << "Q";
			break;
		case 13:
			cout << "K";
			break;
		}
	}

	cout << suit;

	return 1;
}

//function to compare card rank
//return 1 on a match, otherwise 0
int card::compare(int value)
{
	if(value == rank)
		return 1;
	else
		return 0;
}

/*	'node' class functions	*/

//node default constructor
node::node()
{
	previous = NULL;
	next = NULL;
}

//node constructor
node::node(int rank, char suit) : card(rank, suit)
{
	previous = NULL;
	next = NULL;
}

//node copy constructor
node::node(const card & new_card) : card(new_card)
{
	previous = NULL;
	next = NULL;
}

//node destructor
node::~node()
{
	previous = NULL;
	next = NULL;
}

//returns value of previous pointer
node *& node::get_previous()
{
	return previous;
}

//retirns value of next pointer
node *& node::get_next()
{
	return next;
}

//sets value of node's previous pointer
void node::set_previous(node * connection)
{
	previous = connection;
}

//sets value of node's next pointer
void node::set_next(node * connection)
{
	next = connection;
}

/*	deck class functions	*/

//default deck constructor
deck::deck()
{
	reset();
}

//deck copy constructor
deck::deck(const deck & source)
{
	reset();
	node * current;
	node temp;
	for(int i = 0; i < 4; ++i)
	{
		current = source.head[i];
		while(current)
		{
			add_card(current, i);
			current = current->get_next();
		}
	}
}

//deck destructor
deck::~deck()
{
	clear();
}

//function to empty a deck's card list
void deck::clear()
{
	node * current;
	node * previous;

	for(int i = 0; i < 4; ++i)
	{
		if(head[i])
		{
			current = head[i];
			previous = current;
			while(current)
			{
				current = current->get_next();
				previous->set_next(NULL);
				previous->set_previous(NULL);
				delete previous;
				previous = current;
			}
		}
	}
	reset();
}


//resets class members
void deck::reset()
{
	for(int i = 0; i < 4; ++i)
	{
		head[i] = NULL;
		tail[i] = NULL;
	}
	card_count = 0;
}

//function to build a deck as a DLL of nodes
//takes an integer to determine gow many decks worth of cards to shuffle in.
void deck::build(int deck_count)
{
	char suit;

	//clears existing deck, if there is one
	clear();
	
	for(int i = 0; i < deck_count; ++i)
	{
		for(int suit_no = 0; suit_no < 4; ++suit_no)
		{
			for(int rank = 1; rank < 14; ++rank)
			{
				switch (suit_no) 
				{
					case 0:
						suit = 'D';
						break;
					case 1:
						suit = 'H';
						break;
					case 2:
						suit = 'S';
						break;
					case 3:
						suit = 'C';
						break;
					default:
						suit = '\0';
				}
				add_card(rank, suit, suit_no);
			}
		}
	}
}

 //adds a single card - created in this function - to the tail of the deck list
void deck::add_card(int rank, char suit, int index)
{
	node * temp = new node(rank, suit);

	if(!tail[index])
	{
		head[index] = temp;
	} 
	else 
	{
		temp->set_previous(tail[index]);
		tail[index]->set_next(temp);
	}
	
	tail[index] = temp;
	++card_count;
}

//adds a single card - passed into this function - to the tail of a deck list
void deck::add_card(node * new_card, int index)
{
	node * temp = new node(*new_card);

	if(!tail[index])
	{
		head[index] = temp;
	} 
	else 
	{
		temp->set_previous(tail[index]);
		tail[index]->set_next(temp);
	}
	
	tail[index] = temp;
	++card_count;
}

//transfers an existing card node  to the tail of the deck list
void deck::move_card(node * new_card, int index)
{
	if(!new_card) //just in case a NULL pointer is passed in
		return;	

	if(!tail[index])
	{
		head[index] = new_card;
	}
	else
	{
		new_card->set_previous(tail[index]);
		tail[index]->set_next(new_card);
	}
	new_card->set_next(NULL);
	tail[index] = new_card;
	++card_count;
}

void deck::shuffle() //shuffles deck
{
	if(!card_count) //no need to shuffle an empty deck
		return;

	int i, j, k; //index variables

	srand(time(NULL)); //random seed for interleaving cards while shuffling
	int step; //variable used for randomizing shuffling

	node * left_hand; //temporary pointers used to split the deck in half...
	node * right_hand;
	node * temp;

	for(i = 0; i < 7; ++i) //shuffles the deck seven times...
	{
		//combines the deck in two lists
		left_hand = head[0];
		tail[0]->set_next(head[1]);
		head[1]->set_previous(tail[0]);
		right_hand = head[2];
		tail[2]->set_next(head[3]);
		head[3]->set_previous(tail[2]);
		reset();		

		//collates the cards, adding them back into the list
		while(right_hand)
		{
			//some of the right half is shuffled in...
			step = rand() % 3 + 1; //step size from 1 to 3
			for(k = 0; k < step; ++k)
			{
				if(right_hand)
				{
					temp = right_hand;
					right_hand = right_hand->get_next();
					move_card(temp, card_count % 4);	
				}
			}

			//some of the left half is shuffled in...
			step = rand() % 3 + 1;
			for(k = 0; k < step; ++k)
			{
				if(left_hand)
				{
					temp = left_hand;
					left_hand = left_hand->get_next();
					move_card(temp, card_count % 4);
				}
			}
		}
		//adds any leftover cards from the other half...
		while(left_hand)
		{
			temp = left_hand;
			left_hand = left_hand->get_next();
			move_card(temp, card_count % 4);
		}
	}
}

//returns pointer to node object (single card), and removes from itself
node * deck::deal() {
	node * temp;

	//finds the first card in the array of lists, excises it, and returns it
	for(int i = 0; i < 4; ++i)
	{
		if(head[i])
		{
			temp = head[i];
			head[i] = head[i]->get_next();
			temp->set_previous(NULL);
			temp->set_next(NULL);
			--card_count;
			return temp;
		}
	}
	//if the deck is empty...
	return NULL;
}


//display fumction
void deck::display()
{
	if(!card_count)
	{
		cout << "\nDeck is empty!\n";
		return;
	}

	cout << "\nThere are " << card_count << " cards in the deck.\n";

	node * current;

	for(int i = 0; i < 4; ++i)
	{
		current = head[i];
		while(current)
		{
			current->display();
			cout << "\t ";
			current = current->get_next();
		}
	}
	cout << endl;
}

//returns the number of cards left in the deck
int deck::deck_size()
{
	return card_count;

}











