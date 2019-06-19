#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CharactersManager.h"
#include "SystemBase.h"
#include "EventsManager.h"

#define MAP_SAVE_POSITION "Map.txt"

///////////////////////////////////////////////

extern int ShowTip(char* _sentence, int _color);
extern int DrawWholeViewMap(int _mapInView[9]);







/////////////////////////////////////////////

const int _NumOfMapPoint = 4;
const int _SizeOfFeildOfView = 3;


FILE *_MapSavePosition;

/////////坐标管理/////////
typedef struct PlayerPosition
{
	int x;
	int y;

}Transform;

typedef enum MoveDir
{
	Nowhere, Forward, Backward, Left, Right
}Movedir;

Transform _PlayerTransform = { 51,51 };
char _DirName[4][20] = {"前","后","左","右"};

////////////地图管理///////////
typedef enum MapPoint
{
	Road,Mountain,Shop,Enemy,BornPos
}Mappoint;

const int _NumOfDir = 4;


int _MapPointPower[20] = {20,10,2,10};

//地图点随机生成
Mappoint RandomMapPointType(int _numOfMapPoint) {
	Mappoint mapPointType=Road;
	int stageSumOfPower[20] = {0};
/*	for (int i = 0; i < _numOfMapPoint;i++) {
		stageSumOfPower[i] = SumCol(_MapPointPower, i+1);
	}
	
	int tempRandom=GetPowerNumber(stageSumOfPower[_numOfMapPoint-1]);
	for (int i = 0; i < _numOfMapPoint; i++) {
		if (tempRandom <= stageSumOfPower[i]) {
			mapPointType = i;
			break;
		}
	}
*/
	mapPointType = (Mappoint)GetPowerResult(_numOfMapPoint, _MapPointPower);
	return mapPointType;
}

//地图生成
int GenerateMap(int _mapSize_MUSTBESINGLE) {
		
	if (!StartMapReading()) {
		return 0;
	}
		
	for (int i = 0; i < _mapSize_MUSTBESINGLE; i++) {
		for (int j = 0; j < _mapSize_MUSTBESINGLE; j++) {
			Mappoint mapPointType = Road;
			//Mappoint mapPointType = RandomMapPointType(_NumOfMapPoint);
			if (i == ((_mapSize_MUSTBESINGLE-1)/2) && j == ((_mapSize_MUSTBESINGLE-1)/2)) {
				//mapPointType = RandomMapPointType(_NumOfMapPoint);
				
				mapPointType = BornPos;

				/*测试用，记得删去*/
				//mapPointType = Road;
				/*测试用，记得删去*/
							
			}
			else {
				mapPointType = RandomMapPointType(_NumOfMapPoint);
				
			}
			fprintf(_MapSavePosition, "%d", mapPointType);
		}
		fprintf(_MapSavePosition, "\n");
	}

	//fclose(_MapSavePosition);
	EndMapReading();
	return 1;
}

//停止读图
int EndMapReading() {
	if (!fclose(_MapSavePosition)) {
		return 0;
	}
	return 1;
}

//开始读图
int StartMapReading() {
	if (!(_MapSavePosition = fopen(MAP_SAVE_POSITION, "r+"))) {
		ShowTip("地图加载失败！", 31);
		return 0;
	}
//	int b = ftell(_MapSavePosition);

	return 1;
}

//获取坐标在文件中的真正位置
int GetMapPosInData(int _posX, int _posY, int _actMapSize) {
	int actualPos = (_posY * _actMapSize + _posX);

	return actualPos;
}

//将读取点转移到坐标
int SetMapPos(int _posX,int _posY,int _mapSize) {
	int actualDataSize = _mapSize + 2;
//	int a = fseek(_MapSavePosition,(long)(GetMapPosInData(_posX, _posY, actualDataSize)), SEEK_SET);
	fseek(_MapSavePosition,(long)(GetMapPosInData(_posX, _posY, actualDataSize)), SEEK_SET);

//	int b = ftell(_MapSavePosition);
//	printf("ftell:%d\n", b);
}

//将读取点转移到出生点
int SetOriginalPos(int _mapSize) {
	SetMapPos((_mapSize-1)/2, (_mapSize - 1) / 2,_mapSize);
}

//读取单点数据
int ReadMapSinglePoint(int _posX, int _posY,int _mapSize) {
	StartMapReading();
	SetMapPos(_posX, _posY, _mapSize);
	int tempRead; 
	fscanf(_MapSavePosition,"%c", &tempRead);
	tempRead = CharToInt(tempRead);
	EndMapReading();
//	printf("%d\n", tempRead);
	return tempRead;
}

// 0 1 2
// 3 4 5
// 6 7 8
int ReadMapArea(int _posX,int _posY,int _mapSize,int _mapAreaData[9]) {

	int tempX=(_posX-1),
		tempY=(_posY-1);

	for (int i = 0; i < _SizeOfFeildOfView; i++) {
		for (int j = 0; j < _SizeOfFeildOfView; j++) {
			_mapAreaData[_SizeOfFeildOfView*i + j] = ReadMapSinglePoint(tempX, tempY, _mapSize);
			/*printf("_SizeOfFeildOfView*i + j:  %d\n",_SizeOfFeildOfView*i + j);
			printf("[]:%d\n", _mapAreaData[_SizeOfFeildOfView*i + j]);
			
			printf("X=%d Y=%d\n", tempX,tempY);*/
			tempX++;
		}
		tempX -= 3; tempY++;
	}
	DrawWholeViewMap(_mapAreaData);
	return 1;
}

Movedir GetMoveDir(int _dir) {
	switch (_dir)
	{
	case 0:
		return Forward;
		break;
	case 1:
		return Backward;
		break;
	case 2:
		return Left;
		break;
	case 3:
		return Right;
		break;
	default:
		return Nowhere;
		break;
	}
}

int Move(Movedir _dir,Transform *_moverTransform) {
	switch (_dir)
	{
	case Forward:
		_moverTransform->y -=1;
		break;
	case Backward:
		_moverTransform->y += 1;
		break;
	case Left:
		_moverTransform->x -= 1;
		break;
	case Right:
		_moverTransform->x += 1;
		break;
	default:
		break;
	}
}

int PlayerMove(int _inputDir,int _mapSize, int _mapAreaData[9]) {
	Movedir dir = GetMoveDir(_inputDir);
	Move(dir, &_PlayerTransform);
	ReadMapArea(_PlayerTransform.x, _PlayerTransform.y, _mapSize, _mapAreaData);
	return ReadMapSinglePoint(_PlayerTransform.x, _PlayerTransform.y, _mapSize);
}


int PlayerMover(int _inputDir, int _mapSize, int _mapAreaData[9]) {
	MapToEvent(PlayerMove(_inputDir, _mapSize, _mapAreaData));
}

int MapToEvent(int _mapPoint){
	Mappoint tempMP = _mapPoint;
	switch (tempMP)
	{
	case Road:
		return 0;
		break;
	case Mountain:
		return 1;
		break;
	case Shop:
		return 2;
		break;
	case Enemy:
		FightEvent(NULL,100);

		return 3;
		break;
	default:
		return -1;
		break;
	}
}

int ReadAllAreaInCol(int _col[],int _mapSize) {

}


int ChangeMapPoint(Transform _pos, Mappoint _tar, int _mapSiz) {
	StartMapReading();
	int * tempCol = (int*)malloc(((_mapSiz + 2)*(_mapSiz+2))*sizeof(int));


	EndMapReading();
}
