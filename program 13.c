#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for an employee record
struct Employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    FILE *file;
    struct Employee emp;
    int choice, empId;
    long int recordSize = sizeof(struct Employee);

    file = fopen("employee.dat", "r+");

    if (file == NULL) {
        file = fopen("employee.dat", "w+");
    }

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display All Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.id);
                printf("Enter Employee Name: ");
                scanf(" %49[^\n]", emp.name); // Read up to 49 characters for the name
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.salary);

                fseek(file, (emp.id - 1) * recordSize, SEEK_SET);
                fwrite(&emp, recordSize, 1, file);
                break;

            case 2:
                printf("Enter Employee ID to update: ");
                scanf("%d", &empId);

                fseek(file, (empId - 1) * recordSize, SEEK_SET);
                fread(&emp, recordSize, 1, file);

                printf("Employee Details: ID=%d, Name=%s, Salary=%.2f\n", emp.id, emp.name, emp.salary);
                printf("Enter new Employee Name: ");
                scanf(" %49[^\n]", emp.name);
                printf("Enter new Employee Salary: ");
                scanf("%f", &emp.salary);

                fseek(file, (empId - 1) * recordSize, SEEK_SET);
                fwrite(&emp, recordSize, 1, file);
                break;

            case 3:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &empId);

                fseek(file, (empId - 1) * recordSize, SEEK_SET);
                emp.id = 0; // Mark the record as deleted
                fwrite(&emp, recordSize, 1, file);
                break;

            case 4:
                rewind(file);
                printf("Employee Records:\n");
                while (fread(&emp, recordSize, 1, file) == 1) {
                    if (emp.id > 0) {
                        printf("ID=%d, Name=%s, Salary=%.2f\n", emp.id, emp.name, emp.salary);
                    }
                }
                break;

            case 5:
                fclose(file);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
```
