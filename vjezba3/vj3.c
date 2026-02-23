#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_STR (64)
#define FILE_NOT_OPEN (-1)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_STR];
	char surname[MAX_STR];
	double birthYear;
	Position next;
}Person;

int addPersonFront(Position P) {
	Position newPerson = NULL;


	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("USpijeh");
		free(newPerson);
		return;
	}

	printf("\n Unesite podatke nove osobe: \n");
	fscanf("%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

	newPerson->next = P->next;
	P->next = newPerson;



	return EXIT_SUCCESS;
}

void printList(Position P) {
	Position temp = P;
	if (P == NULL)
		printf("Lista je prazna.\n");
	else {
		while (temp != NULL) {
			printf("%s %s %lf\n", temp->name, temp->surname, temp->birthYear);
			temp = temp->next;
		}
	}

	return EXIT_SUCCESS;
}

int addPersonEnd(Position P) {
	Position newPerson = NULL;


	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("USpijeh");
		free(newPerson);
		return;
	}

	printf("\n Unesite podatke nove osobe: \n");
	fscanf("%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

	while (P->next != NULL) {
		P = P->next;
	}

	newPerson->next = P->next;
	P->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindbySurmame(Position P, char* surname) {
	Position temp = P;
	while (temp != NULL && strcmp(temp->surname, surname) != 0) {
		temp = temp->next;
	}
	return temp;
}

void DeletePerson(Position P, char* surname) {
	Position temp = P;
	while (temp->next != NULL && strcmp(temp->next->surname, surname) != 0) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		printf("Ne postoji osoba sa tim prezimenom.\n");
		return;
	}
	Position toDelete = temp->next;
	temp->next = temp->next->next;
	free(toDelete);
}

int insertAfterP(Position P, char* surname) {
	Position temp = FindbySurmame(P, surname);
	if (temp == NULL) {
		printf("Ne postoji osoba sa tim prezimenom.\n");
		return;
	}
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("USpijeh");
		free(newPerson);
		return;
	}
	printf("\n Unesite podatke nove osobe: \n");
	fscanf("%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
	newPerson->next = temp->next;
	temp->next = newPerson;
	return EXIT_SUCCESS;
}

int insertBeforeP(Position P, char* surname) {
	Position temp = P;
	while (temp->next != NULL && strcmp(temp->next->surname, surname) != 0) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		printf("Ne postoji osoba sa tim prezimenom.\n");
		return;
	}
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("USpijeh");
		free(newPerson);
		return;
	}
	printf("\n Unesite podatke nove osobe: \n");
	fscanf("%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
	newPerson->next = temp->next;
	temp->next = newPerson;
	return EXIT_SUCCESS;
}

int sortList(Position P) {
	Position temp1 = P, temp2 = NULL;
	char tempName[MAX_STR], tempSurname[MAX_STR];
	double tempBirthYear;
	while (temp1 != NULL) {
		temp2 = temp1->next;
		while (temp2 != NULL) {
			if (strcmp(temp1->surname, temp2->surname) > 0) {
				strcpy(tempName, temp1->name);
				strcpy(tempSurname, temp1->surname);
				tempBirthYear = temp1->birthYear;
				strcpy(temp1->name, temp2->name);
				strcpy(temp1->surname, temp2->surname);
				temp1->birthYear = temp2->birthYear;
				strcpy(temp2->name, tempName);
				strcpy(temp2->surname, tempSurname);
				temp2->birthYear = tempBirthYear;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
	return EXIT_SUCCESS;
}

int ListtoFile(Position P, char* filename) {
	FILE* filePointer = NULL;
	filePointer = fopen("studenti.txt", "w");
	if (!filePointer) {
		printf("Greska pri otvaranju datoteke.\n");
		return FILE_NOT_OPEN;
	}

	while (P != NULL)
	{
		fprintf(filePointer, "%s %s %lf\n", P->name, P->surname, P->birthYear);
		P = P->next;
	}

	fclose(filePointer);

	return 0;
}

int readList(Position P) {
	FILE* filePointer = NULL;
	Position newPerson = NULL;

	filePointer = fopen("studenti.txt", "r");
	if (!filePointer) {
		printf("Greska pri otvaranju datoteke.\n");
		return FILE_NOT_OPEN;
	}

	while (!feof(filePointer))
	{
		newPerson = malloc(sizeof(Person));

		fscanf(filePointer, "%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
		newPerson->next = P->next;
		P->next = newPerson;

		P = P->next;
	}

	fclose(filePointer);

	return 0;
}


int main() {
	Person head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	Position P = &head;
	addPersonFront(P);
	addPersonEnd(P);
	printList(P->next);
	insertAfterP(P, "Prezime");
	insertBeforeP(P, "Prezime");
	printList(P->next);
	sortList(P->next);
	printList(P->next);
	ListtoFile(P->next, "studenti.txt");
	DeletePerson(P, "Prezime");
	printList(P->next);
	return EXIT_SUCCESS;
}