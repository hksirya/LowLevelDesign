#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class Employee
{
private:
    int id;
    string name;
    int managerId;
    list<Employee>subOrdinate;

public:
    Employee(string name)
    {
        this->name=name;
        this->id=getUniqueId();
        this->managerId=0;
    }

    int getUniqueId()
    {
        static int EmpId=1;
        return EmpId++;
    }

    int getId() const{
        return id;
    }
    void setName(string name)
    {
        this->name=name;
    }

    void setId(int id)
    {
        this->id=id;
    }

    void setManagerId(int id)
    {
        this->managerId=id;
    }
    
    int getManagerId() const{
       return managerId;
    }
    
     string getName() const {
       return name;
    }

    void createSubordinates(Employee&employee)
    {
        subOrdinate.push_back(employee);
    }
    
    list<Employee> getSubOrdinates() const{
        return subOrdinate;
    }

};

class System {
    list<Employee> employees;
    unordered_map<int, Employee*> employeeMap;

public:
    System() {}

    void registerEmployee(Employee& employee) {
        employees.push_back(employee);
        employeeMap[employee.getId()] = &employees.back();
    }

    void registerManager(int empId, int managerId) {
        if (!employeeMap.count(empId) || !employeeMap.count(managerId)) {
            cout << "Your request was declined as the Manager ID or Employee ID does not Exist";
            return;
        }

        employeeMap[empId]->setManagerId(managerId);
        employeeMap[managerId]->createSubordinates(*employeeMap[empId]);
    }

    void printDetails(int empId) {
        if (employeeMap.find(empId) == employeeMap.end()) {
            cout << "Employee not found !" << endl;
            return;
        }

        cout << "ID : " << empId << "\t";
        cout << "| Name : " << employeeMap[empId]->getName() << "\t";
        
        int managerId = employeeMap[empId]->getManagerId();
        if (managerId != 0) {
            cout << "| Manager : " << employeeMap[managerId]->getName() << "\t";
        } else {
            cout << "| Manager : None\t";
        }
        cout << endl;
    }

    void printDetails(string prefix) {
        for (const auto& it : employees) {
            if (it.getName().substr(0, prefix.size()) == prefix) {
                cout << "ID : " << it.getId() << "\t";
                cout << "| Name : " << it.getName() << "\t";

                int managerId = it.getManagerId();
                if (managerId != 0) {
                    cout << "| Manager : " << employeeMap[managerId]->getName();
                } else {
                    cout << "| Manager : None";
                }
                cout << endl;
            }
        }
    }
    
   list<Employee> getSubordinates(int empId) {
     list<Employee> subordinateList;

    if (employeeMap.find(empId) == employeeMap.end()) {
        cout << "Employee not found !" << endl;
        return subordinateList; // Return an empty list
    }

    subordinateList = employeeMap[empId]-> getSubOrdinates();
    return subordinateList;
}
};

int main() {
    System sys;

    // Register employees
    Employee emp1("Alice");
    Employee emp2("Bob");
    Employee emp3("Charlie");
    Employee emp4("David");
    Employee emp5("Eva");
    Employee emp6("Frank");
    Employee emp7("Grace");
    Employee emp8("Helen");
    Employee emp9("Ivy");
    Employee emp10("Jack");

    sys.registerEmployee(emp1);
    sys.registerEmployee(emp2);
    sys.registerEmployee(emp3);
    sys.registerEmployee(emp4);
    sys.registerEmployee(emp5);
    sys.registerEmployee(emp6);
    sys.registerEmployee(emp7);
    sys.registerEmployee(emp8);
    sys.registerEmployee(emp9);
    sys.registerEmployee(emp10);

    // Register managers and subordinates
    sys.registerManager(emp2.getId(), emp1.getId());
    sys.registerManager(emp4.getId(), emp2.getId());
    sys.registerManager(emp5.getId(), emp2.getId());
    sys.registerManager(emp6.getId(), emp2.getId());
    sys.registerManager(emp8.getId(), emp7.getId());
    sys.registerManager(emp9.getId(), emp7.getId());
    sys.registerManager(emp10.getId(), emp7.getId());

    cout << "***************************************" << endl;
    cout << "************ Test Cases ****************" << endl;
    cout << "***************************************" << endl;
     cout<<endl<<endl;
      

    // Print details using name prefix
    cout << "* Details of Employees with name prefix 'Eva':" << endl;
    sys.printDetails("Eva");
     cout<<endl<<endl;
    cout << "* Details of Employees with name prefix 'G':" << endl;
    sys.printDetails("G");
    
     cout<<endl<<endl;
    cout << "* Details of Employees with name prefix 'Z':" <<endl;
    sys.printDetails("Z"); // No employees with this prefix
    
     cout<<endl<<endl;
     
    cout << "* Details of Manager 2 and Subordinates:" <<endl;
    sys.printDetails(emp2.getId());
    
     cout<<endl<<endl;
    cout << "* Details of Manager 7 and Subordinates:" << endl;
    sys.printDetails(emp7.getId());
    
     cout<<endl<<endl;
    // Attempt to register with non-existing IDs
    cout << "* Attempt to register with non-existing IDs:" << endl;
    sys.registerManager(100, 200); // Should print error message
    
    cout<<endl<<endl;
    // Attempt to print details for non-existing employee
    cout << "* Attempt to print details for non-existing employee:" << endl;
    sys.printDetails(1000); // Should print "Employee not found !"
    
     cout<<endl<<endl;
      // Test the getSubordinates function
    cout << "* Subordinates of Manager 2:" << endl;
    list<Employee> subordinatesOfManager2 = sys.getSubordinates(emp2.getId());
    for (const Employee& subordinate : subordinatesOfManager2) {
        cout << "Subordinate Name: " << subordinate.getName() << endl;
    }
     cout<<endl<<endl;
    // Test the getSubordinates function for non-existing employee
    cout << "* Subordinates of Non-Existing Employee:" << endl;
    list<Employee> subordinatesOfNonExisting = sys.getSubordinates(1000); // Non-existing ID
    if (subordinatesOfNonExisting.empty()) {
        cout << "Employee not found !" << endl;
    }
 cout<<endl<<endl;
    cout << "***************************************" << endl<<endl;

    return 0;
}
