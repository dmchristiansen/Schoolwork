/*
Daniel Christiansen
CS202
Program 3
*/

//graph.h
//'VertexNode', 'EdgeNode', and 'Graph' class prototypes

#include "table.h"

class EdgeNode {
	public:
		EdgeNode();
		EdgeNode(const EdgeNode&);
		~EdgeNode();
		void SetNext(EdgeNode *);
		EdgeNode *& GetNext();
		void SetAdjacent(class VertexNode *);
		class VertexNode *& GetAdjacent();
		bool CompareGenre(char *&);
		VertexNode& operator [](int index);
	protected:
		EdgeNode * next;
		class VertexNode * adjacent;
};


class VertexNode {
	public:
		VertexNode();
		~VertexNode();
		VertexNode& operator +=(const Song&);
		VertexNode& operator +=(const EdgeNode&);
		void SetGenre(char *);
		void SetNext(VertexNode *);
		VertexNode *& GetNext();
		EdgeNode *& GetEdgeList();
		Node *& GetSongList();
		bool GenreCompare(char *&);
		bool FindEdgeNode(char *&);
		friend ostream& operator <<(ostream&, const VertexNode&);
		Node& operator [](int index);
	protected:
		VertexNode * next;
		EdgeNode * edgeList;
		Node * songList;
		char * genre;
};

class Graph {
	public:
		Graph();
		~Graph();
		Graph& operator +=(const Song&);	
		VertexNode * FindGenreNode(char *);
		friend ostream& operator <<(ostream&, const Graph&);
		Node& RandomJump(const Node&);
	protected:
		VertexNode * head;
		int vertexCount;
		int songCount;
};

