/*
Daniel Christiansen
CS202
Program 1
*/

//player.cpp
//class functions for hand, player, computer, and human classes

#include "player.h"

/*	'hand' class functions	*/

//default constructor
hand::hand()
{
	for(int i = 0; i < 13; ++i)
		table[i] = NULL;
	hand_count = 0;
}

hand::hand(const hand & source)
{
	node * current;
	for(int i = 0; i < 13; ++i)
	{
		table[i] = NULL;
		current = source.table[i];
		while(current)
		{
			add_card(current, i);
			current = current->get_next();
		}			
	}
	
}

//destructor
hand::~hand()
{
	node * current;
	node * previous;
	for(int i = 0; i < 13; ++i)
	{
		current = table[i];
		previous = current;
		while(current)
		{
			current = current->get_next();
			delete previous;
			previous = current;
		}
	}
}

//draws a card from deck object passed in	
void hand::draw(deck & source)
{
	int i = 0;

	//draws a card from the deck
	node * new_card;
	new_card = source.deal();

	if(new_card)
	{
		//determines where the deck should go in the hand array
		while(!new_card->compare(i+1) && i < 14)
			++i;
		
		if(i == 13)
			return;
		else
			add_card(new_card, i);
	}
}

//adds a new card to the table
void hand::add_card(node * new_card, int index)
{
	node * temp = new node(*new_card);

	temp->set_next(table[index]);
	table[index] = temp;
	++hand_count;
}

//adds an existing card to the table
void hand::move_card(node * new_card, int index)
{
	new_card->set_next(table[index]);
	table[index] = new_card;
	++hand_count;
}

//displays contents of hand
void hand::display()
{
	node * current;

	cout << "\nYou have " << hand_count << " cards in your hand: ";
	for(int i = 0; i < 13; ++i)
	{
		current = table[i];
		while(current)
		{
			current->display();
			cout << "  ";
			current = current->get_next();
		}
	}
	cout << endl;
}

//returns the number of cards in the hand
int hand::hand_size()
{
	return hand_count;
}

/*	'player' class functions	*/

//default constructor
player::player()
{
	books = 0;
}

//constructor
player::player(hand & new_hand, int new_books) : hand(new_hand)
{
	books = new_books;
}

//copy constructor
player::player(const player & source) : hand(source)
{
	books = source.books;
}

//destructor
player::~player()
{
}

//function to check whether the indicated index is empty or not
//note that the value passed in is the opponesing player's guess
int player::check(int index)
{
	if(table[index])
		return 1;
	return 0;
}

//function to echo score
int player::score()
{
	return books;
}

//this function checks to see if the player has any complete books, and scores accordingly.
bool player::assess()
{
	node * current;
	int i, j, count;
	bool score_count = false; //tracks whether or not this function incremented the score

	//loops through the table, checking to see if the player has any full books
	for(i = 0; i < 13; ++i)
	{
		//if there are cards in an array element...
		if(table[i])
		{
			//count how many there are...
			count = 0;
			current = table[i];
			while(current)
			{
				++count;
				current = current->get_next();
			}
			//if there is a complete book, remove them and increment score.
			if(count > 3)
			{
				for(j = 0; j < 4; ++j)
				{
					current = table[i];
					if(current)
					{
						score_count = true;
						table[i] = current->get_next();
						delete current;
						--hand_count;
					}
				}
				cout << "\n\nScore incremented.";
				++books;
			}
		}
	}
	return score_count;
}

void player::take(player & other_player, int index)
{
	if(index < 0 || index > 12)
		return;

	node * temp;
	node * current = other_player.table[index];
	while(current)
	{
		cout << " ";
		current->display();
		other_player.table[index] = current->get_next();
		current->set_next(table[index]);
		table[index] = current;
		current = other_player.table[index];
		++hand_count;
		--other_player.hand_count;
	}
}

/*	'computer' class functions	*/

//default constructor
computer::computer(){}

//constructor
computer::computer(hand & new_hand, int new_books) : player(new_hand, new_books){}

//destructor
computer::~computer(){}

//computer guess function
//chooses a random item in the computer's hand and returns it's guess as an integer
int computer::guess()
{
	int guess;
	srand(time(NULL));
	do {
		guess = rand() % 13;
	} while (!table[guess]);
	cout << "\nThe computer asks \"Do you have any ";
	if(guess == 0) {
		cout << "A";
	} else if (guess == 10) {
		cout << "J";
	} else if (guess == 11) {
		cout << "Q";
	} else if (guess == 12) {
		cout << "K";
	} else {
		cout << guess + 1;
	}
	cout << "s?\"";
	return guess + 1;
}

/*	'human' class	*/

//default constructor
human::human(){}

//constructor 
human::human(hand & new_hand, int & new_books) : player(new_hand, new_books){}

//destructor
human::~human(){}

//human guess function
//asks for a guess, checks for validity, returns guess as an integer
int human::guess()
{
	bool valid;
	char guess_rank;
	int guess;
	do {
		valid = true;
		cout << "\nDo you have any...";
		cin >> guess_rank;
		guess_rank = toupper(guess_rank);
		cin.ignore(100, '\n');
		if(guess_rank == 'A') {
			guess = 1;
		} else if(guess_rank == '1') {
			guess = 10;
		} else if(guess_rank == 'J') {
			guess = 11;
		} else if(guess_rank == 'Q') {
			guess = 12;
		} else if(guess_rank == 'K') {
			guess = 13;
		} else if(guess_rank >= '2' && guess_rank <= '9') {
			guess = guess_rank;
			guess = guess - 48;
		} else {
			guess = 0;
			valid = false;
			cout << "\nInvalid guess.  Please enter a card value (A, 2 - 10, J, Q, K)";
		}
		if(!table[guess-1])
		{
			cout << "\nInvalid guess.  In order to guess a card, you must have a card of that rank!";
			valid = false;
		}
	} while (!valid);
	return guess;
}




