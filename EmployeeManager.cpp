#include "EmployeeManager.h"

using std::exception;

EmployeeManager::~EmployeeManager() {
    employee_by_id.DestroyTree(false);
    employee_by_salary.DestroyTree(false);
    company_not_empty.DestroyTree(false);
    company_by_id.DestroyTree(true);

}

void EmployeeManager::AddCompany(int CompanyID, int Value) {
    if (company_by_id.find(CompanyID) != NULL) throw EmFailure();
    Company *company = new Company(CompanyID, Value);
    if (!company) throw EmAllocationError();
    company_by_id.insert(company);
    company_num++;
}

void EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade) {
    Node<Company, CompCompanyById> *c = company_by_id.find(CompanyID);
    if(c==NULL) throw EmFailure();
    Company * comp = c->obj;

    if (employee_by_id.find(EmployeeID) != NULL) {
        throw EmFailure();
    }
    Employee *employee = new Employee(EmployeeID, Salary, Grade, comp);
    if (!employee) throw EmAllocationError();
    employee_by_id.insert(employee);
    employee_by_salary.insert(employee);
    comp->addEmployee(employee);
    employee_num++;
    max_employee = employee_by_salary.getMaxNode();
    if (company_not_empty.find(CompanyID)==NULL){
        company_not_empty.insert(comp);
    }
}

void EmployeeManager::RemoveEmployee(int EmployeeID) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *employee = node->obj;
    Company *company = employee->getCompany();
    employee_by_id.deleteNode(employee,false);
    employee_by_salary.deleteNode(employee, false);
    company->RemoveEmployee(employee, true);

    max_employee = employee_by_salary.getMaxNode();
    if (company->getSize() == 0) company_not_empty.deleteNode(company,false);
    employee_num--;
}

void EmployeeManager::RemoveCompany(int CompanyID) {
    auto comp = company_by_id.find(CompanyID);
    if (!comp) throw EmFailure();
    Company *company = comp->obj;

    //If company has workers
    if (company->getSize() != 0) throw EmFailure();
    company_by_id.deleteNode(company,true);
    company_num--;
}


void EmployeeManager::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    Company *comp = emp->getCompany();
    *EmployerID = comp->getID();
    *Salary = emp->getSalary();
    *Grade = emp->getGrade();
}

void EmployeeManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    Company *company = emp->getCompany();
    company->RemoveEmployee(emp, false);

    employee_by_salary.deleteNode(emp,false);
    emp->setSalary(SalaryIncrease);
    employee_by_salary.insert(emp);
    company->addEmployee(emp);
    if (BumpGrade > 0) {
        emp->setGrade();
    }

    max_employee = employee_by_salary.getMaxNode();
}


void EmployeeManager::HireEmployee(int EmployeeID, int NewCompanyID) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    Company *company1 = emp->getCompany();
    auto n_company = company_by_id.find(NewCompanyID);
    if (!n_company) throw EmFailure();
    Company *company2 = n_company->obj;
    if (company1->getID()==company2->getID()) throw EmFailure();
    //remove from company 1 and add to company 2
    emp->setCompany(company2);
    company1->RemoveEmployee(emp,false);
    company2->addEmployee(emp);
    if (company2->getSize()==1){
        company_not_empty.insert(company2);
    }
    if (company1->getSize()==0){
        company_not_empty.deleteNode(company1,false);
    }
}


void EmployeeManager::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees) {
    auto node = company_by_id.find(CompanyID);
    if (node == NULL) throw EmFailure();
    *Value = node->obj->getValue();
    *NumEmployees = node->obj->getSize();
}

void EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease) {
    auto node = company_by_id.find(CompanyID);
    if (node == NULL)
        throw EmFailure();
    node->obj->setValue(ValueIncrease);
}

template <class L>
void merge(Employee **X, int x_size, Employee **Y, int y_size, Employee **result, L compare) {
    int i = 0, j = 0, k = 0;
    while ((i < x_size) && (j < y_size)) {
        if (compare(X[i], Y[j]) > 0) {
            result[k] = (Y[j]);
            k++;
            j++;
        } else {
            result[k] = (X[i]);
            k++;
            i++;
        }
    }
    while (i < x_size) {
        result[k] = (X[i]);
        k++;
        i++;
    }
    while (j < y_size) {
        result[k] = (Y[j]);
        k++;
        j++;
    }
}

void update_company(Employee ** arr,int size, Company * comp){
    for (int i = 0; i < size; ++i) {
        arr[i]->setCompany(comp);
    }
}

void EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor) {
    auto acquirer = company_by_id.find(AcquirerID);
    auto target = company_by_id.find(TargetID);
    if (!acquirer || !target) throw EmFailure();
    Company * c_target = target->obj;
    Company * c_acquirer = acquirer->obj;
    int target_value = c_target->getValue();
    int acquirer_value = c_acquirer->getValue();
    if (acquirer_value < target_value * 10) throw EmFailure();
    int new_value = (acquirer_value + target_value) * Factor;
    int tsize = c_target->getSize();
    int asize = c_acquirer->getSize();

    Company *new_company = new Company(AcquirerID, new_value);
    if (!new_company) throw EmAllocationError();

    Employee **empByIDTarget = (Employee **) malloc(sizeof(**empByIDTarget) * tsize);
    Employee **empBySalaryTarget = (Employee **) malloc(sizeof(**empBySalaryTarget) * tsize);
    Employee **empByIDAcq = (Employee **) malloc(sizeof(**empByIDAcq) * asize);
    Employee **empBySalaryAcq = (Employee **) malloc(sizeof(**empBySalaryAcq) * asize);
    Employee **combinedID = (Employee **) malloc(sizeof(**combinedID) * (tsize + asize));
    Employee **combinedSalary = (Employee **) malloc(sizeof(**combinedSalary) * (tsize + asize));

    if(!empByIDTarget ||!empBySalaryTarget||!empByIDAcq||!empBySalaryAcq ||!combinedID ||!combinedSalary){
        free(empByIDTarget);
        free(empBySalaryTarget);
        free(empByIDAcq);
        free(empBySalaryAcq);
        free(combinedID);
        free(combinedSalary);
        delete new_company;
        throw EmAllocationError();
    }

    c_target->TreeToArray(empByIDTarget, empBySalaryTarget);
    c_acquirer->TreeToArray(empByIDAcq, empBySalaryAcq);

    CompEmployeeById ci;
    CompEmployeeBySalary cs;
    merge<CompEmployeeById>(empByIDTarget, tsize, empByIDAcq, asize, combinedID, ci);
    merge<CompEmployeeBySalary>(empBySalaryTarget, tsize, empBySalaryAcq, asize, combinedSalary, cs);

    update_company(combinedID,tsize+asize, new_company);

    new_company->ArrayToTree(combinedID, combinedSalary, tsize+asize);
    c_target->emptyCompany();
    c_acquirer->emptyCompany();
    if(company_not_empty.find(c_target->getID())!=NULL) company_not_empty.deleteNode(c_target, false);
    if(company_not_empty.find(c_acquirer->getID())!=NULL)company_not_empty.deleteNode(c_acquirer,false);

    this->RemoveCompany(TargetID) ;
    this->RemoveCompany(AcquirerID) ;

    //Add company
    this->company_by_id.insert(new_company);
    if (new_company->getSize()>0) this->company_not_empty.insert(new_company);
    company_num++;
    free(empByIDTarget);
    free(empBySalaryTarget);
    free(empByIDAcq);
    free(empBySalaryAcq);
    free(combinedID);
    free(combinedSalary);
}

void EmployeeManager::GetHighestEarner(int CompanyID, int *EmployeeID) {
    if (CompanyID < 0) {
        if(employee_num==0) throw EmFailure();
        *EmployeeID = max_employee->obj->getID();
    } else if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company *comp = node->obj;
        if (comp->getSize()==0) throw EmFailure();
        *EmployeeID = comp->getMax();
    }
}

void EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees) {
    if (CompanyID < 0) {
        if (employee_num ==0) throw EmFailure();
        *Employees = (int *) std::malloc(employee_num * sizeof(int));
        if (!Employees) throw EmAllocationError();
        employee_by_salary.printToList(Employees, employee_num);
        *NumOfEmployees = employee_num;
    } else if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) {
            throw EmFailure();
        }
        Company *comp = node->obj;
        if (comp->getSize()==0) throw EmFailure();
        *Employees = (int *) std::malloc(comp->getSize() * sizeof(int));
        if (!Employees) throw EmAllocationError();
        comp->printToList(Employees, comp->getSize());
        *NumOfEmployees = comp->getSize();
    }
}

void EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees) {
    if (company_not_empty.getSize() < NumOfCompanies) throw EmFailure();
    *Employees = (int *) std::malloc(NumOfCompanies * sizeof(int));
    if (!Employees) throw EmAllocationError();

    company_not_empty.getNMax(NumOfCompanies, Employees);
}

void EmployeeManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                                              int MinGrade,
                                              int *TotalNumOfEmployees, int *NumOfEmployees) {

    *TotalNumOfEmployees = 0;
    *NumOfEmployees = 0;

    if (CompanyID < 0) {
        if(employee_num==0) throw EmFailure();
        employee_by_id.getMatch(MinEmployeeID, MaxEmployeeId, MinSalary,
                                MinGrade, TotalNumOfEmployees, NumOfEmployees);
    }
    if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company *company = node->obj;
        if (company->getSize() == 0) {
            throw EmFailure();
        } else {
            company->getMatchCompany(MinEmployeeID, MaxEmployeeId, MinSalary,
                                     MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
    }
}
