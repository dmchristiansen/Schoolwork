/*
Daniel Christiansen
CS202
Program 3
*/

//CLL.h
//'CLL' class prototype

#include "song.h"

//CLL class to be used as a playlist of songs.
//Manages Node objects
class CLL {
	public:
		CLL();
		~CLL();
		void ClearList();
		int GetSongCount();
		CLL& operator -=(const Song&);
		CLL& operator +=(const Song&);
		CLL& operator =(const CLL&);
		Node& operator [](int index);
		friend CLL operator +(const CLL&, const Song&);
		friend CLL operator +(const Song&, const CLL&);
		friend ostream& operator <<(ostream&, const CLL&);
	protected:
		Node * rear;
		int songCount;
};
