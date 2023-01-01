#include "company.h"

Company::~Company(){
    c_employee_by_id.DestroyTree(false);
    c_employee_by_salary.DestroyTree(true);
}

int Company::getID() const{
    return this->ID;
}

int Company::getValue() const{
    return this->value;
}
int Company::getSize() const{
    return this->size;
}

int Company::getMax(){
    return max_sal_emp->obj->getID();
}


void Company::addEmployee(Employee *employee){
    c_employee_by_id.insert(employee);
    c_employee_by_salary.insert(employee);
    size++;
    max_sal_emp = c_employee_by_salary.getMaxNode();
}

void Company::setValue(int new_value)
{
    this->value += new_value;
}

void Company::RemoveEmployee(Employee * employee, bool is_obj)
{
    this->c_employee_by_id.deleteNode(employee, false);
    this->c_employee_by_salary.deleteNode(employee,is_obj);
    size--;
    max_sal_emp = c_employee_by_salary.getMaxNode();

}

void Company::promote(Employee * employee){
    this->c_employee_by_salary.deleteNode(employee,false);
    this->c_employee_by_salary.insert(employee);
    max_sal_emp = c_employee_by_salary.getMaxNode();
}

void Company::printToList(int ** arr, int size){
    c_employee_by_salary.printToList(arr, size);
}

void Company::getMatchCompany(int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                              int MinGrade,
                              int *TotalNumOfEmployees, int *NumOfEmployees){
    c_employee_by_id.getMatch(MinEmployeeID, MaxEmployeeId, MinSalary,
                               MinGrade,TotalNumOfEmployees, NumOfEmployees);
}

void Company::TreeToArray(Employee ** empByIDTarget,Employee **empBySalaryTarget){
    c_employee_by_id.treeToArr(empByIDTarget);
    c_employee_by_salary.treeToArr(empBySalaryTarget);

}
void Company::ArrayToTree(Employee ** combinedID, Employee ** combinedSalary, int size){
    c_employee_by_id.arrToTree(combinedID, size);
    c_employee_by_salary.arrToTree(combinedSalary, size);
    this->size = size;
    max_sal_emp = c_employee_by_salary.getMaxNode();

}

void Company::emptyCompany(){
    c_employee_by_id.DestroyTree(false);
    c_employee_by_salary.DestroyTree(false);
    size=0;
}

