#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char department[30];
    int semester;
    char email[60];
    char phone[20];

    float cProgramming;
    float dataStructure;
    float mathematics;
} Student;

/* Function declarations */
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void studentResult();

void clearInputBuffer();
void pauseScreen();
void calculateResult(Student student);

/* Clear input buffer */
void clearInputBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

/* Pause screen */
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}

/* Add Student */
void addStudent() {
    FILE *file;
    Student student;

    printf("\n========================================\n");
    printf("             ADD STUDENT\n");
    printf("========================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &student.id);
    clearInputBuffer();

    /* Check if student ID already exists */
    file = fopen(FILE_NAME, "rb");

    if (file != NULL) {
        Student temp;

        while (fread(&temp, sizeof(Student), 1, file)) {
            if (temp.id == student.id) {
                printf("\nStudent ID already exists!\n");
                fclose(file);
                pauseScreen();
                return;
            }
        }

        fclose(file);
    }

    printf("Enter Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &student.age);
    clearInputBuffer();

    printf("Enter Gender: ");
    fgets(student.gender, sizeof(student.gender), stdin);
    student.gender[strcspn(student.gender, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(student.department, sizeof(student.department), stdin);
    student.department[strcspn(student.department, "\n")] = '\0';

    printf("Enter Semester: ");
    scanf("%d", &student.semester);
    clearInputBuffer();

    printf("Enter Email: ");
    fgets(student.email, sizeof(student.email), stdin);
    student.email[strcspn(student.email, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(student.phone, sizeof(student.phone), stdin);
    student.phone[strcspn(student.phone, "\n")] = '\0';

    printf("\nEnter Marks:\n");

    printf("C Programming: ");
    scanf("%f", &student.cProgramming);

    printf("Data Structures: ");
    scanf("%f", &student.dataStructure);

    printf("Mathematics: ");
    scanf("%f", &student.mathematics);

    clearInputBuffer();

    /* Open file for adding the student */
    file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        perror("\nUnable to create/open students.dat");
        pauseScreen();
        return;
    }

    fwrite(&student, sizeof(Student), 1, file);

    fclose(file);

    printf("\nStudent added successfully!\n");

    pauseScreen();
}

/* View all students */
void viewStudents() {
    FILE *file;
    Student student;
    int count = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        pauseScreen();
        return;
    }

    printf("\n====================================================================\n");
    printf("                     ALL STUDENTS\n");
    printf("====================================================================\n");

    printf("%-8s %-20s %-15s %-10s %-8s\n",
           "ID", "Name", "Department", "Semester", "Age");

    printf("--------------------------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, file)) {
        printf("%-8d %-20s %-15s %-10d %-8d\n",
               student.id,
               student.name,
               student.department,
               student.semester,
               student.age);

        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("No student records found.\n");
    }

    pauseScreen();
}

/* Search student */
void searchStudent() {
    FILE *file;
    Student student;
    int choice;
    int id;
    char name[50];
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        pauseScreen();
        return;
    }

    printf("\n========================================\n");
    printf("           SEARCH STUDENT\n");
    printf("========================================\n");

    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        printf("Enter Student ID: ");
        scanf("%d", &id);
        clearInputBuffer();

        while (fread(&student, sizeof(Student), 1, file)) {
            if (student.id == id) {
                found = 1;

                printf("\nStudent Found!\n");
                printf("----------------------------------------\n");
                printf("ID          : %d\n", student.id);
                printf("Name        : %s\n", student.name);
                printf("Age         : %d\n", student.age);
                printf("Gender      : %s\n", student.gender);
                printf("Department  : %s\n", student.department);
                printf("Semester    : %d\n", student.semester);
                printf("Email       : %s\n", student.email);
                printf("Phone       : %s\n", student.phone);

                calculateResult(student);

                break;
            }
        }
    }
    else if (choice == 2) {
        printf("Enter Student Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        while (fread(&student, sizeof(Student), 1, file)) {
            if (strcasecmp(student.name, name) == 0) {
                found = 1;

                printf("\nStudent Found!\n");
                printf("----------------------------------------\n");
                printf("ID          : %d\n", student.id);
                printf("Name        : %s\n", student.name);
                printf("Age         : %d\n", student.age);
                printf("Gender      : %s\n", student.gender);
                printf("Department  : %s\n", student.department);
                printf("Semester    : %d\n", student.semester);
                printf("Email       : %s\n", student.email);
                printf("Phone       : %s\n", student.phone);

                calculateResult(student);
            }
        }
    }
    else {
        printf("\nInvalid choice!\n");
    }

    fclose(file);

    if (!found) {
        printf("\nStudent not found.\n");
    }

    pauseScreen();
}

/* Update student */
void updateStudent() {
    FILE *file;
    Student student;

    int id;
    int found = 0;

    file = fopen(FILE_NAME, "r+b");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        pauseScreen();
        return;
    }

    printf("\n========================================\n");
    printf("           UPDATE STUDENT\n");
    printf("========================================\n");

    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    while (fread(&student, sizeof(Student), 1, file)) {

        if (student.id == id) {
            found = 1;

            printf("\nStudent found: %s\n", student.name);

            printf("\nEnter new information:\n");

            printf("Name: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0';

            printf("Age: ");
            scanf("%d", &student.age);
            clearInputBuffer();

            printf("Gender: ");
            fgets(student.gender, sizeof(student.gender), stdin);
            student.gender[strcspn(student.gender, "\n")] = '\0';

            printf("Department: ");
            fgets(student.department, sizeof(student.department), stdin);
            student.department[strcspn(student.department, "\n")] = '\0';

            printf("Semester: ");
            scanf("%d", &student.semester);
            clearInputBuffer();

            printf("Email: ");
            fgets(student.email, sizeof(student.email), stdin);
            student.email[strcspn(student.email, "\n")] = '\0';

            printf("Phone: ");
            fgets(student.phone, sizeof(student.phone), stdin);
            student.phone[strcspn(student.phone, "\n")] = '\0';

            printf("\nEnter updated marks:\n");

            printf("C Programming: ");
            scanf("%f", &student.cProgramming);

            printf("Data Structures: ");
            scanf("%f", &student.dataStructure);

            printf("Mathematics: ");
            scanf("%f", &student.mathematics);

            clearInputBuffer();

            /*
             * Move file pointer back to the beginning
             * of the current student record.
             */
            fseek(file, -(long)sizeof(Student), SEEK_CUR);

            fwrite(&student, sizeof(Student), 1, file);

            printf("\nStudent updated successfully!\n");

            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nStudent ID not found.\n");
    }

    pauseScreen();
}

/* Delete student */
void deleteStudent() {
    FILE *file;
    FILE *tempFile;

    Student student;

    int id;
    int found = 0;
    char confirmation;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        pauseScreen();
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    printf("\n========================================\n");
    printf("           DELETE STUDENT\n");
    printf("========================================\n");

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    while (fread(&student, sizeof(Student), 1, file)) {

        if (student.id == id) {
            found = 1;

            printf("\nStudent found: %s\n", student.name);

            printf("Are you sure you want to delete this student? (Y/N): ");
            scanf("%c", &confirmation);
            clearInputBuffer();

            if (confirmation == 'Y' || confirmation == 'y') {
                printf("\nStudent deleted successfully!\n");
            }
            else {
                fwrite(&student, sizeof(Student), 1, tempFile);
                printf("\nDeletion cancelled.\n");
            }
        }
        else {
            fwrite(&student, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        remove("temp.dat");
        printf("\nStudent ID not found.\n");
    }
    else {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
    }

    pauseScreen();
}

/* Calculate and display result */
void calculateResult(Student student) {

    float total;
    float average;
    char grade;

    total = student.cProgramming +
            student.dataStructure +
            student.mathematics;

    average = total / 3;

    if (average >= 90)
        grade = 'A';
    else if (average >= 80)
        grade = 'B';
    else if (average >= 70)
        grade = 'C';
    else if (average >= 60)
        grade = 'D';
    else if (average >= 50)
        grade = 'E';
    else
        grade = 'F';

    printf("\nResult\n");
    printf("----------------------------------------\n");
    printf("C Programming : %.2f\n", student.cProgramming);
    printf("Data Structure: %.2f\n", student.dataStructure);
    printf("Mathematics   : %.2f\n", student.mathematics);
    printf("----------------------------------------\n");
    printf("Total         : %.2f / 300\n", total);
    printf("Average       : %.2f\n", average);
    printf("Percentage    : %.2f%%\n", average);
    printf("Grade         : %c\n", grade);
}

/* Student result */
void studentResult() {
    FILE *file;
    Student student;

    int id;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        pauseScreen();
        return;
    }

    printf("\n========================================\n");
    printf("           STUDENT RESULT\n");
    printf("========================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    while (fread(&student, sizeof(Student), 1, file)) {

        if (student.id == id) {
            found = 1;

            printf("\nStudent: %s\n", student.name);
            printf("Department: %s\n", student.department);

            calculateResult(student);

            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("\nStudent not found.\n");
    }

    pauseScreen();
}

/* Main function */
int main() {

    int choice;

    while (1) {

        printf("\n\n");
        printf("========================================\n");
        printf("      STUDENT RECORD MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Student Result\n");
        printf("7. Exit\n");

        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                studentResult();
                break;

            case 7:
                printf("\nThank you for using Student Record Management System!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
                pauseScreen();
        }
    }

    return 0;
}