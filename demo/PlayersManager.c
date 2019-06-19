#include "CharactersManager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////外部方法///////////
extern char* TipForString(char *_tip, char* _input, int _max);
extern int ShowLevelUp(Combater* _combater);
extern int ShowTip(char* _sentence, int _color);
///////////////////////////////


//角色等级数据
extern const  int _NumOfLevel;
extern const  int _EXP[6];
extern const  int _EXPForOneFight;
extern const  int _MAXLevel;

//升级相关
int GetEXP(Combater* _player,int _exp) {
	_player->fighterExperience += _exp;
	return 1;
}



int IsLevelUp(Combater* _player) {
	if (_player->fighterLevel >= _MAXLevel) {
		ShowTip("你满级了！",31);
		return 0;
	}

	if (_player->fighterExperience >= _EXP[_player->fighterLevel + 1]){		
			return 1;
		}

	return 0;
	}

int AbilitiesLevelUp(Combater* _player) {
	_player->fighterAttack *= 1.5;
	_player->fighterDefend *= 1.5;
	_player->fighterSpeed  *= 1.5;
	return 1;
}

int HPLevelUp(Combater* _player) {
	_player->fighterHPMAX *= 1.5;
	_player->fighterHP = _player->fighterHPMAX;
	return 1;
}

int LevelUp(Combater* _player) {
	_player->fighterLevel++;
	AbilitiesLevelUp(_player);
	HPLevelUp(_player);
	_player->fighterExperience = 0;
	ShowLevelUp(_player);
	return 1;
}


int EXP2Level(Combater* _player,int _exp) {
	GetEXP(_player, _exp);
	while (IsLevelUp(_player)) {
		LevelUp(_player);
	}
	return 1;
}

//战斗相关

int WinTheFight(Combater* _player,int _exp) {
	
	EXP2Level(_player, _exp);
	
}



//注册角色名字
int RegisterPlayer(Combater* _player) {
	char name[20];
	TipForString("请输入您的角色名字", name, 20);
	strcpy(_player->fighterName, name);
	return 1;
}