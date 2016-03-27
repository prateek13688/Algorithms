#pragma once
#include <iostream>
#include "demo.h"
using namespace std;
class demo1 
{
private:
	int a;
public:
	int value;
	//demo1() : value(0) {}
	demo1( const demo1 & c){
		if (&c != this)
		this->value = c.value;
		cout << "Copying"<< endl;
	}
	virtual ~demo1(){
		cout << "I am i Demo Class 1 destructor" << endl;
	}
		void set(int val) {
			this->value = val;
		}
		int get(){ return this->value; }
};

