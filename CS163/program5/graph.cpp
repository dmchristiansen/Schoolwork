//graph.cpp
//member functions for 'rideInfo' and 'graph' classes

#include "graph.h"

//rideInfo class functions

//rideInfo constructor
rideInfo::rideInfo()
{
	name = NULL;
	description = NULL;
}

//rideInfo destructor
rideInfo::~rideInfo()
{
	if(name)
		delete [] name;
	if(description)
		delete [] description;	
}

//adds information to a rideInfo object.
//clears out previous values if there are any.
int rideInfo::CreateEntry(char newName[], char newDesc[])
{
	if(name)
		delete name;
	name = new char[strlen(newName)+1];
	strcpy(name, newName);

	if(description)
		delete description;
	description = new char[strlen(newDesc)+1];
	strcpy(description, newDesc);

	return 1;
}

//copies info from one rideInfo object to another
int rideInfo::CopyEntry(const rideInfo & toCopy)
{
	name = new char[strlen(toCopy.name)+1];
	strcpy(name, toCopy.name);

	description = new char[strlen(toCopy.description)+1];
	strcpy(description, toCopy.description);

	return 1;
}
//compares the name field from two rideInfo objects.
//returns 1 if they match, otherwise 0
int rideInfo::Compare(rideInfo & toCompare)
{
	if(!strcmp(toCompare.name, name))
		return 1;

	return 0;
}

//displays name field
int rideInfo::DisplayName()
{
	cout << name;
	return 1;
}

//displays description field
int rideInfo::DisplayDescription()
{
	cout << description;
	return 1;
}

//graph class functions

//graph constructot
graph::graph()
{
	rideList = NULL;
	rideCount = 0;
	head = NULL;
}

//graph destructor
graph::~graph()
{
	edge * previous = NULL;
	edge * current = NULL;

	//goes through the array of vertex nodes...
	for(int i = 0; i < rideCount; ++i)
	{
		//deleting the list of edge nodes attached to each one..
		current = rideList[i].head;
		previous = current;
		while(current)
		{
			current = current->next;
			delete previous;
			previous = current;
		}
		//then deleting the ride info from that vertex...
		delete rideList[i].ride;
	}

	//and finally deleting the array of vertices.
	delete [] rideList;
}

//loads graph information from the file 'data.txt'
int graph::Load()
{
	//the format of the file is as follows:
	//the first line is the number of vertices
	//for each vertex, there is a name line, a description line, 
	//then a line with the number of edges.
	//each line after that is an index value that an edge is pointing to.
	
	char name[100], description[100];
	int edgeCount, adjacentVertex, i, j;
	rideInfo newVertex;

	//attempts to open file, checks for success
	ifstream infile;
	infile.open("data.txt");

	if(!infile)
		return 0;

	//gets list size from file, creates vertex array.
	infile >> rideCount;
	infile.ignore(100, '\n');
	rideList = new vertex[rideCount];

	//populates vertex array
	i = 0;
	infile.getline(name, 100, '\n');
	while(!infile.eof())
	{
		infile.getline(description, 100, '\n');
		newVertex.CreateEntry(name, description);
		AddVertex(i, newVertex);
		infile >> edgeCount;
		infile.ignore(100, '\n');
		for(j = 0; j < edgeCount; ++j)
		{
			infile >> adjacentVertex;
			infile.ignore(100, '\n');
			AddEdge(i, adjacentVertex);
		}
		++i;
		infile.getline(name, 100, '\n');
	}

	//close file, return success
	infile.close();
	return 1;
}

//adds vertex information to a vertex node
int graph::AddVertex(int index, rideInfo & newVertex)
{
	rideList[index].ride = new rideInfo;
	rideList[index].ride->CopyEntry(newVertex);
	rideList[index].visitFlag = 0;
	rideList[index].head = NULL;	
	return 1;
}

//adds am edhe node to the list of a vertex
int graph::AddEdge(int from, int to)
{
	edge * temp = new edge;
	temp->next = rideList[from].head;
	temp->adjacent = &rideList[to];
	rideList[from].head = temp;
	return 1;
}

