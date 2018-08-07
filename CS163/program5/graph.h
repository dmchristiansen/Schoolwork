//graph.h
//class prototypes and struct definitions

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//holds info for each ride
class rideInfo {
	public:
		rideInfo();
		~rideInfo();
		int CreateEntry(char newName[], char newDesc[]);
		int CopyEntry(const rideInfo & toCopy);
		int Compare(rideInfo & toCompare);
		int DisplayName();
		int DisplayDescription();
	private:
		char * name;
		char * description;
};

//vertex info
struct vertex {
	rideInfo * ride;
	struct edge * head;
	int visitFlag;
};

//edge info
struct edge {
	vertex * adjacent;
	edge * next;
};

//node used for traversal between vertices
struct node {
	node * previous;
	node * next;
	vertex * step;
};

//class implementing graph data structure
class graph {
	public:
		graph();
		~graph();
		int Load();
		int AddVertex(int index, rideInfo & newVertex);
		int AddEdge(int from, int to);
		int DisplayRides();
		int DisplayPaths(int index);
		int FindRoute(int from, int to);
		int FindRoute(node *& cuurentStep, vertex *& currentVertex, int from, int to);
		int DisplayRoute(node *& head, int from, int to);
	private:
		vertex * rideList; //pointer to graph
		int rideCount;
		node * head; //pointer to DLL built when searching out a path between vertices
};


