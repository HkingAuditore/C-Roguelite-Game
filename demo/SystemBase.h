#pragma once
#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




//�������ȡ
int GetRandNumber();

//Ȩ�������
int GetPowerNumber(int _power);

//�趨�������
int SetRandSeed();

//�����ַ���
char* GetString(char* _input, int _max);

//int�������
int SumCol(const int *_target, int _numOfTarget);

int CharToInt(char _char);

int GetPowerResult(int _num, int _col[]);

#endif // !SYSTEMBASE_H