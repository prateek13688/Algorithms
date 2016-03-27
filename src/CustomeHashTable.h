#ifndef CUSTOMHASHTABLE_H
#define CUSTOMHASHTABLE_H

#include <forward_list>

using namespace std;
template<class T, class U> 
class CustomeHashTable
{
public:
	CustomeHashTable(int length){
	}
	int GetHash(T key){
		return 0;
	}
	virtual ~CustomeHashTable(){
	}
private:
	forward_list<int> *arr;
};



#endif
