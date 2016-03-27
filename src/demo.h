#pragma once
#include <iostream>
using namespace std;
class demo
{
public:
	demo(int b){
		cout << "I am i Demo Class" << endl;
	}
	virtual ~demo(){
		cout << "I am i Demo Class destructor" << endl;
	}
	void abc() {
		cout << "ABC Demo " << endl;
	}
};

