/*
Daniel Christiansen
CS202
Program 3
*/

//graph.cpp
//'VertexNode', 'EdgeNode', and 'Graph' member functions

#include "graph.h"
/*	'EdgeNode' member functions	*/

//default constructor
EdgeNode::EdgeNode()
{
	next = NULL;
	adjacent = NULL;
}

//copy constructor
EdgeNode::EdgeNode(const EdgeNode& newEdge)
{
	next = NULL;
	adjacent = newEdge.adjacent;
}

//destructor
EdgeNode::~EdgeNode()
{
	//no dynamic memory...
}

//setter
void EdgeNode::SetNext(EdgeNode * pointer)
{
	next = pointer;	
}

//getter
EdgeNode *& EdgeNode::GetNext()
{
	return next;
}

//setter
void EdgeNode::SetAdjacent(VertexNode * pointer)
{
	adjacent = pointer;
}

//getter
VertexNode *& EdgeNode::GetAdjacent()
{
	return adjacent;
}

//compares genre with passed value
bool EdgeNode::CompareGenre(char *& compare)
{
	return adjacent->GenreCompare(compare);
}

/*	'VertexNode' member functions	*/

//default constructor
VertexNode::VertexNode()
{
	next = NULL;
	songList = NULL;
	edgeList = NULL;
	genre = NULL;
}

//destructor
VertexNode::~VertexNode()
{
	delete genre;
	
	//delete node's edge list
	EdgeNode * currentEdge = edgeList;
	EdgeNode * previousEdge = currentEdge;
	while(currentEdge)
	{
		currentEdge = currentEdge->GetNext();
		delete previousEdge;
		previousEdge = currentEdge;
	}

	//delete node's song list
	Node * currentSong = songList;
	Node * previousSong = currentSong;
	while(currentSong)
	{
		currentSong = currentSong->GetNext();
		delete previousSong;
		previousSong = currentSong;
	}
}

//setter
void VertexNode::SetGenre(char * newGenre)
{
	if(genre)
		delete genre;
	if(newGenre)
	{
		genre = new char[strlen(newGenre)+1];
		strcpy(genre, newGenre);
	} else {
		genre = NULL;
	}
}

//setter
void VertexNode::SetNext(VertexNode * pointer)
{
	next = pointer;
}

//getter
VertexNode *& VertexNode::GetNext()
{
	return next;
}

//getter
EdgeNode *& VertexNode::GetEdgeList()
{	
	return edgeList;
}

//getter
Node *& VertexNode::GetSongList()
{
	return songList;
}

//a function to compare the Vertex Node's genre against a value passed in
bool VertexNode::GenreCompare(char *& otherGenre)
{	
	if(!genre || !otherGenre || strcmp(genre, otherGenre))
		return false;
	else
		return true;
}

//+= operator overloaded for VertexNode += Song
VertexNode& VertexNode::operator +=(const Song& newSong)
{
	Node * newNode = new Node(newSong);
	newNode->SetNext(songList);
	songList = newNode;
	return *this;
}

//+= operator overloaded for VertexNode += EdgeNode
VertexNode& VertexNode::operator +=(const EdgeNode& newEdge)
{
	EdgeNode * newEdgeNode = new EdgeNode(newEdge);
	newEdgeNode->SetNext(edgeList);
	edgeList = newEdgeNode;
	return *this;
}

//looks through a vertex node's edge list for a match
bool VertexNode::FindEdgeNode(char *& genreMatch)
{
	EdgeNode * current = edgeList;
	while(current)
	{
		if(current->CompareGenre(genreMatch))
			return true;
		current = current->GetNext();
	}
	return false;
}

//<< operator overloaded for cout << VertexNode
ostream& operator <<(ostream& out, const VertexNode& vertex)
{
	out << "\nGenre: " << vertex.genre << endl;
	Node * current = vertex.songList;
	while(current)
	{
		out << *current;
		current = current->GetNext();
	}
	return out;
} 

/*	'Graph' member functions	*/

