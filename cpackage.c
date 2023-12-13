#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    int age;
    float salary;
    struct Employee* next;
};

typedef struct Employee Employee;

int is_duplicate_id(Employee* head, int id) {
    Employee* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return 1; // true, duplicate found
        }
        current = current->next;
    }
    return 0; // false, no duplicate
}

Employee* add_employee(Employee* head, int id, const char* name, int age, float salary) {
    if (is_duplicate_id(head, id)) {
        printf("Employee with ID %d already exists. Please enter a different ID.\n", id);
        return head;
    }

    Employee* new_employee = (Employee*)malloc(sizeof(Employee));
    new_employee->id = id;
    strcpy(new_employee->name, name);
    new_employee->age = age;
    new_employee->salary = salary;
    new_employee->next = NULL;

    if (head == NULL) {
        return new_employee;
    }

    Employee* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_employee;
    return head;
}

Employee* search_employee(Employee* head, int id) {
    Employee* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void update_employee_details(Employee* employee, const char* attribute, const char* value) {
    if (employee != NULL) {
        if (strcmp(attribute, "name") == 0) {
            strcpy(employee->name, value);
        } else if (strcmp(attribute, "age") == 0) {
            employee->age = atoi(value);
        } else if (strcmp(attribute, "salary") == 0) {
            employee->salary = atof(value);
        } else {
            printf("Invalid attribute.\n");
        }
    } else {
        printf("Employee not found.\n");
    }
}

Employee* delete_employee(Employee* head, int id) {
    Employee* current = head;
    Employee* previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            printf("Employee with ID %d deleted.\n", id);
            free(current);
            return head;
        }

        previous = current;
        current = current->next;
    }

    printf("Employee not found with ID %d.\n", id);
    return head;
}

void display_employees(Employee* head) {
    printf("\nEmployee List:\n");
    if (head == NULL) {
        printf("No employees.\n");
        return;
    }

    Employee* current = head;
    printf("Id          Name            Age         Salary   \n");

    while (current != NULL) {
        printf("%-12d%-16s%-12d%-8.2f\n", current->id, current->name, current->age, current->salary);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Employee* employee_list = NULL;

    while (1) {
        char action;
        printf("Do you want to (A)dd an employee, (S)earch, (D)elete, (U)pdate an employee, or (Q)uit? ");
        scanf(" %c", &action);

        if (action == 'Q' || action == 'q') {
            break;
        } else if (action == 'A' || action == 'a') {
            int id, age;
            float salary;
            char name[50];

            printf("Enter employee ID: ");
            scanf("%d", &id);
            printf("Enter employee name: ");
            scanf("%s", name);
            printf("Enter employee age: ");
            scanf("%d", &age);
            printf("Enter employee salary: ");
            scanf("%f", &salary);

            employee_list = add_employee(employee_list, id, name, age, salary);
        } else if (action == 'S' || action == 's') {
            int search_id;
            printf("Enter ID to search: ");
            scanf("%d", &search_id);
            Employee* found_employee = search_employee(employee_list, search_id);
            if (found_employee != NULL) {
                printf("Employee found with ID %d:\nName: %s, Age: %d, Salary: %.2f\n",
                       found_employee->id, found_employee->name, found_employee->age, found_employee->salary);
            } else {
                printf("Employee not found with ID %d.\n", search_id);
            }
        } else if (action == 'U' || action == 'u') {
            int update_id;
            printf("Enter ID to update: ");
            scanf("%d", &update_id);
            Employee* employee_to_update = search_employee(employee_list, update_id);
            if (employee_to_update != NULL) {
                char attribute[10], value[50];
                printf("Enter attribute to update (name/age/salary): ");
                scanf("%s", attribute);
                printf("Enter updated %s: ", attribute);
                scanf("%s", value);

                update_employee_details(employee_to_update, attribute, value);
            } else {
                printf("Employee not found for updating.\n");
            }
        } else if (action == 'D' || action == 'd') {
            int delete_id;
            printf("Enter ID to delete: ");
            scanf("%d", &delete_id);
            employee_list = delete_employee(employee_list, delete_id);
        } else {
            printf("Invalid option. Please enter 'A', 'S', 'U', 'D', or 'Q'.\n");
        }

        // Displaying updated employee list
        display_employees(employee_list);
    }

    // Free allocated memory before exiting
    Employee* current = employee_list;
    while (current != NULL) {
        Employee* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
