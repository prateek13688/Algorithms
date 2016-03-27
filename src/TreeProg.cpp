#include "TreeProg.h"

using namespace std;
TreeProg::TreeProg()
{
    //ctor
}

TreeProg::~TreeProg()
{
    //dtor
}

int TreeProg::abs(int l, int r)
{
    return ((l - r) > 0) ? (l - r) : (r - l);
}
bool TreeProg::isBalanced(Node* root)
{
    if (root == NULL)
        return true;
    int leftHeight = findTreeHeight(root->left);
    int rightHeight = findTreeHeight(root->right);
    if(abs(leftHeight,rightHeight) <= 1)
        return isBalanced(root->left) && isBalanced(root->right);
    return false;
}

int TreeProg::findTreeHeight(Node* parent)
{
    if(parent == NULL)
        return 1;
    int l = findTreeHeight(parent->left);
    int r = findTreeHeight(parent->right);
    return ((l > r) ? l : r) + 1;
}

Node* TreeProg::LCA(Node* root, Node* p, Node* q)
{
    if(root == NULL)
        return NULL;
    if(p == root)
        return p;
    if(q == root)
        return q;
    Node* leftCA =LCA(root->left, p, q);
    Node* rightCA = LCA(root->right, p , q);
    if(leftCA != NULL && rightCA != NULL)
        return root;
    if(leftCA != NULL)
        return leftCA;
    if(rightCA != NULL)
        return rightCA;
    return NULL;
}

Node* TreeProg::createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* TreeProg::createTreefromInorder_PreOrder(std::vector<int>& preorder, vector<int>& inorder, int index)
{
   bool result = false;
    int i = 0, j =0;
    if(inorder.size() == 0)
        return NULL;
    if(inorder.size() == 1)
        return createNode(inorder.at(0));
    for(i =index; i < (int)preorder.size(); i++)
    {
        if(result)
            break;
        for(j = 0; j < (int)inorder.size(); j++)
        {
            if(inorder.at(j) == preorder.at(i))
            {
                result = true;
                break;
            }
        }
    }
    std::vector<int>* left = new vector<int>(inorder.begin(), inorder.begin() + j);
    std::vector<int>* right = new vector<int>(inorder.begin()+j+1, inorder.end());
    Node* newNode = createNode(inorder.at(j));
    cout << "The Inorder at J" << inorder.at(j) << endl;
    newNode->left = createTreefromInorder_PreOrder(preorder, *left, i-1);
    newNode->right = createTreefromInorder_PreOrder(preorder, *right, i - 1);
    delete left;
    delete right;
    return newNode;
}
Node* TreeProg::buildTree(vector<int>& preorder, vector<int>& inorder)
{
    return createTreefromInorder_PreOrder(preorder, inorder, 0);
}

void TreeProg::printTreeInorder(Node* root)
{
    if(root == NULL)
        return;
    printTreeInorder(root->left);
    cout<<root->data;
    printTreeInorder(root->right);
}

Node *TreeProg::invertTree(Node* root)
{
    if(root == NULL)
        return NULL;

    Node* left = invertTree(root->left);
    Node* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}
Node* TreeProg::LCABinarySearch(Node* root, Node* p, Node* q)
{
    if(root == NULL)
        return NULL;
    if(p == root)
        return p;
    if(q == root)
        return q;
    Node* leftCA = NULL;
    Node* rightCA = NULL;
    if((p->data < root->data) && (q->data < root->data))
        leftCA =LCABinarySearch(root->left, p, q);
    else if(((p->data > root->data) && (q->data > root->data)))
        rightCA = LCABinarySearch(root->right, p, q);
    else
        leftCA =LCABinarySearch(root->left, p, q);
        rightCA = LCABinarySearch(root->right, p, q);

    if(leftCA != NULL && rightCA != NULL)
        return root;
    if(leftCA != NULL)
        return leftCA;
    if(rightCA != NULL)
        return rightCA;
    return NULL;
}
int TreeProg::minDistance(int* dist, bool* sptSet, int n)
{
   int min = INT_MAX, min_index;

   for (int v = 1; v <= n; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}
void TreeProg::dijkstra(int** minDist, int** graph, int src, int nCities)
{
     int* dist = new int[nCities+1];

     bool* sptSet = new bool[nCities+1];

     for (int i = 0; i <= nCities; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
     }

     dist[src] = 0;

     for (int count = 1; count < nCities; count++)
     {
       int u = minDistance(dist, sptSet, nCities);
       sptSet[u] = true;
       for (int v = 1; v <= nCities; v++){
             if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
       }
     }
     for(int i = 1; i <= nCities; i++)
        minDist[src][i] = dist[i];
    delete [] sptSet;
    delete [] dist;
}
