#pragma once
#ifndef CHARACTERSMANAGER_H
#define CHARACTERSMANAGER_H
#include <stdio.h>
#include <stdlib.h>
#include "SystemBase.h"



enum Sex
{
	male, female
};

typedef struct StSkill {
	int atkBase;
	int aTKPowerBase;
	int aTKPoweFloat;
	int dEFPower;
	char skillName[20];

}Skill;

typedef struct Fighter {
	int fighterAge;

	enum Sex fighterSex;
	char fighterName[50];
	int  fighterAttack;
	int  fighterDefend;
	int  fighterSpeed;
	int  fighterHPMAX;
	int  fighterHP;
	int  fighterExperience;
	int  fighterLevel;
	int  fighterNumOfSkills;
	int  isPlayer;
	int  (*fighterSkills[10])(struct Fighter*, struct Fighter*);
}Combater;


#endif // !#define CHARACTERSMANAGER_H
