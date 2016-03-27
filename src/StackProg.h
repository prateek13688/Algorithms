#ifndef STACKPROG_H
#define STACKPROG_H

#include <malloc.h>
#include <cstddef>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;
struct Node{
    int data;
    Node* next;
};
class StackProg
{
    public:
        static Node* node;
        StackProg();
        void push(int);
        int pop();
        int peek();
        void fillPlates(std::vector<Node*>*, int);
        int getElements(Node*);
        void pushPlates(std::vector<Node*>*, int);
        int popPlates(std::vector<Node*>*, int);
        void addaStack(std::vector<Node*>* );
        void changeValue(int*);
        StackProg* sortStack(StackProg*);
        bool isEmpty();
        void printStack();
        int min(int , int );
        int findMaxArea(int *, int);
        bool validParenthesis(string);
        char reverseParanthesis(char);
        int LargestRectangle(vector<int>&);
        virtual ~StackProg();
    protected:
    private:
        int count;
        Node* top;
};

#endif // STACKPROG_H
