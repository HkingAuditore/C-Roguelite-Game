#pragma once
#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H
#include "CharactersManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SystemBase.h"

typedef enum EventType
{
	fight, shop, incident, other
}Eventtype;
typedef struct EvEnt
{
	Eventtype Type;


}Event;



int FightEvent(Combater* _enemy, int _maxRound);
int ShopEvent(int _shopList[]);
int IncidentEvent(char _Sentence[],int _gain);



#endif // !EVENTSMANAGER_H
