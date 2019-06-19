
#include "CharactersManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SystemBase.h"
#include "SkillsManager.h"






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ⲿ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*��ʾ��*/
extern int ShowDamage(Combater* _combater0, Combater* _combater1, char _skillsName[10], int _damage, int _isTooMuch);
extern int ShowDead(Combater* _combatorDead);
extern int ShowWinner(Combater* _combater);






/*��ɫ������*/

/*�������ݿ�*/
extern Skill _FistHit;
extern Skill _FootKick;
/********/


extern int _FistHitATKPowerBase ;
extern int _FistHitATKPoweFloat;
extern int _FistHitDEFPower ;
extern int _FootKickATKPowerBase;
extern int _FootHitATKPoweFloat;
extern int _FootKickDEFPower;
extern int _FistBase;
extern int _FootBase;
extern float _TooMuch;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//�ڲ�����
//
////////////////////////////////////////////����///////////////////////////////////////////////////////////////////////

/******************���ܿ�********************/

/*�˺����ʻ�ȡ*/
double GetDamagePower(Skill _skill) {
	double damagePower = ((double)(((double)_skill.aTKPowerBase+(double)GetPowerNumber(_skill.aTKPoweFloat)) / 100.0) + 1.0);
	
	return damagePower;
}

/*һ���˺�*/
int GetDamage(int _atk,int _def,Skill _skill,double* _powerJudge) {

	*_powerJudge = GetDamagePower(_skill);
	int damage = (_skill.atkBase + _atk * (*_powerJudge) - _def * _skill.dEFPower);
	damage = damage > 0 ? damage : 0;
	return damage;
}

/*Ч����Ⱥ�ж�*/
int IsTooMuchDamage(double* _damagePower,Skill _skill) {
	
	if (((*_damagePower-1)*100.0f-_skill.aTKPowerBase)>=0.8f*_skill.aTKPoweFloat      ) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//ȭ��

int FistHit(Combater* _combaterAttacker, Combater* _combaterDefender) {
	double powerTemp;
	double *powerJudge = &powerTemp;
	int damage = GetDamage(_combaterAttacker->fighterAttack, _combaterAttacker->fighterDefend, _FistHit,powerJudge);
	_combaterDefender->fighterHP -= damage;
	ShowDamage(_combaterAttacker, _combaterDefender, "ȭ��", damage,IsTooMuchDamage(powerJudge, _FistHit));

	return damage;
}

//����
int FootKick(Combater* _combaterAttacker, Combater* _combaterDefender) {
	
	double powerTemp;
	double *powerJudge = &powerTemp;
	int damage = GetDamage(_combaterAttacker->fighterAttack, _combaterAttacker->fighterDefend, _FootKick, powerJudge);
	_combaterDefender->fighterHP -= damage;
	ShowDamage(_combaterAttacker, _combaterDefender, "�߻�", damage,IsTooMuchDamage(powerJudge, _FootKick));

	return damage;
}

/*���ܿ�����*/
//int (*_Skills[10])(Combater*,Combater*) = { FistHit,FootKick     };


/***********************************************************************/



//�����ж�
int IsDead(Combater* _combater) {
	
	return _combater->fighterHP >= 0 ? 0 : 1;
}

//����
int ReBorn(Combater* _combater) {
	_combater->fighterHP = 0;
	return 1;
}


//�����ж�
int ChooseSkill(int _numOfSkill) {
	int skillChosen = GetPowerNumber(_numOfSkill-1);

	return skillChosen;
}


//����˳���ж� ��������
Combater *ChooseCombater(Combater* _combater0, Combater* _combater1) {
	Combater* result;
	result = _combater0->fighterSpeed > _combater1->fighterSpeed ? _combater0 : _combater1;
	return result;
}

//���ν��� �����˷���1
int FightOnce(Combater* _combaterAtk, Combater* _combaterDef) {
	_combaterAtk->fighterSkills[ChooseSkill(_combaterAtk->fighterNumOfSkills)](_combaterAtk, _combaterDef);
	//_Skills[ChooseSkill(_combatorAtk->fighterNumOfSkills)](_combatorAtk, _combatorDef);
	if (IsDead(_combaterDef)) {
		ShowDead(_combaterDef);
		ReBorn(_combaterDef);
		return 1;
	}
	return 0;
}

//ѭ������ �����˷��ػغ���
int FightCycles(Combater* _combaterFirst, Combater* _combaterSecond,int _maxRound) {
	Combater* tempCombaterATK= _combaterFirst, *tempCombaterDEF = _combaterSecond ,*exchangeTemp;
	for (int round = 1; round <= _maxRound; round++) {
		if (FightOnce(tempCombaterATK, tempCombaterDEF)) {
			return round;
		}
		exchangeTemp = tempCombaterDEF, tempCombaterDEF = tempCombaterATK, tempCombaterATK = exchangeTemp;
	}
	return 0;
}
//��ܴ��� �ֳ�ʤ������ʤ�� ���򷵻�NULL
Combater* Fight(Combater* _combater0, Combater* _combater1, int _maxRound) {
	Combater* combaterFirst = ChooseCombater(_combater0, _combater1);
	Combater* combaterSecond = (_combater0 == combaterFirst ? _combater1 : _combater0);
	Combater* winner=NULL;
	int round= FightCycles(combaterFirst, combaterSecond,_maxRound);
	
	if (round) {
		winner = (!(round % 2))? combaterSecond: combaterFirst;
		
	}
	

	_combater0->fighterHP = _combater0->fighterHPMAX;
	_combater1->fighterHP = _combater1->fighterHPMAX;
	ShowWinner(winner);
	return winner;
}