#ifndef PARENT1C_H
#define PARENT1C_H
#include <iostream>

using namespace std;

class parent1C
{
    public:
        parent1C();
        virtual void aboutMe(){
            cout << "I am a parent";
        }
        virtual ~parent1C(){
           cout <<" Deleting the parent object" << endl;
        }
    protected:
    private:
};

#endif // PARENT1C_H
