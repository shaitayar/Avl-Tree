#ifndef INC_234218_EMPLOYEE_H
#define INC_234218_EMPLOYEE_H
#include <memory>
#include <iostream>
using std::string;
using std::ostream;
using std::shared_ptr;

class Company;

class Employee{
    int ID;
    int salary;
    int grade;
    Company *  p_company;

public:
    Employee(int ID, int salary, int grade, Company* p_company);
    ~Employee()=default;
    int getID() const;
    int getSalary() const;
    int getGrade() const;
    Company* getCompany() const;

    void setSalary(int SalaryIncrease);

    void setGrade();

    void setCompany(Company* new_company){this->p_company = new_company;}

    void print() const{
        std::cout<<getID()<<std::endl;
    }
    //Maybe add setters
};

class CompEmployeeById {
public:
    int operator()(Employee * e1, Employee * e2) const{
        int id1 = e1->getID();
        int id2 = e2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

    int operator()(const Employee * e1, int id2) const{
        int id1 = e1->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

};

class CompEmployeeBySalary{
public:
    int operator()(Employee * e1, Employee * e2) const{
        int s1 = e1->getSalary();
        int s2 = e2->getSalary();
        if (s1 == s2){
            CompEmployeeById c;
            return c(e2,e1);
        }
        else if(s1>s2) return 1;
        else return -1;
    }
};



#endif
