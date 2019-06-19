#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CharactersManager.h"
#include "SystemBase.h"
#include "EventsManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////�ⲿ����/////////////

extern int RegisterPlayer(Combater* _player);
extern int Menu(int _numOfMenu, char _menu[][20], char* _guideSentence);
extern int GenerateMap(int _mapSize_MUSTBESINGLE);
extern int ReadMapArea(int _posX, int _posY, int _mapSize, int _mapAreaData[9]);
extern int PlayerMover(int _inputDir, int _mapSize, int _mapAreaData[9]);
/////////////////�ⲿ����/////////////////////
extern Combater *_Combaters[10];
extern Combater _CombaterPlayer;
extern const  int _EXPForOneFight;
extern char _CombaterEnemysName[20][20];
extern int _NumOfDir;
extern char _DirName[4][20];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int _SizeOfMap = 101;
int _AreaInView[9] = { 0 };


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GameStart() {
	SetRandSeed();
	if (!GenerateMap(_SizeOfMap)) {
		exit(2);
	}
	
	return 1;
}

int EnemyMenu(int _numOfenemy) {
	int enemyChosen = Menu(_numOfenemy, _CombaterEnemysName, "ѡ�����빥���ĵ��ˣ�");
	return enemyChosen;
}

int MoveMenu() {
	int dirChosen=Menu(_NumOfDir, _DirName, "ѡ��Ҫǰ���ķ���");
	system("cls");
	return dirChosen;
}

int PlayerMoverControllor() {
	PlayerMover(MoveMenu(), _SizeOfMap,_AreaInView);
}

int main(void) {
	GameStart();
	RegisterPlayer(&_CombaterPlayer);
	ReadMapArea(((_SizeOfMap+1)/2), ((_SizeOfMap + 1) / 2), _SizeOfMap, _AreaInView);

	
	
	while (1)
	{
		PlayerMoverControllor();
	}
	

		
}

