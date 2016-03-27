#include "demoClass.h"
#include "ArrayProg.h"
demoClass::demoClass()
{
    //ctor
}

demoClass::~demoClass()
{
    //dtor
}
int demoClass::abc(int a){
    ArrayProg* obj = new ArrayProg(4);
	cout << this->a;
    obj->a = a;
    return 0;
}
