#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBJECTS 10
#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    int marks[MAX_SUBJECTS];
    int subjectCount;
    float total;
    float average;
    char grade;
    int passed;
} Student;

char calculateGrade(float average) {
    if (average >= 90) return 'A';
    if (average >= 80) return 'B';
    if (average >= 70) return 'C';
    if (average >= 60) return 'D';
    if (average >= 50) return 'E';
    return 'F';
}

int main(void) {
    int studentCount, subjectCount;
    Student *students;
    int i, j;
    int topStudent = 0;
    float classAverage = 0.0;

    printf("========================================\n");
    printf("STUDENT MARKS REPORT PROGRAM\n");
    printf("========================================\n\n");

    printf("Enter number of students: ");
    scanf("%d", &studentCount);
    while (studentCount <= 0) {
        printf("Number of students must be greater than 0. Try again: ");
        scanf("%d", &studentCount);
    }

    printf("Enter number of subjects: ");
    scanf("%d", &subjectCount);
    while (subjectCount <= 0 || subjectCount > MAX_SUBJECTS) {
        printf("Number of subjects must be between 1 and %d. Try again: ", MAX_SUBJECTS);
        scanf("%d", &subjectCount);
    }

    students = (Student *)malloc(studentCount * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    for (i = 0; i < studentCount; i++) {
        students[i].subjectCount = subjectCount;
        students[i].total = 0.0;
        students[i].passed = 1;

        printf("\nEnter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);

        for (j = 0; j < subjectCount; j++) {
            do {
                printf("Marks in subject %d: ", j + 1);
                scanf("%d", &students[i].marks[j]);
                if (students[i].marks[j] < 0 || students[i].marks[j] > 100) {
                    printf("Invalid marks! Please enter a value between 0 and 100.\n");
                }
            } while (students[i].marks[j] < 0 || students[i].marks[j] > 100);

            students[i].total += students[i].marks[j];

            if (students[i].marks[j] < 40) {
                students[i].passed = 0;
            }
        }

        students[i].average = students[i].total / subjectCount;
        students[i].grade = calculateGrade(students[i].average);

        classAverage += students[i].average;

        if (students[i].average > students[topStudent].average) {
            topStudent = i;
        }
    }

    classAverage /= studentCount;

    printf("\n========================================\n");
    printf("STUDENT MARKS REPORT\n");
    printf("========================================\n");
    printf("\nName\t");
    for (j = 0; j < subjectCount; j++) {
        printf("Sub%d\t", j + 1);
    }
    printf("Total\tAverage\tGrade\tResult\n");

    for (i = 0; i < studentCount; i++) {
        printf("%s\t", students[i].name);
        for (j = 0; j < subjectCount; j++) {
            printf("%d\t", students[i].marks[j]);
        }
        printf("%.2f\t%.2f\t%c\t", students[i].total, students[i].average, students[i].grade);
        if (students[i].passed) {
            printf("Pass\n");
        } else {
            printf("Fail\n");
        }
    }

    printf("\nClass Average: %.2f\n", classAverage);
    printf("Top Student: %s (Average: %.2f, Grade: %c)\n",
           students[topStudent].name,
           students[topStudent].average,
           students[topStudent].grade);

    printf("\nThank you for using the Student Marks Report Program.\n");

    free(students);
    return 0;
}
