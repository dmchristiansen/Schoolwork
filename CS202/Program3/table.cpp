/*
Daniel Christiansen
CS202
Program 3
*/

//table.cpp
//'Table' member functions

#include "table.h"

//default constructor
Table::Table(int size)
{
	songCount = 0;
	tableSize = size;
	table = new Node * [tableSize];
	for(int i = 0; i < tableSize; ++i)
		table[i] = NULL;
}

//Table copy constructor
Table::Table(const Table& source)
{
	songCount = 0;
	tableSize = source.tableSize;
	table = new Node * [tableSize];
	Node * current;
	for(int i = 0; i < tableSize; ++i)
	{
		table[i] = NULL;
		current = source.table[i];
		while(current)
		{
			*this += *current;
			current = current->GetNext();
		}
	}
}

//destructor
Table::~Table()
{
	Node * current;
	Node * previous;

	if(table)
	{
		for(int i = 0; i < tableSize; ++i)
		{
			current = table[i];
			previous = current;
			while(current)
			{
				current = current->GetNext();
				previous->SetNext(NULL);
				delete previous;
				previous = current;
			}
			table[i] = NULL;
		}
	}
	delete [] table;
}

//[] operator overloaded for Table[]
Node& Table::operator [](int index)
{
	if(table)
	{
		int count = 0;
		for(int i = 0; i < tableSize; ++i)
		{
			Node * current = table[i];
			while(current)
			{
				if(count == index)
					return *current;
				current = current->GetNext();
				++count;
			}
		}
	}
	Node * temp = new Node();
	return *temp;
}

//+ operator for Table + Song
Table operator +(const Table& Artist, const Song& newSong)
{
	Table newArtist(Artist);
	newArtist += newSong;
	return newArtist;
}

//+ operator for Song + Table
Table operator +(const Song& newSong, const Table& Artist)
{
	Table newArtist(Artist);
	newArtist += newSong;
	return newArtist;
}

//+ operator for Table + Table
Table operator +(const Table& table1, const Table& table2)
{

}

//+ operator for Song + Song
Table operator +(const Song& song1, const Song& song2)
{
	Table newTable;
	newTable += song1;
	newTable += song2;
	return newTable;	
}

//+= operator for Table += Song
Table& Table::operator +=(const Song& newSong)
{
	InsertSong(newSong);
	return *this;
}

//+= operator for Table + Table
Table& Table::operator +=(const Table& newTable)
{
	Node * current;
	for(int i = 0; i < newTable.tableSize; ++i)
	{
		current = newTable.table[i];
		while(current)
		{
			InsertSong(*current);
			current = current->GetNext();
		}
	}
	return *this;
}

//insertion function
void Table::InsertSong(const Song& newSong)
{
	Node * newNode = new Node(newSong);
	int key = Hash(newNode->GetArtist());
	Node * temp = table[key];
	table[key] = newNode;
	newNode->SetNext(temp);
	++songCount;
}

//hash function
int Table::Hash(char * keyValue)
{
	if(!keyValue)
		return 0;

	int hashKey = 0;
	int i;
	for(i = 0; i < strlen(keyValue); ++i)
	{
		hashKey += (keyValue[i] * i);
	}
	return hashKey % tableSize;
}

//overloaded << operator (used as a wrapper for 'DisplayAll' function)
ostream& operator <<(ostream& out, Table& Artist)
{
	Artist.DisplayAll();
	return out;
}

//funtion to display contents of 
void Table::DisplayAll()
{
	cout << "\nThere are " << songCount << " songs in your library.";

	Node * current;
	for(int i = 0; i < tableSize; ++i)
	{
		current = table[i];
		while(current)
		{
			cout << *current;
			current = current->GetNext();
		}
	}
}

//function to return a random node
Node& Table::GetRandom()
{
	return (*this)[rand() % songCount];
}
