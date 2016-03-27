#include "SingleList.h"
#include <cstddef>pa
#include <malloc.h>
#include <iostream>
#include <queue>
using namespace std;

SingleList::SingleList()
{
}

node* SingleList:: createList(int d)
{
    node* Node = (node *) malloc(sizeof(node));
    Node->data = d;
    Node->next = NULL;
    return Node;
}

node* SingleList:: addtohead(node* currList, int d)
{
    node* start = (node *)malloc(sizeof(node));
    start->data = d;
    start->next = currList;
    return start;
}
void SingleList::addtoTail(node* list, int d)
{
    if(list == NULL)
        return ;
    while(list->next != NULL)
        list = list->next;
    node *end = (node *) malloc(sizeof(node));
    end->data = d;
    end->next = NULL;
    list->next = end;
}
void SingleList::addtoToList(node* currList, int data)
{
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    while(currList->next != NULL)
        currList = currList->next;
    currList->next = newNode;
}

void SingleList::printList(node* list)
{
    if (list == NULL)
        return;
    cout << list->data<<endl;
    printList(list->next);
}
void SingleList::deletenode_at_kpostion(node *knode)
{
    if(knode == NULL)
        return;
    node *temp = knode->next;
    if(temp == NULL)
    {
        free(knode);
        knode = NULL;
        return;
    }
    knode->data = temp->data;
    knode->next = temp->next;
    free(temp);
    temp = NULL;
}

bool SingleList::isPallindrome(node* n)
{
    node* head = n;
    if(pallindrome(head, head))
        return true;
    return false;
}

node* SingleList::pallindrome(node* left, node* right)
{
    bool result;
    if(right == NULL)
        return left;
    left = pallindrome(left, right->next);
    if(left)
    {
        result = (left->data == right->data) ? true : false;
        if(result)
        {
            left = (left->next != NULL) ? left->next : left;
            return left;
        }
    }
    return NULL;
}

void SingleList:: removeDuplicates(node* current)
{
    node* movingPointer;
    while(current != NULL)
    {
        movingPointer = current;
        while(movingPointer->next != NULL)
        {
            if(movingPointer->next->data == current->data)
                movingPointer->next = movingPointer->next->next;
            else
                movingPointer = movingPointer->next;
        }
        current = current->next;
    }
}

void SingleList::printKelements(int k, node* list)
{
    int i = 1;
    while( i < k && list != NULL)
    {
        i++;
        list = list->next;
    }
    printList(list);
}

void SingleList::printinReverse(node* list)
{
    if(list == NULL)
        return;
    printinReverse(list->next);
    cout << list->data << endl;
}

node* SingleList::partitionAroundValue(node* list, int x)
{
    node* begin ;
    node* temp;
    if(!list)
        return NULL;
    node* plist = (node *) malloc(sizeof(node));
    plist-> data = x;
    plist->next = NULL;
    begin = plist;
    while(list)
    {
        if(list->data < plist->data)
            begin = addtohead(begin, list->data);
        else if(list->data > plist->data)
            addtoTail(plist, list->data);
        temp = list;
        list = list->next;
        free(temp);
    }
    return begin;
}

node* SingleList::isLoop(node* list)
{
    node* first = list;
    node* moving = list;
    while(moving != NULL || moving->next != NULL)
    {
        first = first->next;
        moving = moving->next->next;
        if(first == moving)
            break;
    }
    if(moving == NULL || moving->next != NULL)
        return NULL;


    while(first != moving)
    {
        first = first->next;
        moving = moving->next;
    }
    return first;
}

node* SingleList::addTwoNumbers(node* l1, node* l2, int k){
    if((l1 == NULL) && (l2 == NULL))
    {
        if(k == 0)
            return NULL;
        else
            return createList(k);
    }
    int firstNo = 0;
    int secondNo = 0;
    int add = 0;
        if(l1 == NULL)
        firstNo = 0;
    else
        firstNo = l1->data;
    if(l2 == NULL)
        secondNo = 0;
    else
        secondNo = l2->data;
    add = firstNo + secondNo + k;
    node* newNode = createList(add%10);
    k = add / 10;
    if(l1 == NULL)
        newNode->next = addTwoNumbers(NULL, l2->next, k);
    else if(l2 == NULL)
        newNode->next = addTwoNumbers(l1->next, l2, k);
    else
        newNode->next = addTwoNumbers(l1->next, l2->next, k);
    return newNode;
}
node* SingleList::createNumber(ulint result){
    node* first = NULL;
    node* current = NULL;
    if(result == 0)
        return createList(0);
    while(result > 0)
    {
        if(first == NULL)
        {
            first = createList(result % 10);
            current = first;
        }
        else
        {
            current->next = createList(result %10);
            current = current->next;
        }
        result = result / 10;
    }
    return first;
}
node* SingleList::addNumber(node* l1, node* l2){
    return addTwoNumbers(l1, l2, 0);
}

node* SingleList::swapList(node* head){
    node* temp = head;
    head = head->next;
    head->next = temp;
    return head;
}
node* SingleList::swapPairs(node* head){
    if(head == NULL || head->next == NULL)
        return NULL;

    node* temp = swapPairs(head->next->next);
    node* tmp = head;
    head = head->next;
    head->next = tmp;
    head->next->next = temp;
    printList(head);
    return head;
}

void SingleList::reverseKnode(node* head, node* revnode, node* cutList, int k, int index){
    if(index > k)
    {
        cutList = head;
        return;
    }
    reverseKnode(head->next, revnode, cutList, k, index+1);
    cout << cutList->data;
    if(index == k)
        revnode = head;
    else{
        node* temp = revnode;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = head;
    }
    if(index == 0)
        revnode->next = cutList;
}
node* SingleList::reverseKGroup(node* head, int k){
    node* temp = head;
    int size = 0;
    while(temp != NULL){
        temp = temp->next;
        size++;
    }
    if(size < k)
        return head;
    temp = head;
    node* revNode = NULL;
    while(size >= k){
        node* buff = NULL;
        node* currtail = NULL;
        for(int i = 0; i < k; i++){
            if(buff == NULL){
                buff = head;
                currtail = head;
                head = head->next;
            }
            else{
                node* temp = head;
                head = head->next;
                temp->next = buff;
                buff = temp;
            }
            size --;
        }
        if(currtail)
            currtail->next = NULL;
        if(revNode == NULL)
            revNode = buff;
        else {
            node* tmp = revNode;
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = buff;
        }
    }
    temp = revNode;
    while(temp->next != NULL)
        temp = temp->next;
    temp ->next = head;
    cout << "The Reversed Node" << endl;printList(revNode);
    cout << "The Left Node" << endl;printList(head);
    return revNode;
}
