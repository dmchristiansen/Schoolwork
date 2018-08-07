/*
Daniel Christiansen
CS202
Program 3
*/

//song.cpp
//'Song' and 'Node' member functions

#include "song.h"

/*	'Song' class functions	*/

//default constructor
Song::Song()
{
	title = NULL;
	artist = NULL;
	album = NULL;
	genres = NULL;
	genreCount = 0;
	seconds = 0;
}

//constructor w/ individual args
Song::Song(char * newTitle, char * newArtist, char * newAlbum, char ** newGenres, int newGenreCount, int newSeconds)
{
	if(newTitle)
	{
		title = new char[strlen(newTitle)+1];
		strcpy(title, newTitle);
	} else {
		title = NULL;
	}

	if(newArtist)
	{
		artist = new char[strlen(newArtist)+1];
		strcpy(artist, newArtist);
	} else {
		artist = NULL;
	}

	if(newAlbum)
	{
		album = new char[strlen(newAlbum)+1];
		strcpy(album, newAlbum);
	} else {
		album = NULL;
	}

	if(newGenres)
	{
		genreCount = newGenreCount;
		genres = new char * [newGenreCount];
		for(int i = 0; i < newGenreCount; ++i)
		{
			genres[i] = new char[strlen(newGenres[i]+1)];
			strcpy(genres[i], newGenres[i]);
		}
	} else {
		genres = NULL;
		genreCount = 0;
	}

	seconds = newSeconds;
}

//copy constructor
Song::Song(const Song & source)
{
	if(source.title)
	{
		title = new char[strlen(source.title)+1];
		strcpy(title, source.title);
	} else {
		title = NULL;
	}

	if(source.artist)
	{
		artist = new char[strlen(source.artist)+1];
		strcpy(artist, source.artist);
	} else {
		artist = NULL;
	}

	if(source.album)
	{
		album = new char[strlen(source.album)+1];
		strcpy(album, source.album);
	} else {
		album = NULL;
	}

	if(source.genres)
	{
		genreCount = source.genreCount;
		genres = new char * [source.genreCount];
		for(int i = 0; i < source.genreCount; ++i)
		{
			genres[i] = new char[strlen(source.genres[i]+1)];
			strcpy(genres[i], source.genres[i]);
		}
	} else {
		genres = NULL;
		genreCount = 0;
	}

	seconds = source.seconds;
}

//destructor
Song::~Song()
{
	ClearSong();
}

//function to actually clear out a song's data
//used by destructor and overloaded =
void Song::ClearSong()
{
	if(title)
		delete [] title;
	if(artist)
		delete [] artist;
	if(album)
		delete [] album;
	for(int i = 0; i < genreCount; ++i)
		if(genres[i])
			delete [] genres[i];
	delete [] genres;
}

//a getter to retrieve the 'artist' field
char * Song::GetArtist()
{
	return artist;
}

//a getter to retrieve the 'genres' field
char ** Song::GetGenres() const
{
	return genres;
}

//a getter to retrieve the 'genreCount' field
int Song::GetGenreCount() const
{
	return genreCount;
} 

//display function
void Song::Display() const
{
	if(title)
		cout << "\nTitle: " << title;
	if(artist)
		cout << "\nArtist: " << artist;
	if(album)
		cout << "\nAlbum: " << album;
	if(genres)
	{
		cout << "\nGenre(s): ";
		if(genreCount)
			cout << genres[0];
		for(int i = 1; i < genreCount; ++i)
			cout << ", " << genres[i];
	}
	cout << "\nLength: " << (seconds / 60) << "m " << (seconds % 60) << "s\n";
}

//<< oeprator overloaded for Song
ostream& operator <<(ostream& out, const Song& currentSong)
{
	currentSong.Display();
	return out;
}

//== operator overloaded for Song == Song
bool operator ==(const Song& song1, const Song& song2)
{
	if(!strcmp(song1.title, song2.title)
		&& !strcmp(song1.artist, song2.artist)
		&& !strcmp(song1.album, song2.album))
		return true;
	else
		return false;
}

//!= operator overloaded for Song != Song
bool operator !=(const Song& song1, const Song& song2)
{
	return !(song1 == song2);
}

//< operator overloaded for Song < Song
//Compares based on alphabetical organization
//of artist, then title, then album
bool operator <(const Song& song1, const Song& song2)
{
	if(strcmp(song1.artist, song2.artist) < 0)
		return true;
	else if (strcmp(song1.artist, song2.artist) > 0)
		return false;
	else if(!strcmp(song1.artist, song2.artist))
	{
		if(strcmp(song1.title, song2.title) < 0)
			return true;
		else if(strcmp(song1.title, song2.title) > 0)
			return false;
		else if(!strcmp(song1.title, song2.title))
		{
			if(strcmp(song1.album, song2.album) < 0)
				return true;
			else
				return false;
		}
	}
}

//> operator overloaded for Song > Song
bool operator >(const Song& song1, const Song& song2)
{
	return song2 < song1;
}

//<= operator overloaded for Song <= Song
bool operator <=(const Song& song1, const Song& song2)
{
	return !(song2 < song1);
}

//>= operator overloaded for Song >= Song
bool operator >=(const Song& song1, const Song& song2)
{
	return !(song1 < song2);
}

/*	'Node' class functions	*/

//default constructor
Node::Node()
{
	next = NULL;
}

//constructor w/ Song object
Node::Node(const Song & source) : Song(source)
{
	next = NULL;
}

//copy constructor
Node::Node(const Node & source) : Song(source)
{
	next = NULL;
}

//destructor
Node::~Node()
{
	next = NULL;
}

//setter
void Node::SetNext(Node * pointer)
{
	next = pointer;
}

//getter
Node *& Node::GetNext()
{
	return next;
}

//= operator overloaded for Node = Node
Node& Node::operator =(const Node& source)
{
	Song::ClearSong();
	
	if(source.title)
	{
		title = new char[strlen(source.title)+1];
		strcpy(title, source.title);
	} else {
		title = NULL;
	}

	if(source.artist)
	{
		artist = new char[strlen(source.artist)+1];
		strcpy(artist, source.artist);
	} else {
		artist = NULL;
	}

	if(source.album)
	{
		album = new char[strlen(source.album)+1];
		strcpy(album, source.album);
	} else {
		album = NULL;
	}

	if(source.genres)
	{
		genreCount = source.genreCount;
		genres = new char * [source.genreCount];
		for(int i = 0; i < source.genreCount; ++i)
		{
			genres[i] = new char[strlen(source.genres[i]+1)];
			strcpy(genres[i], source.genres[i]);
		}
	} else {
		genres = NULL;
		genreCount = 0;
	}

	seconds = source.seconds;
}
