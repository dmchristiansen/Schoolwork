/*
Daniel Christiansen
CS202
Program 3
*/

//CLL.cpp
//'CLL' member functions

#include "CLL.h"

//degault constructor
CLL::CLL()
{
	rear = NULL;	
	songCount = 0;
}

//destructor
CLL::~CLL()
{
	ClearList();
}

//getter
int CLL::GetSongCount()
{
	return songCount;
}

//list destruction function
//used by destructor & overloaded =
void CLL::ClearList()
{
	if(rear)
	{
		Node * current = rear->GetNext();
		Node * previous = current;
		rear->SetNext(NULL);
		while(current)
		{
			current = current->GetNext();
			delete previous;
			previous = current;
		}
	}
}

//= operator overloaded for CLL = CLL
CLL& CLL::operator =(const CLL& appendList)
{
	if(rear)
		ClearList();

	if(appendList.rear)
	{
		Node * current = appendList.rear;
		do {
			current = current->GetNext();
			*this += *current;
		} while(current != appendList.rear);
	}

	return *this;
}

//-= operator overloaded for CLL -= Song
CLL& CLL::operator -=(const Song& removeSong)
{
	Node * current = rear;
	Node * previous = current;
	if(rear)
	{
		do {
			current = current->GetNext();
			if(removeSong == *current)
			{
				if(rear == rear->GetNext())
				{
					delete rear;
					rear = NULL;
				} else if(rear == current) {
					rear = previous;
					previous->SetNext(current->GetNext());
					delete current;
					current = previous;
				} else {
					previous->SetNext(current->GetNext());
					delete current;
					current = previous;
				}
				--songCount;
			}
			previous = current;
		} while(current != rear);
	}
	return *this;
}

//+= operator overloaded for CLL += Song
CLL& CLL::operator +=(const Song& newSong)
{
	Node * newNode = new Node(newSong);
	if(rear)
		newNode->SetNext(rear->GetNext());
	else
		newNode->SetNext(newNode);

	rear = newNode;			
	++songCount;
	return *this;
}

//[] operator overloaded for CLL[]
Node& CLL::operator [](int index)
{
	if(!rear)
	{
		Node * temp = new Node;
		return *temp;
	}

	Node * current = rear->GetNext();
	for(int i = 0; i < index; ++i)
	{
		current = current;
	}
	return *current;
}

//+ operator overloaded for CLL + Song
CLL operator +(const CLL & Playlist, const Song& newSong)
{
	CLL newPlaylist;
	newPlaylist += newSong;
	return newPlaylist;
}

//+ operator overloaded for Song + CLL
CLL operator +(const Song& newSong, const CLL& Playlist)
{
	CLL newPlaylist;
	newPlaylist += newSong;
	return newPlaylist;
}

//<< operator overloaded for cout << CLL
ostream& operator <<(ostream& out, const CLL& Playlist)
{
	if(Playlist.rear)
	{
		Node * current = Playlist.rear;
		do {
			current = current->GetNext();
			cout << *current;
		} while(current != Playlist.rear);
	}
	return out;
}
