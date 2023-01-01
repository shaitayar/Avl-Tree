#include "employee.h"
#include <iostream>


Employee::Employee(int ID, int salary, int grade, Company* p_company): ID(ID), salary(salary), grade(grade), p_company(p_company) {}


int Employee::getID() const {
    return this->ID;
}

int Employee::getSalary() const {
    return this->salary;
}

int Employee::getGrade() const {
    return this->grade;
}

Company* Employee::getCompany() const{
    return p_company;
}

void Employee::setSalary(int SalaryIncrease) {
    salary+=SalaryIncrease;
}

void Employee::setGrade(){
    grade+=1;
}


