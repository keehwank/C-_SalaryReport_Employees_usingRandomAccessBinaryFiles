//This program is for creating departments and employees to report the total 
// alary paid for each department and storing the data in Binary Files and 
// accessing it in Random Access mode.
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

const int sizeDepName = 20, sizeName = 15;
fstream departments, employees;

struct Department           //designing the structure named Department
{
   int departmentID;
   char departmentName[sizeDepName];
   char departmentHeadName[sizeName];
};

struct Employee         //designing the structure named Employee
{
    int  employeeID;
    char employeeName[sizeName];
    int  employeeSalary;
    int  employeeAge;
    int  employeeDepartmentID;
};

Department dep;           //declaring a structure variable 
Employee emp;             //declaring a structure variable
    

void depFileOpen();                   // Function Prototypes  
void empFileOpen();                   // Function Prototypes
void displayMenu();                   // Function Prototypes
void validation(char &num);            // Function Prototypes
int  vdDepartmentID(int depID);      // Function Prototypes
int  vdEmployeeID(int empID);        // Function Prototypes
int  vdEmployeeDepID(int empDepID);  // Function Prototypes
int  numRecordDep();                  // Function Prototypes
int  numRecordEmp();                  // Function Prototypes

int main()
{
    char charSelection;   //for user choices
    string input;         //use to read strings
    int choiceEdit;       //store the choice to edit department and employee
    int count, countRecordDep, countRecordEmp;
    
    
    do
    {
       displayMenu();    //calling the displayMenu function
    
       cout << "Please make a selection : ";
       cin >> charSelection;
       validation(charSelection);     //validating the variable of charSelection
       
       if (charSelection == '1')      //in case of creating departments
       {
           cout << "Enter the NEW Department Data:" << endl;
                        
           cout << "Dept ID: ";
           cin >> dep.departmentID;
           dep.departmentID = vdDepartmentID(dep.departmentID);  //validating
           cin.ignore();       
                         
           cout << "Dept Name: ";
           getline(cin, input);
           strcpy(dep.departmentName, input.c_str());
                         
           cout << "Head of Dept Name: ";
           getline(cin, input);
           strcpy(dep.departmentHeadName, input.c_str());
  
           depFileOpen(); 
           departments.seekp(0L, ios::end);
           departments.write(reinterpret_cast<char *>(&dep), sizeof(dep));
                        
           departments.close();
       }
                         
       else if (charSelection == '2')    //in case of creating employees
       {
           cout << "Enter the NEW Employee Data:" << endl;
                        
           cout << "Employee ID: ";
           cin >> emp.employeeID;
           emp.employeeID = vdEmployeeID(emp.employeeID);  //validating
           cin.ignore();
                         
           cout << "Employee Name: ";
           cin.getline(emp.employeeName, sizeName);
                         
           cout << "Employee Salary: $";
           cin >> emp.employeeSalary;
                        
           cout << "Employee Age: ";
           cin >> emp.employeeAge;
                        
           cout << "Department ID: ";
           cin >> emp.employeeDepartmentID;
           //validating employee's department should be one of existed departments
           emp.employeeDepartmentID = vdEmployeeDepID(emp.employeeDepartmentID);
           
           empFileOpen(); 
           employees.seekp(0L, ios::end);   //random access 
           employees.write(reinterpret_cast<char *>(&emp), sizeof(emp));
           
           employees.close();
       }
                         
       else if (charSelection == '3')   //editing the existed departments
       {
           cout << "Which record to Edit:" << endl;
           cout << "Please choose one of the following... 1 to " << numRecordDep() << " : ";
           cin >> choiceEdit;
           //validating whether the choice is one of existed departments
           while (choiceEdit  < 1 || choiceEdit > numRecordDep())
           {
               cout << "Please enter a valid choice (1 to " << numRecordDep() << "): ";
               cin >> choiceEdit;
           }
           
           //display the department data to edit
           depFileOpen();
           departments.seekg(sizeof(dep)*(choiceEdit-1), ios::beg);
           departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
           cout << endl << "Display Department Details:" << endl;
           cout << left << setw(13) << "Dept ID     : " << choiceEdit << endl;
           cout << left << setw(13) << "Dept Name   : " << dep.departmentName << endl;
           cout << left << setw(13) << "Dept Head   : " << dep.departmentHeadName << endl << endl;
           
           //editing the department data except the department ID              
           cout << "Edit the Department Data:" << endl;
           dep.departmentID = choiceEdit;
           cin.ignore();
           cout << "Dept Name: ";
           getline(cin, input);
           strcpy(dep.departmentName, input.c_str());
           cout << "Head of Dept Name: ";
           getline(cin, input);
           strcpy(dep.departmentHeadName, input.c_str());
           departments.seekp(sizeof(dep)*(choiceEdit-1), ios::beg);
           departments.write(reinterpret_cast<char *>(&dep), sizeof(dep));
           departments.close();
       }
           
       else if (charSelection == '4')   //editing the existed employees
       {
           cout << "Which record to Edit:" << endl;
           cout << "Please choose one of the following... 1 to " << numRecordEmp() << " : ";
           cin >> choiceEdit;
           //validating whether the choice is one of existed employees
           while (choiceEdit  < 1 || choiceEdit > numRecordEmp())
           {
               cout << "Please enter a valid choice (1 to " << numRecordEmp() << "): ";
               cin >> choiceEdit;
           }
           
           //display the employee data to edit
           empFileOpen();
           employees.seekg(sizeof(emp)*(choiceEdit-1), ios::beg);
           employees.read(reinterpret_cast<char *>(&emp), sizeof(emp));
           cout << endl << "Display Employee Details:" << endl;
           cout << left << setw(9) << "ID     : " << choiceEdit << endl;
           cout << left << setw(9) << "Name   : " << emp.employeeName << endl;
           cout << left << setw(9) << "Salary : $" << emp.employeeSalary << endl;
           cout << left << setw(9) << "Age    : " << emp.employeeAge << endl;
           cout << left << setw(9) << "Dept   : " << emp.employeeDepartmentID << endl << endl;
                         
           //editing the employee data except the employee ID     
           cout << "Edit the Employee Data:" << endl;
           emp.employeeID = choiceEdit;
           cin.ignore();
           cout << "Employee Name: ";
           getline(cin, input);
           strcpy(emp.employeeName, input.c_str());
           cout << "Employee Salary: $";
           cin >> emp.employeeSalary;
           cout << "Employee Age: ";
           cin >> emp.employeeAge;
           cout << "Department ID: ";
           cin >> emp.employeeDepartmentID;
           emp.employeeDepartmentID = vdEmployeeDepID(emp.employeeDepartmentID);
           
           employees.seekp(sizeof(emp)*(choiceEdit-1), ios::beg);
           employees.write(reinterpret_cast<char *>(&emp), sizeof(emp));
           employees.close();
       }
       
       else if (charSelection == '5')   //in case of displaying salary report by department
       {
           cout << endl << "Salary Report By Department" << endl;
           
           countRecordDep = numRecordDep();
           int totalSalary[countRecordDep];
           
           depFileOpen();
           for (int p=0;  p < countRecordDep ; p++)         //Calculating the total salary for each department
           {
                departments.seekg(p*sizeof(dep), ios::beg);
                departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
                            
                totalSalary[p] = 0;
                countRecordEmp = numRecordEmp();      
                 
                empFileOpen();
                for (int m=0; m < countRecordEmp ; m++)
                {
                    employees.seekg(m*sizeof(emp), ios::beg);
                    employees.read(reinterpret_cast<char *>(&emp), sizeof(emp) );
                                 
                    if (dep.departmentID == emp.employeeDepartmentID) 
                         totalSalary[p] += emp.employeeSalary;
                }
                employees.close();
                
                cout << endl;            
                cout << left << setw(13) << "Dept" << ": " << dep.departmentName << endl;
                cout << left << setw(13) << "Total Salary" << ": $" << totalSalary[p] << endl;
           }    
                        
           departments.close(); 
       }
       
    }while (charSelection != '6');
    
    cout << "Thank you, goodbye.";
 
    return 0;
}




