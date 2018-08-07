//BST.h
//class prototypes for 'nominee' and 'BST' classes

#include <iostream>
#include <cstring>
using namespace std;

class nominee {
	public:
		nominee();
		~nominee();
		int CreateEntry(char newName[], char newMovie[], int newVotes);
		int CopyEntry(const nominee & toAdd);
		int Retrieve(char *& passName, char *& passMovie, int & passVotes);
		int Display();
		int Compare(char compName[]);
		int Vote();
	private:
		char * name;
		char * movie;
		int votes;
};

struct node {
	nominee nomination;
	node * left;
	node * right;
};

class BST {
	public:
		BST();
		~BST();
		int Delete(node *& root);
		int Insert(char name[], const nominee & toAdd);
		int Insert(node *& root, char name[], const nominee & toAdd);
		int Remove(char name[]);
		int Remove(node *& root, char name[]);
		node * FindSuccessor(node *& root);
		node * FindInOrderSuccessor(node *& root);
		node * Find(node * root, char name[]);
		int Search(char *& name, char *& movie, int & votes);
		int Vote(char *& name, char *& movie, int & votes);
		int DisplayAll();
		int DisplayAll(node * root);
	private:
		node * root;
		char * category;
};
