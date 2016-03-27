#ifndef DEMOCLASS_H
#define DEMOCLASS_H
#include "ArrayProg.h"
#include "Oragnization.h"
class demoClass
{
    public:
        demoClass();
		demoClass(int a) : a(a) {}
		void display(){ cout << a;  }
        virtual ~demoClass();
        int abc(int);
        /*void aboutMe(){
            cout << "I am a student" << endl;
        }*/
    protected:
    private:
		int a;
};

#endif // DEMOCLASS_H
