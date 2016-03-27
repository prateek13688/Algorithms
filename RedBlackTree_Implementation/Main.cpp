#include <iostream>
#include "RBTree.h"
#include <ctime>

using namespace std;

int main(int argv, char* args[]){
	cout << "The BBST Program" << endl;
	bool usermode = false;
	if (argv == 2)
		usermode = true;
	else if (argv == 4)
		usermode = false;
	else {
		cout << "The Input format not correct" << endl;
		return 0;
	}
	char *inputFile = args[1];
	vector<i_event> input = getInput(inputFile);
	if (input.size() == 0){
		cout << "The Input Vector is Empty" << endl;
		return 0;
	}
	RBTree *rbst = new RBTree();
	rbst->initializeTree(input);
	if (usermode){
		startUserMode(rbst);
	}
	else{
		clock_t startTime = clock();
		char *commandFile = args[2];
		char *outputFile = args[3];
		getCommands(rbst, commandFile, outputFile);
		clock_t endTime = clock();
		cout << "The Time taken" << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
	}
	return 0;
}