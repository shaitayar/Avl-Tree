#include "library1.h"
#include "EmployeeManager.h"


/***
 * Init - initializes empty Data Structure.
 */
void *Init() {
    EmployeeManager *DS = new EmployeeManager();
    return (void *) DS;
}


/***
 * AddCompany - Adds new company to DS, with unique ID and start Value.
 * @param DS- pointer to Data Structure
 * @param CompanyID- unique ID for the new company
 * @param Value- start Value for the company
 *
 * @return StatusType
 */

StatusType AddCompany(void *DS, int CompanyID, int Value) {
    if (DS == NULL || CompanyID <= 0 || Value <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AddCompany(CompanyID, Value);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}

/***
 * AddEmployee -
 * @param DS- pointer to Data Structure
 * @param EmployeeID- ID for the new employee.
 * @param CompanyID- ID of the employees' company
 * @param Salary- start salary for the new employee
 * @param Grade- start grade of the new employee
 *
 * @return StatusType
 */
StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade) {
    if (DS == NULL || EmployeeID <= 0 || CompanyID <= 0 || Salary<=0 || Grade < 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}
/***
 * RemoveCompany - Removing bankrupted company from the DS. note: the company need to be empty.
 * @param DS- pointer to Data Structure
 * @param CompanyID- The ID of the bankrupted company
 *
 * @return StatusType
 */
StatusType RemoveCompany(void *DS, int CompanyID) {
    if (DS == NULL || CompanyID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->RemoveCompany(CompanyID);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * RemoveEmployee -
 * @param DS- pointer to Data Structure
 * @param EmployeeID- ID for the new employee.
 *
 * @return StatusType
 */
StatusType RemoveEmployee(void *DS, int EmployeeID) {
    if (DS == NULL || EmployeeID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->RemoveEmployee(EmployeeID);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}

/***
 * GetCompanyInfo - Returning existing company's value and number of employees.
 * @param DS- pointer to Data Structure
 * @param CompanyID- The ID of the relevant company
 * @param Value- pointer to integer that will contain company's value
 * @param NumEmployees- pointer to integer that will contain company's number of employees
 *
 * @return StatusType
 */
StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees) {
    if (DS == NULL || CompanyID <= 0 || Value == NULL || NumEmployees == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * GetEmployeeInfo - Returning existing Employee's current Employer ID, salary and grade.
 * @param DS- pointer to Data Structure
 * @param EmployeeID- The ID of the relevant employee
 * @param EmployerID- pointer to integer that will be change in accordance with Employer ID
 * @param Salary- pointer to integer that will contain employee's salary
 * @param Grade- pointer to integer that will contain employee's grade
 *
 * @return StatusType
 */
StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    if (DS == NULL || EmployerID == NULL || Salary == NULL || Grade == NULL || EmployeeID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * IncreaseCompanyValue - Adding increment to existing company's value.
 * @param DS- pointer to Data Structure
 * @param CompanyID- The ID of the relevant company
 * @param ValueIncrease- The increment in company's value
 *
 * @return StatusType
 */
StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease) {
    if (DS == NULL || CompanyID <= 0 || ValueIncrease <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * PromoteEmployee - raising existing employee's salary and promoting him to higher grade .
 * @param DS- pointer to Data Structure
 * @param EmployeeID- The ID of the relevant employee
 * @param SalaryIncrease- The increment in employee's salary
 * @param BumpGrade- if BumpGrade>0, employee will be promoted
 *
 * @return StatusType
 */
StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade) {
    if (DS == NULL || EmployeeID <= 0 || SalaryIncrease <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}

/***
 * HireEmployee - changing existing employee's employer.
 * @param DS- pointer to Data Structure
 * @param EmployeeID- The ID of the relevant employee
 * @param NewCompanyID- The ID of the new employer (comapny)
 *
 * @return StatusType
 */
StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID) {
    if (DS == NULL || EmployeeID <= 0 || NewCompanyID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->HireEmployee(EmployeeID, NewCompanyID);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * AcquireCompany - One company from the DS Acquiring another company.
 * @param DS- pointer to Data Structure
 * @param AcquirerID- The ID of the acquirer company
 * @param TargetID- The ID of the target (acquired) company
 * @param Factor- the factor that will be used to calculate the new value
 *
 * @return StatusType
 */
StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor) {
    if (DS == NULL || AcquirerID <= 0 || TargetID <= 0 || Factor < 1.00 || TargetID == AcquirerID)
        return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AcquireCompany(AcquirerID, TargetID, Factor);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * GetHighestEarner - Returning the most earning employee (in specific company or the whole DS).
 * @param DS- pointer to Data Structure
 * @param CompanyID- The ID of the of specific company. if CompanyID<0 checking the entire DS
 * @param EmployeeID- pointer to integer that will contain the most earning employee's ID
 *
 * @return StatusType
 */
StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID) {
    if (DS == NULL || CompanyID == 0 || EmployeeID == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetHighestEarner(CompanyID, EmployeeID);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * GetAllEmployeesBySalary - Returning the employees ID's sorted by their salaries in descending order (in specific company or the whole DS).
 * @param DS- pointer to Data Structure
 * @param CompanyID- he ID of the of specific company. if CompanyID<0 checking the entire DS
 * @param Employees- pointer to array that will contain the sorted employees ID's
 * @param NumOfEmployees- pointer to integer that will contain the number of employees
 *
 * @return StatusType
 */
StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees) {
    if (DS == NULL || CompanyID == 0 || Employees == NULL || NumOfEmployees == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * GetHighestEarnerInEachCompany - Returning the most earning employees ID in the lowest ID companies.
 * @param DS- pointer to Data Structure
 * @param NumOfCompanies- the number of companies that will be checked
 * @param Employees- pointer to array that will contain the most earning employee ID for each of the checked companies
 *
 * @return StatusType
 */
StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees) {
    if (DS == NULL || NumOfCompanies < 1 || Employees == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}
/***
 * GetNumEmployeesMatching - returning the number of the employees who met the conditions for ID, salary and garde.
 * @param DS- pointer to Data Structure
 * @param CompanyID- the ID of the of specific company. if CompanyID<0 checking the entire DS
 * @param MinEmployeeID- condition for minimum employee ID
 * @param MaxEmployeeId - condition for maximum employee ID
 * @param MinSalary - condition for minimum salary
 * @param MinGrade - condition for minimum grade
 * @param TotalNumOfEmployees - pointer to integer that will contain the number of employees that met the conditions for min and max ID.
 * @param NumOfEmployees -  pointer to integer that will contain the number of employees that met the conditions for min and max ID, min salary and min grade.
 *
 * @return StatusType
 */
StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (DS == NULL || CompanyID == 0 || MinEmployeeID > MaxEmployeeId || MinSalary < 0 ||
        MaxEmployeeId < 0 || MinEmployeeID < 0 || MinGrade < 0 || NumOfEmployees == NULL || TotalNumOfEmployees == NULL)
        return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade,
                                                          TotalNumOfEmployees, NumOfEmployees);
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;

}

/***
 * Quit - freeing all the allocations of memory, and set the DS pointer to null.
 * @param DS- pointer to Data Structure
 */
void Quit(void **DS){
    if (DS==NULL) return ;
    delete ((EmployeeManager *) *DS);
    *DS = NULL;
}