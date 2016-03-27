#include "RBTree.h"

node *root;
vector<i_event> getInput(char* inputFileName){
	vector<i_event> input;
	ifstream iFile(inputFileName);
	string line;
	getline(iFile, line);
	int value = atoi(line.c_str());
	for (int i = 0; i < value; i++){
		std::getline(iFile, line);
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b)) {
			cout << "The Input Format Error In the Input File";
			break;
		}
		input.push_back(i_event(a, b));
	}
	iFile.close();
	return input;
}

void startUserMode(RBTree *obj){
	cout << "1. Increase the ID" << endl;
	cout << "2. Reduce the ID" << endl;
	cout << "3. Get Count of the ID" << endl;
	cout << "4. Get Count InRange" << endl;
	cout << "5. Get Next Event of ID" << endl;
	cout << "6. Get Previous Event of ID" << endl;
	cout << "7. Quit" << endl;
	bool toContinue = true;
	while (toContinue){
		int ch = -1;
		int a = 0, b = 0;
		cout << "Enter the Operation Number" << endl;
		cin >> ch;
		switch (ch)
		{
			case 1:{
				cout << "Enter ID & m" << endl;
				cin >> a >> b;
				cout << obj->Increase(a, b) << endl;
			}
			   break;
			case 2:{
				cout << "Enter ID & m" << endl;
				cin >> a >> b;
				cout << obj->Reduce(a, b) << endl;
			}
				break;
			case 3:{
				cout << "Enter the ID" << endl;
				cin >> a;
				cout << obj->Count(a) << endl;
			}
				break;
			case 4:{
				cout << "Enter the Range for InRange" << endl;
				cin >> a >> b;
				cout << obj->InRange(a, b);
			}
				break;
			case 5:{
				cout << "Enter the ID for Next" << endl;
				cin >> a;
				node* res = obj->Next(a);
				if (res != NULL)
					cout << res->Id << " " << res->count << endl;
				else
					cout << 0 << " " << 0 << endl;
			}
				break;
			case 6:{
				cout << "Enter the ID for Next" << endl;
				cin >> a;
				node* res = obj->Previous(a);
				if (res != NULL)
					cout << res->Id << " " << res->count << endl;
				else
					cout << 0 << " " << 0 << endl;
			}
				break;
			case 7:{
				toContinue = false;
			}
				break;
		default:
			cout << "Wrong Operation Asked For" << endl;
			break;
		}
	}
}
void getCommands(RBTree* obj, char *commandFile, char* outputFile){
	ifstream iFile(commandFile);
	ofstream oFile;
	remove(outputFile);
	oFile.open(outputFile, std::ofstream::out | std::ofstream::app);
	string line;
	string command; int a, b;
	int result = 0;
	while (getline(iFile, line)){
		istringstream iss(line);
		iss >> command >> a >> b;
		executeCommand(obj, oFile, command, a, b);
		a = 0, b = 0;
	}
	oFile.close();
	iFile.close();
}

int executeCommand(RBTree *obj, ofstream& oFile, string command, int a, int b){
	if (command == "increase"){
		oFile << obj->Increase(a, b);
		oFile << "\n";
	}
	if (command == "reduce"){
		oFile << obj->Reduce(a, b);
		oFile << "\n";
	}
	if (command == "count"){
		oFile << obj->Count(a);
		oFile << "\n";
	}
	if (command == "inrange"){
		oFile << obj->InRange(a, b);
		oFile << "\n";
	}
	if (command == "next"){
		node* res = obj->Next(a);
		if (res == NULL){
			oFile << 0;
			oFile << " ";
			oFile << 0;
		}
		else{
			oFile << res->Id;
			oFile << " ";
			oFile << res->count;
		}
		oFile << "\n";
	}
	if (command == "previous"){
		node *res = obj->Previous(a);
		if (res == NULL){
			oFile << 0;
			oFile << " ";
			oFile << 0;
		}
		else{
			oFile << res->Id;
			oFile << " ";
			oFile << res->count;
		}
		oFile << "\n";
	}
	if (command == "quit")
		return 0;
	return 0;
}

RBTree::RBTree()
{
	// Read Events from the file
}


RBTree::~RBTree()
{

}

