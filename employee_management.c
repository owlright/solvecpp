#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

typedef enum { true = 1, false = 0 } bool;
typedef struct _ {
    char name[50];
    int id;
    int salary;
    char position[50];
    char department[50];
} Employee;
Employee* employees[MAX_EMPLOYEES];
bool is_valid_id(int id)
{
    if (id >= 0 && id < MAX_EMPLOYEES)
        return true;
    return false;
}

void print_employee(Employee* employee)
{
    printf("Name: %s\n", employee->name);
    printf("ID: %d\n", employee->id);
    printf("Salary: %d\n", employee->salary);
    printf("Position: %s\n", employee->position);
    printf("Department: %s\n", employee->department);
}

void insert_employee(Employee* emp)
{
    int id = emp->id;
    if (is_valid_id(id)) {
        if (employees[id] != NULL) {
            printf("employee with id %d already exists.\n\n", id);
            return;
        } else {
            Employee* new_emp = (Employee*)malloc(sizeof(Employee));
            if (new_emp) {
                memcpy(new_emp, emp, sizeof(Employee));
                employees[id] = new_emp;
                print_employee(new_emp);
                printf("employee inserted successfully.\n\n");
            } else {
                printf("memory allocation failed.\n\n");
            }
        }
    } else {
        printf("invalid employee id.\n\n");
    }
}

int count_employees_in_department(char department[])
{
    int count = 0;
    for (int i = 0; i < MAX_EMPLOYEES; i++) {
        if (employees[i] != NULL && strcmp(employees[i]->department, department) == 0) {
            count++;
        }
    }
    return count;
}

int main()
{
    Employee emp1 = { "Alice", 1, 50000, "Manager", "HR" };
    Employee emp2 = { "Bob", 2, 60000, "Developer", "IT" };
    Employee emp3 = { "Charlie", 3, 55000, "Analyst", "Finance" };
    Employee emp4 = { "David", 4, 45000, "Assistant", "HR" };
    Employee emp5 = { "Eve", 5, 70000, "Director", "Marketing" };

    insert_employee(&emp1);
    insert_employee(&emp1);
    insert_employee(&emp2);
    insert_employee(&emp3);
    insert_employee(&emp4);
    insert_employee(&emp5);
    printf("Three are %d people in HR", count_employees_in_department("HR"));
    for (int i = 0; i < MAX_EMPLOYEES; i++) {
        free(employees[i]);
    }
    return 0;
}