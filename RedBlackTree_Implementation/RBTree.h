#include <iostream>
#include <vector>
#include <limits>
#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

typedef enum Color {
	Red = 0,
	Black
};

typedef struct node{
	int color;
	int Id;
	int count;
	node *left;
	node *right;
	node *parent;
	node(int Id, int count){
		this->Id = Id;
		this->count = count;
		color = Color::Red;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
} _node;

typedef struct i_event{
	int Id;
	int count;
	i_event(int Id, int count){
		this->Id = Id;
		this->count = count;
	}
} _i_event;
extern node *root;
class RBTree
{
public:
	RBTree();
	virtual ~RBTree();
	node* addNewNode(int, int);
	node* initializeSubTrees(vector<i_event>&, node *);
	void initializeTree(vector<i_event> &);
	void insertEvent(int, int);
	node* getGrandParent(node*);
	node* getSibbling(node *);
	node* getUncle(node *);
	void deleteEvent(node *);
	int Reduce(int, int);
	int Increase(int, int);
	int getNodeColor(node*);
	int Count(int);
	int InRange(int, int);
	void InRangeSub(node *, int, int, int*);
	node* Next(int);
	node* Previous(int);
	void rotateLeft(node*);
	void rotateRight(node*);
	void replaceNode(node*, node*);
	void insertFix(node *);
	void insertFix_twoReds(node *);
	void delete_colorFix(node*);
	void delete_blackFix(node *);
	void delete_red_blackFix(node *);
	void delete_red_blackFix_other(node *);
	void delete_blackFix_other(node *);
	node* getMaxOnRight(node*);
	void insertFix_rotation(node *);
	void insert_color_rotation(node *);
};

extern vector<i_event> getInput(char*);

extern void getCommands(RBTree*, char*, char*);

extern int executeCommand(RBTree*, ofstream&, string, int, int);

extern void startUserMode(RBTree*);