node* RBTree::addNewNode(int Id, int count){
	node* newNode = new node(Id, count);
	return newNode;
}

node* RBTree::initializeSubTrees(vector<i_event>& input_array, node *parent){
	if (input_array.size() == 0)
		return NULL;
	if (input_array.size() == 1){
		node *newNode = addNewNode(input_array[0].Id, input_array[0].count);
		newNode->parent = parent;
		if (parent->color == Color::Red)
			newNode->color = Color::Black;
		return newNode;
	}
	int mid = (input_array.size() - 1) / 2;
	node *newNode = new node(input_array[mid].Id, input_array[mid].count);
	newNode->parent = parent;
	if (parent->color == Color::Red)
		newNode->color = Color::Black;
	vector<i_event> leftArray = vector<i_event>(input_array.begin(), input_array.begin() + mid);
	vector<i_event> rightArray = vector<i_event>(input_array.begin() + mid + 1, input_array.end());
	newNode->left = initializeSubTrees(leftArray, newNode);
	newNode->right = initializeSubTrees(rightArray, newNode);
	return newNode;
}

void RBTree::initializeTree(vector<i_event>& input_array){
	if (input_array.size() == 0 || root != NULL)
		return;
	int mid = (input_array.size() - 1) / 2;
	i_event root_event = input_array[mid];
	root = addNewNode(root_event.Id, root_event.count);
	root->parent = NULL;
	root->color = Color::Black;
	vector<i_event> leftArray = vector<i_event>(input_array.begin(), input_array.begin() + mid);
	vector<i_event> rightArray = vector<i_event>(input_array.begin() + mid + 1, input_array.end());
	root->left = initializeSubTrees(leftArray, root);
	root->right = initializeSubTrees(rightArray, root);
}

int RBTree::Increase(int ID, int m){
	node *n = root;
	int result = 0;
	while (n != NULL)
	{
		if (n->Id == ID){
			n->count += m;
			cout << "The Match Found" << n->count << endl;
			result = n->count;
			break;
		}
		else if(ID < n->Id){
			n = n->left;
		}
		else{
			n = n->right;
		}
		if (n == NULL){
			cout << " The ID not found" << endl;
			insertEvent(ID, m);
			result = m ;
			break;
		}
	}
	return result;
}

void RBTree::insertEvent(int ID, int m){
	node* newNode = new node(ID, m);
	if (root == NULL)
		root = newNode;
	else{
		node* n = root;
		while (true){
			if (n->Id == ID){
				cout << "The Node already Exists With the Node" << endl;
				delete newNode;
				return;
			}
			else if(ID < n->Id){
				if (n->left == NULL){
					n->left = newNode;
					break;
				}
				else
					n = n->left;
			}
			else{
				if (n->right == NULL){
					n->right = newNode;
					break;
				}
				else
					n = n->right;
			}
		}
		newNode->parent = n;
	}
	insertFix(newNode);
}

void RBTree::insertFix(node *n){
	if (n->parent == NULL)		//The Node inserted is the root Node
		n->color = Color::Black;
	else
		insertFix_twoReds(n);
}

void RBTree::insertFix_twoReds(node *n){
	if (n->parent->color == Color::Black)
		return;
	else{
		// Check the Uncle's node Color.
		// If the Uncle Node color is Red, then parent and uncle can be made Black and grandparent can be made Red.
		// This will preserve the Property 2 & 3
		if (getUncle(n)->color == Color::Red){
			n->parent->color = Color::Black;
			getUncle(n)->color = Color::Black;
			getGrandParent(n)->color = Color::Red;
			insertFix(getGrandParent(n));
		}
		else{
			// Rotation Needs to be done in order to Fix the tree
			insertFix_rotation(n);
		}
	}
}

void RBTree::insertFix_rotation(node *n){
	// Node n is a right child of the left child of its grandparent
	if (n == n->parent->right && n->parent == getGrandParent(n)->left) {
		rotateLeft(n->parent);
		n = n->left;
	}

	// Node n is a left child of the right child of its grandparent
	else if (n == n->parent->left && n->parent == getGrandParent(n)->right) {
		rotateRight(n->parent);
		n = n->right;
	}
	insert_color_rotation(n);
}

