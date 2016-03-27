#include "Employee.h"

using namespace std;
Employee::Employee(string name, string contact, int age, int rank)
{
    employee_name = name;
    employee_contact = contact;
    employee_age = age;
    employee_rank = rank;
}

Employee::~Employee()
{
    //dtor
}

vector<string> Employee::getEmployeeDetails(){
    std::stringstream emp_age;
    std::stringstream emp_rank;
    emp_age << employee_age;
    emp_rank << employee_rank;
    vector<string> details = {employee_name, employee_contact, emp_age.str(), emp_rank.str()};
    return details;
}
