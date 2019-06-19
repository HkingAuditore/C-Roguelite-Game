
#include "CharactersManager.h"
#include "SystemBase.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SkillsManager.h"


/*技能数据库*/
Skill _FistHit  = { 100,80,200,2,"拳击" };
Skill _FootKick = { 120,50,380,3,"踢击" };

/*技能威力权重*/


float _TooMuch = 0.6;


/*升级相关数据*/
const  int _NumOfLevel = 5;
const  int _EXP[100] = { 0,50,150,300,500,750,750,750,750,750,750,750,750,750,750,750 };
const  int _EXPForOneFight = 50;
const  int _MAXLevel = 10;

/*人物数据库*/

Combater _CombaterAlexios    = { 20, male  , "Alexios"		, 20,20,20,400,480 ,0,0,2, 0, {FistHit,FootKick} };
Combater _CombaterEzio		 = { 35, male  , "Ezio"			, 60,35,35,450,450 ,0,0,2, 0, {FistHit,FootKick} };
Combater _CombaterCasandera	 = { 20, female, "Casandera"    , 25,15,15,800,800 ,0,0,2, 0, {FistHit,FootKick} };

Combater _CombaterPlayer	 = { 18,  male  , "Player"       , 20,15,30,500,500 ,0,0,2, 1, {FistHit,FootKick} };

Combater* _Combaters[10] = { &_CombaterAlexios,&_CombaterEzio,&_CombaterCasandera,&_CombaterPlayer };

/*敌人名称表*/
char _CombaterEnemysName[20][20] = { "Alexios","Ezio","Casandera" };