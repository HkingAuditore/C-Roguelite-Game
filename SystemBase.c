
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "SystemBase.h"



//�������ȡ
int GetRandNumber() {
	//srand((unsigned)time(NULL));
	int randnum = rand();
	return randnum;
}

//Ȩ�������
int GetPowerNumber(int _power) {
	int randNum = GetRandNumber() % (_power + 1);
	return randNum;
}

//�趨�������
int SetRandSeed() {
	srand((unsigned)time(NULL));
	return 1;
}

//�����ַ���
char* GetString(char* _input, int _max) {
	char* temp;
	int i=0;
	temp = fgets(_input, _max, stdin);
	if (temp) {
		while (_input[i]!='\n' && _input[i]!='\0')
		{
			i++;
		}
		if (_input[i] == '\n') {
			_input[i] = '\0';
		}
		else {
			while (getchar()!='\n')
			{
				continue;
			}
		}
	}
	return temp;
}

//int�������
int SumCol(const int *_target,int _numOfTarget) {
	int sum=0;
	for (int i = 0; i < _numOfTarget; i++) {
		sum += _target[i];
	}
	return sum;
}

int CharToInt(char _char) {
	int result =_char - '0';

	return result;
}