void depFileOpen()     // Function for opening a department file as binary (both input and output)
{
    departments.open("departments.dat", ios::in | ios::out | ios::binary);
    if (departments.fail())
    {
        departments.open("departments.dat", ios::out | ios::in | ios::binary | ios::trunc);
        if (departments.fail())
        {
            cout << "Error opening department file....";
            
        }
        
    }
}

void empFileOpen()     // Function for opening a employee file as binary (both input and output)
{
    employees.open("employees.dat", ios::in | ios::out | ios::binary);
    if (employees.fail())
    {
        employees.open("employees.dat", ios::out | ios::in | ios::binary | ios::trunc);
        if (employees.fail())
        {
            cout << "Error opening employee file....";
            
        }
    }
}    



void displayMenu()    // function for displaying menu
{
    cout << endl;
    cout << "Human Resources Menu" << endl;
    cout << "1. Create Department" << endl;
    cout << "2. Create Employee" << endl;
    cout << "3. Edit Department" << endl;
    cout << "4. Edit Employee" << endl;
    cout << "5. Display Salary Report" << endl;
    cout << "6. -- Quit -- " << endl;
}

void validation(char &sel)   //Funtion for validating the choice at the beginning menu
{
    while (sel <= '0' || sel >= '7')      //validating the variable of Selection
       {   
           cout << "Please enter a valid choice (1 - 6): ";
           cin >> sel;
       }
}
        