//default constructor
Graph::Graph()
{
	head = NULL;
	vertexCount = 0;
	songCount = 0;
}

//destructor
Graph::~Graph()
{
	VertexNode * current = head;
	VertexNode * previous = current;
	while(current)
	{
		current = current->GetNext();
		delete previous;
		previous = current;
	}	
}

//+= operator overloaded for Graph + Song
Graph& Graph::operator +=(const Song& newSong)
{
	//get the genre field and genre count through getters...
	int genreCount = newSong.GetGenreCount();
	char ** genres = newSong.GetGenres();

	//loop through the genres, checking if there is already a vertex node with a matching genre...
	for(int i = 0; i < genreCount; ++i)
	{
		//check if there is a matching genre node...
		VertexNode * targetNode = FindGenreNode(genres[i]);
		if(!targetNode) //if there isn't already a matching node, create one...
		{
			targetNode = new VertexNode;
			targetNode->SetGenre(genres[i]);
			targetNode->SetNext(head);
			head = targetNode;
			++vertexCount;
		}
		//add new song node to correct vertex node
		*targetNode += newSong;
	}

	//loop through genres, adding/connecting edge list nodes...
	for(int i = 0; i < genreCount; ++i)
	{
		//find the correct Vertex Node...
		VertexNode * currentVertexNode = FindGenreNode(genres[i]);
		//this node now needs to link up to every other genre node this song is associated with...
		for(int j = 0; j < genreCount; ++j)
		{
			//check if there is a matching edge node for that genre...
			if(i != j && currentVertexNode && !(currentVertexNode->FindEdgeNode(genres[i])))
			{
				VertexNode * targetNode = FindGenreNode(genres[j]);
				EdgeNode * newEdge = new EdgeNode;
				newEdge->SetAdjacent(targetNode);
				*currentVertexNode += *newEdge;
				delete newEdge;
			}
		}
	}
	++songCount;
	return *this;
}

//a function to check if a current genre is present in a LL of VertexNodes
//returns a vertex node pointer if it finds one matching the current genre, 
//returns a null pointer if there is no match
VertexNode* Graph::FindGenreNode(char * genre)
{
	VertexNode * currentNode = head;
	while(currentNode)
	{
		if(currentNode->GenreCompare(genre))
			return currentNode;
		currentNode = currentNode->GetNext();
	}
	return NULL; 
}

//<< operator overloaded for cout << Graph
ostream& operator <<(ostream& out, const Graph& Genre)
{
	VertexNode * current = Genre.head;
	while(current)
	{
		out << *current;
		current = current->GetNext();
	} 
	return out;
}

//function that returns a random node based on genre...
Node& Graph::RandomJump(const Node& currentNode)
{
	//gets genre list for current song and randomly selects one...
	char ** genres = currentNode.GetGenres();
	int genreCount = currentNode.GetGenreCount();
	char * selectGenre = genres[rand() % genreCount];
	//finds the node that corresponds to that genre...
	VertexNode * currentVertex = FindGenreNode(selectGenre);
	//then randomly selects another vertex that it is connected to...
	int moves = (rand() % songCount);
	EdgeNode * currentEdge = currentVertex->GetEdgeList();
	for(int i = 0; i < moves; ++i)
	{
		if(!currentEdge)
			currentEdge = currentVertex->GetEdgeList();
		else
			currentEdge = currentEdge->GetNext();
	}
	//then randomly selects a song in that node's song list...
	moves = (rand() % songCount);
	if(currentEdge)
		currentVertex = currentEdge->GetAdjacent();
	else
		currentVertex = currentVertex->GetEdgeList()->GetAdjacent();

	Node * currentSong = currentVertex->GetSongList();
	for(int i = 0; i < moves; ++i)
	{
		if(!currentSong)
			currentSong = currentVertex->GetSongList();
		else
			currentSong = currentSong->GetNext();
	}
	//then returns it.
	if(currentSong)
		return *currentSong;
	else
		return *(currentVertex->GetSongList());
}

