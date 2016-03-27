#include "StackProg.h"

using namespace std;

StackProg::StackProg()
{
    top = NULL;
    count = 0;
}

StackProg::~StackProg()
{
    //dtor
}

void StackProg::push(int d)
{
    Node* newItem = (Node *)malloc(sizeof(Node));
    newItem->data = d;
    newItem->next = top;
    top = newItem;
    count ++;
}
int StackProg::pop()
{
    if(top != NULL)
    {
        Node* item = top;
        top = top->next;
        int data = item->data;
        count --;
        free(item);
        return data;
    }
    return -1;
}

int StackProg::peek(){
    if(top != NULL)
        return top->data;
    return -1;
}

int StackProg::getElements(Node* node)
{
    int i = 1;
    while(node->next != NULL)
    {
        i = i+1;
        node = node->next;
    }
    return i;
}

void StackProg::pushPlates(vector<Node*>* currVector, int stackIndex)
{
    Node* node = currVector->at(stackIndex);
    Node* newItem = (Node*)malloc(sizeof(Node));
    newItem->data = 1;
    newItem->next = node;
    currVector->erase(currVector->begin() + stackIndex);
    currVector->insert(currVector->begin() + stackIndex, newItem);
}

int StackProg::popPlates(vector<Node*>* currVector, int i)
{
    Node* node = currVector->at(i);
    int data = node->data;
    currVector->erase(currVector->begin() + i);
    currVector->insert(currVector->begin() + i, node->next);
    free(node);
    return data;
}
void StackProg::addaStack(vector<Node*>* currVector)
{
    Node *node = (Node* )malloc(sizeof(Node));
    node->data = 1;
    node->next = NULL;
    currVector->push_back(node);
}
void StackProg::fillPlates(vector<Node*>* currVector, int threshold)
{
    int i = 0;
    int nElements = 0;
    bool pushed = false;
    int size = currVector->size();
    while(i < size)
    {
        nElements = getElements(currVector->at(i));
        if(nElements < threshold)
        {
            pushPlates(currVector, i);
            pushed = true;
            break;
        }
        i++;
    }
    if(!pushed)
        addaStack(currVector);
}
void StackProg::changeValue(int *a )
{
    *a = 6;
}

bool StackProg::isEmpty()
{
    if(top == NULL)
        return true;
    return false;
}

void StackProg::printStack()
{
    if(top == NULL)
        return;
    while(top != NULL)
    {
        cout << top->data;
        top = top->next;
    }
}
StackProg* StackProg::sortStack(StackProg* list)
{
    if(top == NULL)
    {
        std::cout << "THE STACK IS EMPTY AND SO NOTHING TO SORT" << endl;
        return NULL;
    }
    int element = 0;
    StackProg* temp = new StackProg();
    while(!list->isEmpty())
    {
        element = list->pop();
        if(temp->isEmpty())
            temp->push(element);
        else{
         while(!temp->isEmpty() && temp->peek() < element)
         {
            list->push(temp->pop());
         }
         temp->push(element);
        }
    }
    return temp;
}

int StackProg::min(int a, int b)
{
    return (a > b) ? b : a;
}

int StackProg::findMaxArea(int* hist, int n)
{
    stack<int> s;

    int max_area = 0;
    int tp;
    int area_with_top;

    int i = 0;
    while (i < n)
    {
        if (s.empty() || hist[s.top()] <= hist[i])
            s.push(i++);
        else
        {
            if(s.empty())
                cout << "The Stack Is Empty" << endl;
            tp = s.top();
            s.pop();

            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);

            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }
    while (s.empty() == false)
    {
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);

        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    return max_area;
}

char StackProg::reverseParanthesis(char ch){
    if (ch == ')')
        return '(';
    else if(ch == ']')
        return '[';
    else
        return '{';
}
bool StackProg::validParenthesis(string s){
    stack<char> charStack;
    bool result = true;
    for(int i = 0; i < s.length(); i++){
        if(s.at(i) == '(' || s.at(i) == '{' || s.at(i) == '[')
            charStack.push(s.at(i));
        if(s.at(i) == ')' || s.at(i) == '}' || s.at(i) == ']')
        {
            if(charStack.empty())
            {
                result = false;
                break;
            }
            if(charStack.top() != reverseParanthesis(s.at(i)))
            {
                result = false;
                break;
            }
            else
                charStack.pop();
        }
    }
    if(result){
        if(!charStack.empty())
            result = false;
    }
    return result;
}
int StackProg::LargestRectangle(vector<int>& rec){
    stack<int> hist;
    int i = 0;
    int n = rec.size();
    int currArea = 0;
    int maxArea = 0;
    while(i < n){
        if(hist.empty() || (rec[hist.top()] <= rec[i])){
            hist.push(i);
            i++;
        }
        else{
            int x = hist.top();
            hist.pop();
            currArea = rec[x] * (hist.empty() ? i : i - hist.top()  - 1);
            maxArea = maxArea > currArea ? maxArea : currArea;
        }
    }
    while(!hist.empty()){
        int x = hist.top();
        hist.pop();
        currArea = rec[x] * ((hist.empty()) ? i : i - hist.top()  - 1);
        maxArea = maxArea > currArea ? maxArea : currArea;
    }
    return maxArea;
}
