/*
Daniel Christiansen
CS202
Program 2
*/

//tree.cpp

#include "tree.h"

/*	ListTreeNode member functions	*/

//default constructor
ListNode::ListNode()
{
	next = NULL;
	courseObj = NULL;
}

ListNode::ListNode(Course *& newCourse)
{
	next = NULL;
	courseObj = newCourse;
}

ListNode::~ListNode()
{
	delete courseObj;
	next = NULL;
}

ListNode *& ListNode::GetNext()
{
	return next;
}

void ListNode::SetNext(ListNode *& pointer)
{
	next = pointer;
}

//List Node display function
void ListNode::Display()
{
	courseObj->Display();
}

/*	TreeTreeNode member functions	*/

//default constructor
TreeNode::TreeNode()
{
	left = NULL;
	right = NULL;
	head = NULL;
	term = 0;
	black = false;
}

//constructor w/ term
TreeNode::TreeNode(int term)
{
	left = NULL;
	right = NULL;
	head = NULL;
	this->term = term;
	black = false; //set to red upon creation
}

//copy constructor
TreeNode::TreeNode(const TreeNode &)
{

}

//destructor
//note that this dtor will delete any node that is is holding on to
TreeNode::~TreeNode()
{
	if(left)
		delete left;
	if(right)
		delete right;
	
	ListNode * current = head;
	ListNode * previous = current;
	while(current)
	{
		current = current->GetNext();
		if(previous)
			delete previous;
		previous = current;
	}
}

//function to add a ListNode to a TreeNode's list
void TreeNode::AddNode(Course *& newCourse)
{
	ListNode * temp = new ListNode(newCourse);
	temp->SetNext(head);
	head = temp;
}

//compares node's term value against value passed in.
//if the value passed in is less, it returns a negative value
//if they match, returns zero
//if the value passed in is greater, it returns a positive value
int TreeNode::CompareTerm(int otherTerm)
{
	return otherTerm - term;
}

//getter
TreeNode *& TreeNode::GetLeft()
{
	return left;
}

//getter
TreeNode *& TreeNode::GetRight()
{
	return right;
}

//getter
bool TreeNode::GetFlag()
{
	return black;
}

//sets red/black flag
void TreeNode::SetFlag(bool flag)
{
	black = flag;
}

//toggles flag
void TreeNode::ToggleFlag()
{
	if(black)
		black = false;
	else
		black = true;
}


//Tree node display function
void TreeNode::Display()
{
	ListNode * current = head;

	if(term)
	{
		cout << "\n- Courses taken during the term "
			<< (term/10) << "/" << (term%10) << " -\n";
	} else {
		cout << "\n- Courses not yet taken -\n";
	}
	while(current)
	{
		cout << endl;
		current->Display();
		current = current->GetNext();
	}
}


//the tree is used to manage nodes containing courses
/*	Tree member functions	*/

//default constructor
Tree::Tree()
{
	root = NULL;
	OverallGPA = 0;
	CoreGPA = 0;
}

//destructor
Tree::~Tree()
{
	if(!root)
		return;

	if(root->GetLeft())
		delete root->GetLeft();

	if(root->GetRight())
		delete root->GetRight();

	delete root;
}

//function to set the GPA requirements
void Tree::SetReqs(float overall, float core)
{
	OverallGPA = overall;
	CoreGPA = core;
}

//wrapper function for insertion
void Tree::Insert(Course *& newCourse, int quarter)
{
	bool RotateFlag = false;
	TreeNode * nullPointer = NULL;
	Insert(newCourse, quarter, root, nullPointer, nullPointer, RotateFlag);
}

//recursive function for insertion
bool Tree::Insert(Course *& newCourse, int quarter, TreeNode *& root, TreeNode *& parent, TreeNode *& grandparent, bool & RotateFlag)
{
	bool balanceFlag = false;
	
	//BST insertion algotihm
	if(!root) {
		root = new TreeNode(quarter);
		root->AddNode(newCourse);
	} else if(!root->CompareTerm(quarter)) {
		root->AddNode(newCourse);
		cout << endl << "insert" << endl;
		return true;
	} else if(root->CompareTerm(quarter) < 0) {
		balanceFlag = Insert(newCourse, quarter, root->GetLeft(), root, parent, RotateFlag);
	} else if(root->CompareTerm(quarter) > 0) {
		balanceFlag = Insert(newCourse, quarter, root->GetRight(), root, parent, RotateFlag);
	}

	//if we know that the tree is already balanced
	if(balanceFlag)
		return true;

	//check tree's state and balance if neccesary upon the return
	return Balance(root, parent, grandparent, RotateFlag);
}

