#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CharactersManager.h"
#include "SystemBase.h"

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int _SizeOfMap = 21;
int _AreaInView[9] = { 0 };


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GameStart() {
	SetRandSeed();
	if (!GenerateMap(_SizeOfMap)) {
		exit(2);
	}
	ReadMapSinglePoint(1, 1, _SizeOfMap);
	return 1;
}

int PlayerFight(Combater* _combaterCompeter) {
	if ((&_CombaterPlayer)==Fight(&_CombaterPlayer, _combaterCompeter, 100)) {
		WinTheFight(&_CombaterPlayer, _EXPForOneFight);
	}

}

int EnemyMenu(int _numOfenemy) {
	int enemyChosen = Menu(_numOfenemy, _CombaterEnemysName, "选择您想攻击的敌人：");
	return enemyChosen;
}

int MoveMenu() {
	int dirChosen=Menu(_NumOfDir, _DirName, "选择要前往的方向：");
	system("cls");
	return dirChosen;
}

int PlayerMover() {
	PlayerMove(MoveMenu(), _SizeOfMap,_AreaInView);
}

int main(void) {
	GameStart();
	RegisterPlayer(&_CombaterPlayer);
	ReadMapArea(10, 10, _SizeOfMap, _AreaInView);

	
	
	while (1)
	{
		PlayerMover();
	}
	

		
}

