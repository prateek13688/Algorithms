#ifndef SINGLELIST_H
#define SINGLELIST_H
#include <cstddef>
#include <Math.h>
      struct node{
            int data;
            node* next;
        };
typedef unsigned long long int ulint;
class SingleList
{
    public:
        SingleList();
        node* createList(int d);
        void addtoToList(node*, int);
        void printList(node*);
        void deletenode_at_kpostion(node *);
        bool isPallindrome(node*);
        void removeDuplicates(node*);
        void printKelements(int, node*);
        void printinReverse(node *);
        node* addtohead(node*, int);
        void addtoTail(node*, int);
        node* partitionAroundValue(node* , int);
        node* isLoop(node*);
        node* addTwoNumbers(node*, node*, int);
        node* addNumber(node*, node*);
        node* createNumber(ulint);
        node* swapList(node*);
        node* swapPairs(node*);
        void reverseKnode(node*, node*, node*, int, int);
        node* reverseKGroup(node*, int);
    private:
        node* pallindrome(node*, node*);
    protected:
};

#endif // SINGLELIST_H