//cycles through the rideList array, displaying information for each vertex
int graph::DisplayRides()
{
	//if rideList hasn't been initialized...
	if(!rideList)
		return 0;

	cout << "\nThere are " << rideCount << " ride(s).\n";

	for(int i = 0; i < rideCount; ++i)
	{
		cout << "\nRide number " << i + 1 << ": ";
		rideList[i].ride->DisplayName();
		cout << endl;
		rideList[i].ride->DisplayDescription();
		cout << endl;
		//DisplayPaths(i);
	}
	return 1;
}

//displays all edges for a vertex
int graph::DisplayPaths(int index)
{
	//checks for valid input...
	if(!rideList || index < 0 || index >= rideCount)
		return 0;

	edge * current = rideList[index].head;

	cout << "\nThe following rides are adjacent to ";
	rideList[index].ride->DisplayName();
	cout << ":\n";

	//traversing edge list...
	while(current)
	{
		current->adjacent->ride->DisplayName();
		cout << endl;
		current = current->next;
	}

	return 1;
}

//wrapper function for recursive DFS function
//this function and the one it calls assemble a DLL of vertices representing the route
int graph::FindRoute(int from, int to)
{
	//checks for valid input
	if(from < 0 || to < 0 || from == to)
		return 0;

	//reset all visit flags
	for(int i = 0; i < rideCount; ++i)
		rideList[i].visitFlag = 0;

	//add starting vertex to list
	vertex * temp = &rideList[from];
	head = new node;
	head->next = NULL;
	head->previous = NULL;
	head->step = temp;

	//calls recursive function, evaluates success...
	if(FindRoute(head, temp, from, to))
	{
		//displays path, deallocated path list, reports success
		DisplayRoute(head, from, to);
		node * current = head;
		node * prev = current;
		while(current)
		{
			current = current->next;
			delete prev;
			prev = current;
		}
		return 1;
	} else {
		//deletes remaining node and report failure
		if(head)
			delete head;
		head = NULL;
		return 0;
	}
}

//recursive function that loops through a vertex's edge list, calling itself
//with each vertex pointed to by that edge in turn, evaluating if it needs to back, forward,
//or if it's found the vertex it's looking for.
//it builds a DLL as it goes, adding a node before calling itself again, and removing if that
//path was a failure.
int graph::FindRoute(node *& currentStep, vertex *& currentVertex, int from, int to)
{	
	//test if the vertex has already been visited
	if(currentVertex->visitFlag)
	{		
		return 0;
	}

	//if this vertex is the destination (to), return '1'
	if(currentVertex->ride->Compare(*(rideList[to].ride)))
	{
		return 1;
	}
	
	//mark vertex as visited
	currentVertex->visitFlag = 1;

	//traverse through edge list, calling this function for each edge.
	//if the function returns false, remove the node that it added to the step list
	//and move to the next item.
	//if it returns true, return '1' and end recursion.
	edge * currentEdge = currentVertex->head;
	while(currentEdge)
	{
		//add new node before recursive call with the next vertex
		node * temp = new node;
		temp->next = NULL;
		temp->previous = currentStep;
		currentStep->next = temp;
		temp->step = currentEdge->adjacent;
		if(FindRoute(temp, currentEdge->adjacent, from, to))
		{
			//if there was a success somewhere down the chain of recursion, return.
			return 1;
		} else {
			//delete the node that the call that just resolved created...
			delete currentStep->next;
			currentStep->next = NULL;
			currentEdge = currentEdge->next;
		}
	}
	
	//if the function hasn't found the end by now, there isn't a path through.
	return 0;
}

//display DLL created by 'FindRoute; functions
int graph::DisplayRoute(node *& head, int from, int to)
{
	node * current = head;

	cout << "\nA route from ";
	rideList[from].ride->DisplayName();
	cout << " to ";
	rideList[to].ride->DisplayName();
	cout << " is:\n";

	while(current)
	{
		current->step->ride->DisplayName();
		cout << endl;
		current = current->next;
	}
	return 1;
}