int vdDepartmentID(int depID)          //Validating the department ID
{
    while (depID <= 0)              
    {
        cout << "Please enter the positive number: ";
        cin >> depID;
        
    }
    
    depFileOpen();
    departments.seekg(0L, ios::beg);
    departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
    while (!departments.eof())
    {
        while (depID == dep.departmentID)
        {
            cout << "Please enter a unique Deptartment ID: ";
            cin >> depID;
        }
        departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
    }
    
    departments.close();
    return depID;
}

int vdEmployeeID(int empID)          //Validating the employee ID
{
    while (empID <= 0)              
    {
        cout << "Please enter the positive number: ";
        cin >> empID;
    }
    
    empFileOpen();
    employees.seekg(0L, ios::beg);
    employees.read(reinterpret_cast<char *>(&emp), sizeof(emp));
    while (!employees.eof() )
    {
        while (empID == emp.employeeID)
        {
            cout << "Please enter a unique Employee ID: ";
            cin >> empID;
        }
        employees.read(reinterpret_cast<char *>(&emp), sizeof(emp));
    }
    
    employees.close();
    return empID;
}

int vdEmployeeDepID(int empDepID)   //Validating the employee's department ID
{
    bool flag;
    flag = false;
    while (!flag)
    {
        depFileOpen();
        departments.seekg(0L, ios::beg);
        departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
        while (!departments.eof() && !flag)
        {
            if (dep.departmentID == empDepID)
                flag = true;
            departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
        }
        
        departments.close();

        if (!flag)
        {
            cout << "Please enter an existing Deptartment ID: ";
            cin >> empDepID;
        }
    }
    return empDepID;
}

int  numRecordDep()     //Return the number of records in departments file
{
    int count = 0;
    depFileOpen();
    departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
    while (!departments.eof() )
    {
        count++;
        departments.read(reinterpret_cast<char *>(&dep), sizeof(dep));
    }
    
    departments.close();
    return count;
}

int  numRecordEmp()      //Return the number of records in employees file
{
    int count = 0;
    empFileOpen();
    employees.read(reinterpret_cast<char *>(&emp), sizeof(emp));
    while (!employees.eof() )
    {
        count++;
        employees.read(reinterpret_cast<char *>(&emp), sizeof(emp));
    }
    
    employees.close();
    return count;
}