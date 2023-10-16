// vjezba1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_POINTS (15)
#define FILE_NOT_OPEN (-1)

typedef struct _student
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    double bodovi;

}Student;

int readNoRowsInFile()
{
    int counter = 0;

    FILE* filePointer = NULL;
    char buffer[MAX_SIZE] = { 0 };

    filePointer = fopen("students.txt", "r");
    if (!filePointer)
    {
        printf("Neuspjesno otvaranje datoteke.");
            return FILE_NOT_OPEN;
    }
    while (!feof(filePointer))
    {
        fgets(buffer, MAX_SIZE, filePointer);
        counter++;
    }


    fclose(filePointer);
    return counter;
}

Student* allmem(int noStudents)
{
    int counter = 0;
    FILE* filePointer = NULL;
    Student* students = NULL;

    students = (Student*)malloc(noStudents * sizeof(Student));

    if (!students)
    {
        printf("Neuspjela alokacija memorije \n");
        return NULL;

    }
}

int main()
{
       


        return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
