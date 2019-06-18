#pragma once
#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




//随机数获取
int GetRandNumber();

//权重随机数
int GetPowerNumber(int _power);

//设定随机种子
int SetRandSeed();

//输入字符串
char* GetString(char* _input, int _max);

//int数组求和
int SumCol(const int *_target, int _numOfTarget);

int CharToInt(char _char);

#endif // !SYSTEMBASE_H