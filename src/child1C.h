#ifndef CHILD1C_H
#define CHILD1C_H

#include <iostream>
#include "parent1C.h"
#include "Employee.h"
using namespace std;

template <class T>
class child1C
{
	friend class Employee;
    public:
        T *arr;
        int a , b;
        child1C(){
        }
        void aboutMe(){
            cout << "I am a student" << endl;
        }
        child1C operator+(child1C &obj){
            child1C c;
            c = *this;
            return c;
        }
        void find(int a, int b = 3, int c = 5){
           cout << " The Values of a & b & c" << a << " " << b << c << endl;
           cout << endl;
        }
        virtual ~child1C(){
            cout << " Deleting Child Object" << endl;
        }
    protected:
    private:
};

#endif // CHILD1C_H
