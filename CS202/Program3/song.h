/*
Daniel Christiansen
CS202
Program 3
*/

//song.h
//'Song' and 'Node' class prototypes

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Song class, to store basic info
class Song {
	public:
		Song();
		Song(char *, char *, char *, char**, int, int);
		Song(const Song &);
		~Song();
		void ClearSong();
		char * GetArtist();
		char ** GetGenres() const;
		int GetGenreCount() const;
		void Display() const;
		friend ostream& operator << (ostream&, const Song&);
		friend bool operator ==(const Song&, const Song&);
		friend bool operator !=(const Song&, const Song&);
		friend bool operator <(const Song&, const Song&);
		friend bool operator >(const Song&, const Song&);
		friend bool operator <=(const Song&, const Song&);
		friend bool operator >=(const Song&, const Song&);
	protected:
		char * title;
		char * artist;
		char * album;
		char ** genres;
		int genreCount;
		int seconds;
};

//node class used for CLL & DLL
class Node : public Song {
	public:
		Node();
		Node(const Song &);
		Node(const Node &);
		~Node();
		void SetNext(Node *);
		Node *& GetNext();
		Node& operator =(const Node&);
	protected:
		Node * next;
};