//function to check the tree state and modify as needed
bool Tree::Balance(TreeNode *& root, TreeNode *& parent, TreeNode *& grandparent, bool & RotateFlag)
{
	//if the rotation flag is set, then there is a request to rotate from one level below...
	if(RotateFlag)
	{
		root->ToggleFlag();
		parent->ToggleFlag();
		if(root->GetLeft() && !root->GetLeft()->GetFlag())
		{
			RotateRight(parent);
		} 
		else if (root->GetRight() && !root->GetRight()->GetFlag())
		{
			RotateLeft(parent);
		}
		RotateFlag = false;
		return true;
	}

	//case 1 - The node is the root of the whole tree
	//solution - paint node black
	if(!parent) 
	{
		root->SetFlag(true);
		return true;
	}
	
	//case 2 - The node's parent is black
	//solution - there is no problem to solve.  
	//There might be a problem durther up, though.
	if(parent->GetFlag())
	{
		return false;
	}

	//case 3 - both parent and 'uncle' are red nodes
	//solution - swap color of parent, grandparent, and uncle.
	//either solves problem, or pushes it up two generations.
	if((grandparent && grandparent->GetRight() && !grandparent->GetRight()->GetFlag()) 
	&& (grandparent && grandparent->GetLeft() && !grandparent->GetLeft()->GetFlag()))
	{
		grandparent->SetFlag(false); //paint grandparent red
		grandparent->GetLeft()->SetFlag(true); //paint parent/uncle black
		grandparent->GetRight()->SetFlag(true);
		return false;
	}

	//case 4 - If the node's parent is red, but the 'uncle' is black,
	//and the current node is the same direction as its uncle
	//(it's a right node of its parent, the uncle is a right node of the grandparent, or the reverse)
	//solution - rotate either right or left to refuce it to case 5.
	//this is broken into two mirror cases.
	if(grandparent && (grandparent->GetLeft() == parent) && (parent->GetRight() == root))
	{
		RotateLeft(parent);
		RotateFlag = true;
		return false;	
	}
	if(grandparent && (grandparent->GetRight() == parent) && (parent->GetLeft() == root))
	{
		RotateRight(parent);
		RotateFlag = true;
		return false;
	}

	//case 5 - If the node's parent is red, but the 'uncle' is black,
	//and the current node is the opposite direction as its uncle
	//(it's a left node of its parent, and the uncle is the right node of the grandparent, or the reverse)
	//solution - set the rotation flag to let the previous frame deal with the problem
	if((grandparent && (grandparent->GetLeft() == parent) && (parent->GetLeft() == root)) 
	||(grandparent && (grandparent->GetRight() == parent) && (parent->GetRight() == root)))
	{
		RotateFlag = true;
		return false;
	}
}



//function for left rotation
//takes a pointer to the pivot node
void Tree::RotateLeft(TreeNode *& pivot)
{
	if(!pivot->GetRight()) //if the right pointer is null, you can't rotate left...
		return;
	TreeNode * NewRoot = pivot->GetRight();
	TreeNode * SubTree = NewRoot->GetLeft();
	NewRoot->GetLeft() = pivot;
	pivot->GetRight() = SubTree;
	pivot = NewRoot;
}

//function for right rotation
//takes a pointer to the pivot node
void Tree::RotateRight(TreeNode *& pivot)
{
	if(!pivot->GetLeft()) //if the left pointer is null, you can't rotate right...
		return;
	TreeNode * NewRoot = pivot->GetLeft();
	TreeNode * SubTree = NewRoot->GetRight();
	NewRoot->GetRight() = pivot;
	pivot->GetLeft() = SubTree;
	pivot = NewRoot;
}

//wrapper function for display function	
void Tree::DisplayAll()
{
	DisplayAll(root);
}

void Tree::DisplayAll(TreeNode *& root)
{
	if(!root)
		return;
	DisplayAll(root->GetLeft());
	root->Display();
	DisplayAll(root->GetRight());
}

void Tree::DisplayGPA()
{
	float earnedCore, earnedOverall;
	float attemptedCore, attemptedOverall;
	GatherGPA(root, earnedCore, attemptedCore, earnedOverall, attemptedOverall);
	cout << "\nThe overall GPA is " << earnedOverall/attemptedOverall 
		<< " ( " << earnedOverall << "/" << attemptedOverall << ")";
	cout << "\nThe GPA for core classes is " << earnedCore/attemptedCore
		<< " ( " << earnedCore << "/" << attemptedCore << ")";
}

//function to calculate and display the average of the core/overall GPAs
void Tree::GatherGPA(TreeNode *& root, float & earnedCore, float & attemptedCore, float & earnedOverall, float & attemptedOverall)
{
	if(!root)
		return;

	GatherGPA(root->GetLeft(), earnedCore, attemptedCore, earnedOverall, attemptedOverall);
	root->GatherGPA(earnedCore, attemptedCore, earnedOverall, attemptedOverall);
	GatherGPA(root->GetRight(), earnedCore, attemptedCore, earnedOverall, attemptedOverall);
}


//function to gather all the GPA related info from a node's list
void TreeNode::GatherGPA(float & earnedCore, float & attemptedCore, float & earnedOverall, float & attemptedOverall)
{
	ListNode * current = head;
	while(current)
	{
		current->ReturnCredits(earnedCore, attemptedCore, earnedOverall, attemptedOverall);
		current = current->GetNext();
	}
}

//function to gather GPA info from object contained by node
void ListNode::ReturnCredits(float & earnedCore, float & attemptedCore, float & earnedOverall, float & attemptedOverall)
{
		courseObj->ReturnCredits(earnedOverall, attemptedOverall);
		courseObj->ReturnCoreCredits(earnedCore, attemptedCore);
}