void RBTree::insert_color_rotation(node* n){
	n->parent->color = Color::Black;
	getGrandParent(n)->color = Color::Red;
	if (n == n->parent->left && n->parent == getGrandParent(n)->left) {
		rotateRight(getGrandParent(n));
	}
	else if (n == n->parent->right && n->parent == getGrandParent(n)->right) {
		rotateLeft(getGrandParent(n));
	}
}

int RBTree::Reduce(int ID, int m){
	node *n = root;
	int result = 0;
	while (n != NULL){
		if (n->Id == ID){
			n->count -= m;
			if (n->count <= 0){
				cout << "The count has been reduced to 0" << endl;
				deleteEvent(n);
				result = 0;
				break;
			}
			result = n->count;
			break;
		}
		else if (ID < n->Id)
			n = n->left;
		else
			n = n->right;
		if (n == NULL)
			cout << " The Event with ID not found" << endl;
	}
	return result;
}

node* RBTree::getMaxOnRight(node *n){
	if (n == NULL)
		return NULL;
	while (n->right != NULL)
		n = n->right;
	return n;
}
void RBTree::deleteEvent(node* n){
	node* ch;
	if (n == NULL)
		return;
	if (n->left != NULL && n->right != NULL) {
		node* pred = getMaxOnRight(n->left);
		n->Id = pred->Id;
		n = pred;
	}
	assert(n->left == NULL || n->right == NULL);
	ch = n->right == NULL ? n->left : n->right;
	if (n->color == Color::Black) {
		n->color = ch->color;
		delete_colorFix( n);
	}
	replaceNode(n, ch);
	if (n->parent == NULL && ch != NULL)
		ch->color = Color::Black;
	delete n;
	n = NULL;
}

void RBTree::delete_colorFix(node* n){
	if (n->parent == NULL)
		return;
	else{
		if (getNodeColor(getSibbling(n)) == Color::Red) {
			n->parent->color = Color::Red;
			getSibbling(n)->color = Color::Black;
			if (n == n->parent->left)
				rotateLeft(n->parent);
			else
				rotateRight(n->parent);
		}
		delete_blackFix(n);
	}
}

void RBTree::delete_blackFix(node *n){
	// All the parents, childs and its sibblings are black
	if (getNodeColor(n->parent)== Color::Black &&
		getNodeColor(getSibbling(n)) == Color::Black &&
		getNodeColor(getSibbling(n)->left) == Color::Black &&
		getNodeColor(getSibbling(n)->right) == Color::Black)
	{
		getSibbling(n)->color = Color::Red;
		delete_colorFix(n->parent);
	}
	else
		delete_red_blackFix(n);
}

void RBTree::delete_red_blackFix(node* n){
	// Parent is Red and Sibbling of node and both the childs of Sibblings is Black
	if (getNodeColor(n->parent) == Color::Red &&
		getNodeColor(getSibbling(n)) == Color::Black &&
		getNodeColor(getSibbling(n)->left) == Color::Black &&
		getNodeColor(getSibbling(n)->right) == Color::Black)
	{
		getSibbling(n)->color = Color::Red;
		n->parent->color = Color::Black;
	}
	else
		delete_red_blackFix_other(n);
}

void RBTree::delete_red_blackFix_other(node *n){
	// The node is either to left of its parent and have black sibbling with Red and Black Child
	//								OR
	//The node is either to right of its parent and have black sibbling with Red and Black Child
	if (n == n->parent->left &&
		getNodeColor(getSibbling(n)) == Color::Black &&
		getNodeColor(getSibbling(n)->left) == Color::Red &&
		getNodeColor(getSibbling(n)->right) == Color::Black)
	{
		getSibbling(n)->color = Color::Red;
		getSibbling(n)->left->color = Color::Black;
		rotateRight(getSibbling(n));
	}
	else if (n == n->parent->right &&
		getNodeColor(getSibbling(n)) == Color::Black &&
		getNodeColor(getSibbling(n)->right) == Color::Red &&
		getNodeColor(getSibbling(n)->left)== Color::Black)
	{
		getSibbling(n)->color = Color::Red;
		getSibbling(n)->right->color = Color::Black;
		rotateLeft(getSibbling(n));
	}
	delete_blackFix_other(n);
}

