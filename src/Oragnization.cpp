#include "Oragnization.h"

vector<vector<Employee>> Oragnization::employeedetails;
Oragnization::Oragnization(int maxrespondent, int maxmanagers, int maxdirectors)
{
    max_no_of_respondents = maxrespondent;
    max_no_of_managers = maxmanagers;
    max_no_of_directors = maxdirectors;
    vector<Employee> respondents;
    vector<Employee> managers;
    vector<Employee> directors;
    employeedetails.push_back(respondents);
    employeedetails.push_back(managers);
    employeedetails.push_back(directors);
}

Oragnization::~Oragnization()
{
    //dtor
}

void Oragnization::addEmployee(string name, string contact, int age, int rank){
    Employee obj = {name, contact, age, rank};
    //if(employeedetails[obj.employee_rank].size() > )
        employeedetails[obj.employee_rank].push_back(obj);
}
