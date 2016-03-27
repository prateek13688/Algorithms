#include "ThreadDemo.h"
#include <thread>

using namespace std;
ThreadDemo::ThreadDemo(int value)
{
	a = value;
}


ThreadDemo::~ThreadDemo()
{
}

void ThreadDemo::func1(){
	cout << "The World should know" << endl;
}