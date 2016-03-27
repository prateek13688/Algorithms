#ifndef ORAGNIZATION_H
#define ORAGNIZATION_H
#include <vector>
#include <iostream>
#include "Employee.h"
#include <vector>
#include "ArrayProg.h"
#include "demoClass.h"
using namespace std;

class Oragnization : public ArrayProg {
    public:
        enum{
            respondent = 0,
            manager,
            director
        }Rank;
        Oragnization(int, int, int);
        void addEmployee(string, string, int, int);
        int max_no_of_respondents;
        int max_no_of_managers;
        int max_no_of_directors;
        /*void aboutMe(){
            cout <<" I am a student" << endl;
        }*/
        virtual ~Oragnization();
    protected:
    private:
        static vector<vector<Employee>> employeedetails;
};

#endif // ORAGNIZATION_H
