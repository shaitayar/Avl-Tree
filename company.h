#ifndef INC_234218_COMPANY_H
#define INC_234218_COMPANY_H

#include <iostream>
#include "employee.h"
#include "AvlTree.h"
#include <memory>

using std::shared_ptr;
using std::string;


class Company {
    int ID;
    int value;
    int size;
    Node<Employee,CompEmployeeBySalary> * max_sal_emp;
    CompEmployeeById ed;
    CompEmployeeBySalary es;
    AvlTree<Employee, CompEmployeeById> c_employee_by_id;
    AvlTree<Employee, CompEmployeeBySalary> c_employee_by_salary;

public:
    Company(int ID, int value) : ID(ID), value(value), size(0), max_sal_emp(NULL), ed(), es(), c_employee_by_id(ed),
                                 c_employee_by_salary(es) {};

    ~Company();

    int getID() const;

    int getValue() const;

    int getSize() const;

    int getMax();

    void setValue(int value);

    void addEmployee(Employee *);

    void RemoveEmployee(Employee * employee, bool is_obj);

    void promote(Employee * employee);

    void printToList(int ** arr, int size);

    void print() const{
        c_employee_by_id.print();
    }
    void getMatchCompany(int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                         int MinGrade,
                         int *TotalNumOfEmployees, int *NumOfEmployees);
    void TreeToArray(Employee ** empByIDTarget,Employee **empBySalaryTarget);

    void ArrayToTree(Employee ** combinedID, Employee ** combinedSalary, int size);

    void emptyCompany();

};

class CompCompanyById {
public:
    int operator()(Company *c1, Company *c2) const {
        int id1 = c1->getID();
        int id2 = c2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

    int operator()(Company *c1, int id2) const {
        int id1 = c1->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }
};

#endif
