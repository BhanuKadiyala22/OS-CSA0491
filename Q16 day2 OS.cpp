#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee_data.dat"
#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50

struct Employee {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};

void add_employee() {
    struct Employee emp;
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
    printf("Employee added successfully.\n");
}

void search_employee(int id) {
    struct Employee emp;
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee ID: %d\n", emp.id);
            printf("Employee Name: %s\n", emp.name);
            printf("Employee Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(file);
}

void update_employee(int id) {
    struct Employee emp;
    FILE *file = fopen(FILENAME, "r+b");
    if (file == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file)) {
        if (emp.id == id) {
            printf("Enter new name for employee: ");
            scanf("%s", emp.name);
            printf("Enter new salary for employee: ");
            scanf("%f", &emp.salary);
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            printf("Employee details updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(file);
}

int main() {
    int choice, id;
    do {
        printf("\nEmployee Record System\n");
        printf("1. Add New Employee\n");
        printf("2. Search Employee by ID\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                printf("Enter employee ID to search: ");
                scanf("%d", &id);
                search_employee(id);
                break;
            case 3:
                printf("Enter employee ID to update: ");
                scanf("%d", &id);
                update_employee(id);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
