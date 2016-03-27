#include <iostream>
#pragma once
class ThreadDemo
{
private:
	int a;
public:
	ThreadDemo(){
	}
	int getValue(){
		return a;
	}
	ThreadDemo(int);
	~ThreadDemo();
	void func1();
	ThreadDemo operator +(const ThreadDemo& rhs){
		ThreadDemo demo;
		demo.a = a + rhs.a;
		return demo;
	}
};

