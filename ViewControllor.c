#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "CharactersManager.h"
#include "SystemBase.h"
/////////////////////////////////////////////////////////////
typedef enum Color
{
	black=30, red, green, yellow, blue,purple,deepgreen,white
}color;

color _MapColorCol[20] = { white , green,yellow,red,white};

char _CNNameOfMapPoint[20][20] = { "路" ,"山","商","敌"};
char _ENNameOfMapPoint[20] = "RMSEP";

int  _NumOfView = 9;
int  _NumOfColView = 3;

//////////////////////////////////////////////////////////
color GetColor(Combater* _combater) {
	return (_combater->isPlayer ? blue : red);
}

int ShowDamage(Combater* _combater0,Combater* _combater1, char _skillsName[10], int _damage,int _isTooMuch) {
	printf("\033[1;%dm%s\033[m 使用 \033[1;36m%s\033[m 给 \033[1;%dm%s\033[m 造成了 \033[1;35m%d\033[m 点伤害！", GetColor(_combater0), _combater0->fighterName,_skillsName, GetColor(_combater1),_combater1->fighterName,_damage);
	if (_isTooMuch) {
		printf("\033[1; %dm效果拔群！\033[m",purple);
	}
	printf("\n");
	return 1;
}

int ShowDead(Combater* _combaterDead) {
	printf("\033[1;%dm%s\033[m 被打败了!\n", GetColor(_combaterDead), _combaterDead->fighterName);
	return 1;
}

int ShowWinner(Combater* _combater) {
	if (_combater) {
		printf("胜者是：\033[1;%dm%s\033[m!\n",GetColor(_combater), _combater->fighterName);
	}
	else {
		printf("打平了！\n");
	}
	return 1;
}



char* TipForString(char *_tip,char* _input,int _max) {
	printf("%s:", _tip);
	return GetString(_input, _max);
}

int ShowLevelUp(Combater *_combater) {
	printf("\033[1;34m%s\033[m 升级了！当前等级是%d级。\n", _combater->fighterName, _combater->fighterLevel);
}

int GetMenuInput(int _numOfmenu) {
	int input;
	scanf("%d",&input );
	if (input <0 || input > _numOfmenu) {
		printf("输入无效！请重新输入\n");
		return 0;
	}
	else {
		return (input);
	}
}

int ShowTip(char* _sentence,int _color) {
	printf("\033[1;%dm%s\033[m\n", _color, _sentence);
	//puts(_sentence);
}

int ShowMenu(int _numOfMenu,char _menu[][20], char* _guideSentence) {
	puts(_guideSentence);
	for (int i = 0; i < _numOfMenu; i++) {
		printf("%d:", i + 1);
		puts(_menu[i]);
	}
}

int Menu(int _numOfMenu, char _menu[][20], char* _guideSentence) {
	ShowMenu(_numOfMenu, _menu, _guideSentence);
	int tempInput;
	while (!(tempInput=GetMenuInput(_numOfMenu)))
	{
		continue;
	}
	return (tempInput-1);
}

color ChooseMapPointColor(int _typeOfMapPoint) {
	return _MapColorCol[_typeOfMapPoint];
}

char GetMapPointName(int _typeOfMapPoint) {
	return  _ENNameOfMapPoint[_typeOfMapPoint];
}

//\033[1;%dm└──────┘\033[m
int DrawMapPiece(int _typeOfMapPoint0,int _typeOfMapPoint1,int _typeOfMapPoint2,int _isPlayer) {
	color	mapPoint0Color = ChooseMapPointColor(_typeOfMapPoint0), 
			mapPoint1Color = ChooseMapPointColor(_typeOfMapPoint1), 
			mapPoint2Color = ChooseMapPointColor(_typeOfMapPoint2);

	char	mapPoint0Name = GetMapPointName(_typeOfMapPoint0),
			mapPoint1Name = GetMapPointName(_typeOfMapPoint1),
			mapPoint2Name = GetMapPointName(_typeOfMapPoint2);
	if (_isPlayer == 1)mapPoint1Color = purple;
	printf("\033[1;%dm┌──────┐\033[m\033[1;%dm┌──────┐\033[m\033[1;%dm┌──────┐\033[m\n", mapPoint0Color, mapPoint1Color, mapPoint2Color);
	printf("\033[1;%dm│  %c   │\033[m\033[1;%dm│  %c   │\033[m\033[1;%dm│  %c   │\033[m\n", mapPoint0Color, mapPoint0Name, mapPoint1Color, mapPoint1Name, mapPoint2Color, mapPoint2Name);
	printf("\033[1;%dm└──────┘\033[m\033[1;%dm└──────┘\033[m\033[1;%dm└──────┘\033[m\n", mapPoint0Color, mapPoint1Color, mapPoint2Color);
	
	return 1;
}
//0 1 2 /0
//3 4 5 /1
//6 7 8 /2
int DrawWholeViewMap(int _mapInView[9]) {
	for (int i = 0; i < _NumOfColView; i++) {
		if (i == 1) {
			DrawMapPiece(_mapInView[3 * i], _mapInView[3 * i + 1], _mapInView[3 * i + 2], 1);
		}
		else {
			DrawMapPiece(_mapInView[3 * i], _mapInView[3 * i + 1], _mapInView[3 * i + 2], 0);

		}
	}
	return 1;
}




