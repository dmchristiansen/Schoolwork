/*
Daniel Christiansen
CS202
Program 1
Go Fish!
*/

//gofish.cpp

#include "player.h"

void Welcome();

int main()
{
	int guess, i;
	bool again;

	//players created...
	human player1;
	computer player2;

	//deck created and shuffled...
	deck main_deck;
	main_deck.build(1);
	main_deck.shuffle();
	
	Welcome();

	//both players draw their initial hands...
	for(i = 0; i < 5; ++i)
	{
		player1.draw(main_deck);
		player2.draw(main_deck);
	}

	cout << "\nPlayer, you begin the game...";

	//loops through alternating turns while there are still cards in play...
	while(main_deck.deck_size() || player1.hand_size() || player2.hand_size())
	{
		cout << "\n\nIt's your turn.";
		again = true;
		while(again && (player1.hand_size() || main_deck.deck_size()))
		{
			player1.display();
			guess = player1.guess();
			if(player2.check(guess - 1))
			{
				cout << "\n\nThey had: "; 
				player1.take(player2, guess - 1);
				if(player1.assess())
					cout << "\nYour score is " << player1.score();
				if(!player1.hand_size())
				{
					for(i = 0; i < 5; ++i)
					{
						player1.draw(main_deck);
						player1.assess();
					}
				}
			} else {
				cout << "\n\nGo fish!";
				player1.draw(main_deck);
				again = false;
				if(player1.assess())
					cout << "\nYour score is " << player1.score();
			}
		}
		player1.assess();
		cout << "\n\nThe computer is thinking...";
		again = true;
		while(again && (player2.hand_size() || main_deck.deck_size()))
		{
			guess = player2.guess();
			if(player1.check(guess - 1))
			{
				cout << "\n\nThey took ";
				player2.take(player1, guess - 1);
				if(player2.assess())
					cout << "\nThe computer's score is " << player2.score();
				if(!player2.hand_size())
				{
					for(i = 0; i < 5; ++i)
					{
						player2.draw(main_deck);
						player2.assess();
					}
				}
			} else {
				cout << "\n\nThe computer is drawing a card...";
				player2.draw(main_deck);
				again = false;
				player2.assess();
			}
		}
		player2.assess();
	}


	cout << "\nGame over!\nThe score was " 
		<< player1.score() << "(you) to " 
		<< player2.score() << "(computer).";

	if(player1.score() > player2.score())
		cout << "\nYou win!";
	else if(player1.score() < player2.score())
		cout << "\nYou lose!";
	else
		cout << "\nTie game!";

	return 0;
}

void Welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << endl;

	cout << "\nYou are now playing 'Go Fish!', a fun game for the whole family!"
		<< "\n(One player only)" << endl;

	cout << "\n\nThe rules are as follows:"
		<< "\nEach player starts with five cards."
		<< "\nThe goal is to get 'books' of four cards of the same rank."
		<< "\nTo get those cards, you must guess the contents of the other player's hand."
		<< "\nIf you have a card of a certain rank, you may ask if the player has any of the same."
		<< "\nIf they do, they must give them to you, and you get another guess."
		<< "\nIf not, you must 'go fish', and draw a card."
		<< "\nIf you have gour of a kind, you discard them and get a point."
		<< "\nThe game continues until there are no more cards in play."
		<< "\nHave fun!\n";
}

