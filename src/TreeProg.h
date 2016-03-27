#ifndef TREEPROG_H
#define TREEPROG_H

#include <cstddef>
#include <vector>
#include <malloc.h>
#include <iostream>
#include <climits>
struct Node{
    int data;
    Node* left;
    Node* right;
};
class TreeProg
{
    public:
        TreeProg();
        int findTreeHeight(Node* parent);
        bool isBalanced(Node* root);
        int abs(int, int);
        Node* LCA(Node*, Node*, Node*);
        Node* buildTree(std::vector<int>& , std::vector<int>&);
        Node* createTreefromInorder_PreOrder(std::vector<int>&, std::vector<int>&, int);
        Node* createNode(int);
        Node* invertTree(Node*);
        Node* LCABinarySearch(Node*, Node*, Node*);
        void printTreeInorder(Node* );
        int minDistance(int*, bool*, int);
        void dijkstra(int**, int**, int, int);
        virtual ~TreeProg();
    protected:
    private:
};

#endif // TREEPROG_H
