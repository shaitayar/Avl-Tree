#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "AvlTree.h"
#include <stdio.h>
#include "exception"

class EmployeeManager {
    int company_num;
    int employee_num;
    Node<Employee, CompEmployeeBySalary> *max_employee;
    CompEmployeeById ed;
    CompEmployeeBySalary es;
    CompCompanyById cd;
    AvlTree<Employee, CompEmployeeById> employee_by_id;
    AvlTree<Employee, CompEmployeeBySalary> employee_by_salary;
    AvlTree<Company, CompCompanyById> company_by_id;
    AvlTree<Company, CompCompanyById> company_not_empty;


public:
    EmployeeManager() : company_num(0), employee_num(0), max_employee(NULL), ed(), es(), cd(), employee_by_id(ed),
                        employee_by_salary(es),
                        company_by_id(cd), company_not_empty(cd) {};

    ~EmployeeManager();

    void AddCompany(int CompanyID, int Value);

    void AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    void RemoveCompany(int CompanyID);

    void RemoveEmployee(int EmployeeID);

    void GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

    void GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

    void print() const {
        employee_by_salary.print();
    }

    void IncreaseCompanyValue(int CompanyID, int ValueIncrease);


    void PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);


    void HireEmployee(int EmployeeID, int NewCompanyID);

    void AcquireCompany(int AcquirerID, int TargetID, double Factor);

    void GetHighestEarner(int CompanyID, int *EmployeeID);

    void GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);

    void GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

    void GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade,
                            int *TotalNumOfEmployees, int *NumOfEmployees);

    //void Quit();
    class EmException : public std::exception {};

    class EmFailure : public EmException {};

    class EmInvalidInput : public EmException {};

    class EmAllocationError : public EmException {};

};


#endif
