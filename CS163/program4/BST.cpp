//BST.cpp
//public class functions for 'nominee' and 'BST' classes

#include "BST.h"

//nominee class functions

//constructor
nominee::nominee()
{
	name = NULL;
	movie = NULL;
	votes = 0;
}

//destructor
nominee::~nominee()
{
	if(name)
		delete name;
	if(movie)
		delete movie;
}

//copies information into object piece by piece
int nominee::CreateEntry(char newName[], char newMovie[], int newVotes)
{
	name = new char[strlen(newName)+1];
	strcpy(name, newName);
	movie = new char[strlen(newMovie)+1];
	strcpy(movie, newMovie);
	votes = newVotes;
}

//copies information into object from another object
int nominee::CopyEntry(const nominee & toAdd)
{
	name = new char[strlen(toAdd.name)+1];
	strcpy(name, toAdd.name);
	movie = new char[strlen(toAdd.movie)+1];
	strcpy(movie, toAdd.movie);
	votes = toAdd.votes;
}

//passes information back out
int nominee::Retrieve(char *& passName, char *& passMovie, int & passVotes)
{
	if(passName)
	{
		delete passName;
		passName = NULL;
	}
	passName = new char[strlen(name)+1];
	strcpy(passName, name);

	if(passMovie)
	{
		delete passMovie;
		passMovie = NULL;
	}
	passMovie = new char[strlen(movie)+1];
	strcpy(passMovie, movie);

	passVotes = votes;
}

//displays a single nominee object
int nominee::Display()
{
	cout << "\n\nName: " << name
		<< "\nMovie: " << movie
		<< "\nVotes: " << votes;
}

//returns the value of strcmp between name passed in and local name
int nominee::Compare(char compName[])
{
	return strcmp(compName, name);
}

//increments 'votes' count
int nominee::Vote()
{
	++votes;
	return 1;
}


//BST class functions

//constructor
BST::BST()
{
	root = NULL;
	category = NULL;
}

//destructor
BST::~BST()
{
	int count = 0;

	if(!root)
		return;

	count += Delete(root);	

	cout << "\n" << count << " nodes deleted.\n"; //for testing purposes
}

//recursive deallocation function, called by destructor
//returns the number of nodes deleted
int BST::Delete(node *& root) 
{
	int count = 0;

	if(!root)
		return 0;

	count += Delete(root->left);
	count += Delete(root->right);
	delete root;
	root = NULL;

	return count + 1;
}

//wrapper function for insertion.
int BST::Insert(char name[], const nominee & toAdd)
{
	if(Insert(root, name, toAdd))
		return 1;

	return 0;	
}

//recursive function for finding correct insertion spot.
int BST::Insert(node *& root, char name[], const nominee & toAdd)
{
	if(!root)
	{
		root = new node;
		root->left = NULL;
		root->right = NULL;
		root->nomination.CopyEntry(toAdd);
		return 1;
	}

	if(root->nomination.Compare(name) < 0)
		return Insert(root->left, name, toAdd);
	else
		return Insert(root->right, name, toAdd);

	return 0;	
}

//wrapper function fot removal
int BST::Remove(char name[])
{
	if(!root)
		return 0;

	if(Remove(root, name))
		return 1;

	return 0;
}

//recursive function for removal of a single node
//relies on several other functions
int BST::Remove(node *& root, char name[])
{
	if(!root)
		return 0;

	//if the name is less than current node, recurse left
	if(root->nomination.Compare(name) < 0)
	{
		return Remove(root->left, name);
	}
	//if the name is greater than current node, recurse right
	else if(root->nomination.Compare(name) > 0) 
	{
		return Remove(root->right, name);
	}
	//if the name matches, do the thing
	else
	{
		node * successor = FindSuccessor(root);
		if(successor)
		{
			successor->left = root->left;
			successor->right = root->right;
		}
		delete root;
		root = successor;	
		return 1;
	}
}

//function to determine how the successor will be found
node * BST::FindSuccessor(node *& root)
{
	//no children (node to be deleted is a leaf)
	if((!root->left) && (!root->right))
	{
		return NULL;
	}
	//left child only
	else if(root->left && (!root->right))
	{
		node * temp = root->left;
		root->left = NULL;
		return temp;	
	}
	//right child only
	else if((!root->left) && root->right)
	{
		node * temp = root->right;
		root->right = NULL;
		return temp;
	}
	//two children
	else
	{
		return FindInOrderSuccessor(root->right);
	}
}

//recursive function to find the inorder successor
node * BST::FindInOrderSuccessor(node *& root)
{
	//this function should never be passed a null pointer, but just in case...
	if(!root)
		return NULL;

	//if there's more left to go...
	if(root->left)
	{
		FindInOrderSuccessor(root->left);
	}
	//you can't go any further left...
	else if(!root->left)
	{
		node * temp = root;
		root = root->right;
		return temp;
	}
}

//takes in a pointer to root and a name to match, returns a pointer to matching element.
node *  BST::Find(node * root, char name[])
{
	if(!root)
		return NULL;

	if(!root->nomination.Compare(name))
	{
		return root;
	}
	else if(root->nomination.Compare(name) < 0)
	{
		return Find(root->left, name);
	}
	else if(root->nomination.Compare(name) > 0)
	{
		return Find(root->right, name);
	}
}

//searches by name, modifies movies and votes to pass back search results
//returns a 0 or 1 to indicate the success of the search
int BST::Search(char *& name, char *& movie, int & votes)
{
	//use 'Find' to find match
	node * result = Find(root, name);
	//if there was a match...
	if(result)
	{
		result->nomination.Retrieve(name, movie, votes);
		return 1;
	}

	//if there wasn't a match
	return 0;
}

//searches for a node, increments the 'votes' count if there's a match
int BST::Vote(char *& name, char *& movie, int & votes)
{
	//use 'Find' to find match
	node * result = Find(root, name);
	//if there was a match...
	if(result)
	{
		result->nomination.Vote();
		result->nomination.Retrieve(name, movie, votes);
		return 1;
	}

	//if there wasn;t a match
	return 0;	
}

//wrapper function for recursive DisplayAll()
int BST::DisplayAll()
{
	if(DisplayAll(root))
		return 1;

	return 0;	
}

//displays all nodes in the tree
int BST::DisplayAll(node * root)
{
	if(!root)
		return 0;

	DisplayAll(root->left);
	root->nomination.Display();
	DisplayAll(root->right);

	return 1;
}