void RBTree::delete_blackFix_other(node *n){
	getSibbling(n)->color = n->parent->color;
	n->parent->color = Color::Black;
	if (n == n->parent->left) {
		if (getNodeColor(getSibbling(n)->right) != Color::Red)
			return;
		getSibbling(n)->right->color = Color::Black;
		rotateLeft(n->parent);
	}
	else
	{
		if (getNodeColor(getSibbling(n)->left) != Color::Red)
			return;
		getSibbling(n)->left->color = Color::Black;
		rotateRight(n->parent);
	}
}

node* RBTree::getGrandParent(node* n){
	if (n == NULL)
		return NULL;
	if (n->parent == NULL)
		return NULL;
	if (n->parent->parent == NULL)
		return NULL;
	return n->parent->parent;
}

node* RBTree::getSibbling(node* n){
	if (n == NULL)
		return NULL;
	if (n->parent == NULL)
		return NULL;
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

node* RBTree::getUncle(node *n){
	if (n == NULL)
		return NULL;
	if (n->parent == NULL)
		return NULL;
	if (n->parent->parent == NULL)
		return NULL;
	return getSibbling(n->parent);
}

void RBTree::replaceNode(node *oldNode, node *newNode){
	if (oldNode->parent == NULL)
		root = newNode;
	else{
		if (oldNode == oldNode->parent->left)
			oldNode->parent->left = newNode;
		else
			oldNode->parent->right = newNode;
	}
	if (newNode != NULL)
		newNode->parent = oldNode->parent;
}

void RBTree::rotateLeft(node* n){
	node* R = n->right;
	replaceNode(n, R);
	n->right = R->left;
	if (R->left != NULL) {
		R->left->parent = n;
	}
	R->left = n;
	n->parent = R;
}

void RBTree::rotateRight(node* n){
	node* L = n->left;
	replaceNode(n, L);
	n->left = L->right;
	if (L->right != NULL)
		L->right->parent = n;
	L->right = n;
	n->parent = L;
}

int RBTree::getNodeColor(node *n){
	return n == NULL ? Color::Black : n->color;
}

int RBTree::Count(int ID){
	int count = 0;
	node *n = root;
	while (n != NULL){
		if (n->Id == ID)
			return n->count;
		else if (ID < n->Id)
			n = n->left;
		else
			n = n->right;
	}
	return count;
}

void RBTree :: InRangeSub(node *r, int ID1, int ID2, int* count){
	if (r == NULL)
		return;
	if (r->Id >= ID1 && r->Id <= ID2)
		*count += r->count;
	if (ID1 < r->Id)
		InRangeSub(r->left, ID1, ID2, count);
	if (ID2 > r->Id)
		InRangeSub(r->right, ID1, ID2, count);
}

int RBTree::InRange(int ID1, int ID2){
	int count = 0;
	InRangeSub(root, ID1, ID2, &count);
	return count;
}

node* RBTree::Next(int ID){
	if (root == NULL)
		return 0;
	node *successor = NULL;
	bool found = false;
	node *n = root;
	while (n != NULL){
		if (ID < n->Id){
			successor = n;
			n = n->left;
		}
		else if (ID > n->Id)
			n = n->right;
		else { // reached the node with that ID
			//found = true;
			if (n->right != NULL){
				n = n->right;
				while (n != NULL){
					successor = n;
					n = n->left;
				}
			}
			else
				break;
		}
	}
	if (successor)
		return successor;
	else
		return NULL;
}

node* RBTree::Previous(int ID){
	if (root == NULL)
		return 0;
	bool found = false;
	node* n = root;
	node* pred = NULL;
	while (n != NULL){
		if (ID < n->Id)
			n = n->left;
		else if (ID > n->Id){
			pred = n;
			n = n->right;
		}
		else{ //Node with that ID found
			if (n->left != NULL){
				found = true;
				// Find Rightmost element of Left tree of this Node
				n = n->left;
				while (n != NULL){
					pred = n;
					n = n->right;
				}
			}
			else // Pred already has that node which is 
				break;
		}
	}

	if (pred != NULL)
		return pred;
	else
		return NULL;
}