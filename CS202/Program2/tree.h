/*
Daniel Christiansen
CS202
*/

//tree.h

#include "course.h"

class ListNode {
	public:
		ListNode();
		ListNode(Course *&);
		~ListNode();
		ListNode *& GetNext();
		void SetNext(ListNode *& pointer);
		void Display();
		void ReturnCredits(float &, float &, float &, float &);
	protected:
		ListNode * next;
		Course * courseObj;
};

//node objects contain a course object
class TreeNode {
	public:
		TreeNode();
		TreeNode(int term);
		TreeNode(const TreeNode &);
		~TreeNode();
		void AddNode(Course *&);
		int CompareTerm(int otherTerm);
		TreeNode *& GetLeft();
		TreeNode *& GetRight();
		bool GetFlag();
		void SetFlag(bool);
		void ToggleFlag();
		void Display();
		void GatherGPA(float &, float &, float &, float &);
	private:
		ListNode * head;
		TreeNode * left;
		TreeNode * right;
		bool black;
		int term; //the year/quarter this node represents
};

//the tree is used to manage nodes containing courses
class Tree {
	public:
		Tree();
		~Tree();
		void SetReqs(float, float);
		void Insert(Course *& newCourse, int quarter);
		bool Insert(Course *& newCourse, int quarter, TreeNode *& root, TreeNode *& parent, TreeNode *& grandparent, bool & RotateFlag);
		void DisplayAll();
		void DisplayAll(TreeNode  *&);
		void DisplayGPA();
		void GatherGPA(TreeNode *&, float &, float &, float &, float &);
		bool Balance(TreeNode *& root, TreeNode *& parent, TreeNode *& grandparent, bool & RotateFlag);
		void RotateLeft(TreeNode *& pivot);
		void RotateRight(TreeNode *& pivot);
	protected:
		TreeNode * root;
		float OverallGPA;
		float CoreGPA;
};



