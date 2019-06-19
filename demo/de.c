#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct STUDENT {                 //DECLEAR THE STUDENT STRUCT TO SAVE THE DATAS OF STUDENT
	char license[100];
	int computer_number;
	int test_number;
};

int Searching_computer(int input, struct STUDENT student[], int num,int finder) {
	int i;
	for (i = 0; i < num; i++) {
		if (input == student[i].computer_number) {
			finder = i;
		}
	}
}

void ReadSTU(struct STUDENT student[] ,int number_of_students){
	int i;
	scanf_s("%d", &number_of_students);
	for (i = 0; i < number_of_students; i++) {
		scanf_s("%s%d%d", student[i].license, &student[i].computer_number, &student[i].test_number);         //READ THE DATA OF STUDENTS
	}
}


void Read_and_SearchCOM(int computer[], int Search_computer_num, struct STUDENT student[],int num,int finder[]) {
	int i;
	scanf_s("%d", &Search_computer_num);
	for (i = 0; i < Search_computer_num; i++) {
		scanf_s("%d", &computer[i]);
		Searching_computer(computer[i],student,num,finder[i]);
	}
}

int main()
{
	int number_of_students=0;
	int target_student[100] = { 0 };
	int i;
	int Search_computer_num=0, computer[100];
	int computer_finder[100];

	struct STUDENT student[100];

	ReadSTU(student, number_of_students);
	Read_and_SearchCOM(computer,Search_computer_num,student,number_of_students,computer_finder);

	/*for (i = 0; i < number_of_students; i++) {
		target_student[i] = Searching_computer(student[i].computer_number, computer, Search_computer_num);   //GET FLAG IF IT IS POSSIBLE
	}*/


	for (i = 0; i < Search_computer_num; i++) {                                                     //SERACH THE STUDENTS WHO HAS FLAG AND PRINT IT

			printf("%s %d %d\n", student[computer_finder[i]].license, student[computer_finder[i]].test_number);

	}
}

