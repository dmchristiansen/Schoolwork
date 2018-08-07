/*
Daniel Christiansen
CS202
Program 3
*/

//table.h
//'Table' class prototype

#include "CLL.h"

//Table class used to implement a hash table of Node objects
class Table {
	public:
		Table(int size = 13);
		Table(const Table&);
		~Table();
		Table& operator +=(const Song&);
		Table& operator +=(const Table&);
		Node& operator [](int index);
		friend Table operator +(const Table&, const Song&);
		friend Table operator +(const Song&, const Table&);
		friend Table operator +(const Table&, const Table&);
		friend Table operator +(const Song&, const Song&);
		friend ostream& operator <<(ostream&, Table&);
		void InsertSong(const Song&);
		int Hash(char *);
		void DisplayAll();
		Node& GetRandom();
	private:
		Node ** table;
		int tableSize;
		int songCount;
};
