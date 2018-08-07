/*
Daniel Christiansen
CS202
Program 3
*/

//main.cpp
//This program us meant to simulate the functionality of the Pandora radio servic.
//It uses a hash table to keep track of songs sorted by artist,
//a graph table to keep track of songs by genre, and a CLL to maintain a playlist of songs.
//Loads song list from songs.txt

#include "graph.h"
#include <iostream>
#include <fstream>

void Welcome();
char MainMenu();
char LikeMenu();
int LoadFile(ifstream &, Table &, Graph &);
void Randomize(CLL &, Table &, Graph &);
void Play(CLL &);

//main function loops through a menu, dispatching based on chosen option
int main()
{
	CLL Playlist;
	Table Artist;
	Graph Genre;
	
	Welcome();

	ifstream infile("songs.txt");
	char choice;

	if(LoadFile(infile, Artist, Genre))
	{
		cout << Genre;
		do {
			choice = MainMenu();
			switch(choice) {
				case 'R':
					Randomize(Playlist, Artist, Genre);
					break;
				case 'P':
					Play(Playlist);
					break;
				default:
					break;
			}
		} while(choice != 'X');
	} else {
		cout << "\nCouldn't load song file (songs.txt)";
	}

	return 0;
}

//function to welcome the user
void Welcome()
{
	for(int i = 0; i < 75; ++i)
		cout << '\n';
	cout << "\nWelcome to you Pandora emulator!";
}

//displays main menu and returns a char
char MainMenu()
{
	char choice;

	cout << "\n\nPlease choose one of the following:"
		<< "\n(R) Play randomized playlist"
		<< "\n(P) Play liked playlist"
		<< "\n(X) Exit";
	do {
		cout << "\n(R/P/X): ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);
	} while(!(choice == 'R' || choice == 'P' || choice == 'X'));

	return choice;
}

//loads song.txt into Table and Graph objects
int LoadFile(ifstream & infile, Table & Artist, Graph & Genre)
{
	char title[100], artist[100], album[100];
	char ** genres;
	int genreCount, seconds;
	Song * newSong;

	srand(time(NULL));

	//checks if the file is open...
	if(infile.is_open())
	{
		//loops through the file, getting data...
		infile.getline(title, 100, '\n');
		while(!infile.eof())
		{
			infile.getline(artist, 100, '\n');	
			infile.getline(album, 100, '\n');
			infile >> genreCount;
			infile.ignore(100, '\n');
			genres = new char * [genreCount];
			for(int i = 0; i < genreCount; ++i)
			{
				genres[i] = new char[100];
				infile.getline(genres[i], 100, '\n');
			}
			infile >> seconds;
			infile.ignore(100, '\n');

			//adding the data to a Song object...
			newSong = new Song(title, artist, album, genres, genreCount, seconds);
			for(int i = 0; i < genreCount; ++i)
				delete genres[i];
			delete genres;
			infile.ignore(100, '\n');

			//and adding it to the appropriate data structures.
			Artist += *newSong;
			Genre += *newSong;
			delete newSong;

			infile.getline(title, 100, '\n');
		}			
	} else {
		cout << "\nNo file";
		return 0;
	}
	return 1;
}

//function to randomize by genre or artist
void Randomize(CLL & Playlist, Table & Artist, Graph & Genre)
{
	int index;
	char choice;

	Node * currentSongNode;
	Node * tempNode;
	//playing first random song from hash table...
	do {
		cout << "\nPlaying random song...\n";
		currentSongNode = new Node(Artist.GetRandom());
		cout << *currentSongNode;
		choice = LikeMenu();
		if(choice == 'U')
		{
			Playlist += *currentSongNode;
			cout << "\nAdding to playlist...";
		} else
			delete currentSongNode;
	} while(choice != 'U');

	//playing subsequent random songs...
	do {
		tempNode = currentSongNode;
		currentSongNode = new Node(Genre.RandomJump(*tempNode));
		delete tempNode;
		cout << *currentSongNode;
		choice = LikeMenu();
		switch (choice) {
		case 'U':
			Playlist += *currentSongNode;
			cout << "\nAdding to playlist...";
			break;
		case 'D':
			break;
		case 'N':
			break;
		case 'S':
			break;
		}
	} while(choice != 'S');
	delete currentSongNode;
}

//function to play current playlist
void Play(CLL & Playlist)
{
	char choice;
	Node * currentSongNode;

	cout << "\nPlaying your playlist...";

	do {
		currentSongNode = &(Playlist[rand() % Playlist.GetSongCount()]);
		cout << *currentSongNode;
		choice = LikeMenu();
		switch (choice) {
		case 'U':
			break;
		case 'D':
			Playlist -= *currentSongNode;
			break;
		case 'N':
			break;
		case 'S':
			break;
		} 
	} while(choice != 'S');
}

//used for thumbs up/down when using playlists
char LikeMenu()
{
	char choice;

	cout << "\nChoose one: "
		<< "\n(U) Thumbs up"
		<< "\n(D) Thumbs down"
		<< "\n(N) Next"
		<< "\n(S) Stop play";

	do {
		cout << "\n(U/D/N): ";
		cin >> choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);
	} while(!((choice == 'U') || (choice == 'D') || (choice == 'N') || (choice == 'S')));
	return choice;
}






