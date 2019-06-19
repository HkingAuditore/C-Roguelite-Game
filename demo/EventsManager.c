#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CharactersManager.h"
#include "SystemBase.h"
#include "EventsManager.h"

//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////外部方法/////////////

extern int *ChooseSkill(int _numOfSkill);

extern int IsDead(Combater* _combater);
extern int FightCycles(Combater* _combaterFirst, Combater* _combaterSecond, int _maxRound);
extern int ShowWinner(Combater* _combater);
extern int Fight(Combater* _combater0, Combater* _combater1, int _maxRound);
extern int RegisterPlayer(Combater* _player);
extern int WinTheFight(Combater* _player, int _exp);
extern int Menu(int _numOfMenu, char _menu[][20], char* _guideSentence);
extern int GenerateMap(int _mapSize_MUSTBESINGLE);
extern int ReadMapSinglePoint(int _posX, int _posY, int _mapSize);
extern int ReadMapArea(int _posX, int _posY, int _mapSize, int _mapAreaData[9]);
extern int PlayerMove(int _inputDir, int _mapSize, int _mapAreaData[9]);
/////////////////外部数据/////////////////////
extern Combater *_Combaters[10];
extern Combater _CombaterPlayer;
extern const  int _EXPForOneFight;
extern char _CombaterEnemysName[20][20];
extern int _NumOfDir;
extern char _DirName[4][20];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//内部数据//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int _NumOfEnemy = 3;
int _EnemyRandPower[3] = {10,10,10    };



//////////////////////////////////////////////////////
int SignUpEvent() {

}

int FightEvent(Combater* _enemy,int _maxRound) {
	Combater * enemyChosen = _Combaters[0];

	if (!_enemy) {
		enemyChosen=_Combaters[GetPowerResult(_NumOfEnemy,_EnemyRandPower)];
	}
	else {
		enemyChosen = _enemy;
	}

	if ((&_CombaterPlayer) == Fight(&_CombaterPlayer, enemyChosen, _maxRound)) {
		WinTheFight(&_CombaterPlayer, _EXPForOneFight);
	}
}

int ShopEvent(int _shopList[]) {

}

int IncidentEvent(char _Sentence[], int _gain) {

}
