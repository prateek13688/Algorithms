#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Employee
{
    friend class Oragnization;
    public:
        Employee(std::string, std::string, int, int);
        virtual ~Employee();
    protected:
    private:
        std::string employee_name;
        std::string employee_contact;
        int employee_age;
        int employee_rank;
        std::vector<std::string> getEmployeeDetails();
};

#endif // EMPLOYEE_H
