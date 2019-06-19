
#include "CharactersManager.h"
#include "SystemBase.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SkillsManager.h"


/*技能数据库*/
Skill _FistHit  = { 100,80,20,2,"拳击" };
Skill _FootKick = { 120,50,40,3,"踢击" };

/*技能威力权重*/
int _FistHitATKPowerBase	 = 80;
int _FistHitATKPoweFloat	 = 20;
int _FistHitDEFPower		 = 2;
int _FootKickATKPowerBase	 = 50;
int _FootHitATKPoweFloat	 = 20;
int _FootKickDEFPower		 = 3;

int _FistBase = 100;
int _FootBase = 120;

float _TooMuch = 0.6;


/*升级相关数据*/
const  int _NumOfLevel = 5;
const  int _EXP[100] = { 0,50,150,300,500,750,750,750,750,750,750,750,750,750,750,750 };
const  int _EXPForOneFight = 50;
const  int _MAXLevel = 3;

/*人物数据库*/

Combater _CombaterAlexios    = { 20, male  , "Alexios"		, 20,20,20,200,200 ,0,0,2, 0, {FistHit,FootKick} };
Combater _CombaterEzio		 = { 35, male  , "Ezio"			, 30,35,35,130,130 ,0,0,2, 0, {FistHit,FootKick} };
Combater _CombaterCasandera	 = { 20, female, "Casandera"    , 25,15,15,150,150 ,0,0,2, 0, {FistHit,FootKick} };

Combater _CombaterPlayer	 = { 0,  male  , "Player"       , 10,25,25,200,200 ,0,0,2, 1, {FistHit,FootKick} };

Combater* _Combaters[10] = { &_CombaterAlexios,&_CombaterEzio,&_CombaterCasandera,&_CombaterPlayer };

/*敌人名称表*/
char _CombaterEnemysName[20][20] = { "Alexios","Ezio","Casandera" };