

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "BattleForLifeGameComponents.h"

#include "PersonIntelligence.h"
#include "ArtificialIntelligence.h"

#define _PLAYER_INIT_ERR_INTELLIGENCE_MODE_UNDEF "PLAYER_INIT_ERR_INTELLIGENCE_MODE_UNDEF"

#define _PLAYER_INTELLIGENCE_MODE_PERSON_MIND 1
#define _PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND 2

/*
	����� ������
	����� ���������� ����� ��� ������� ��������
	� ��� �� ����� ���������� "��� ���������� ������"
*/

class Player
{
private:
	//PersonIntelligence mind;
	Intelligence* mind = NULL; //��������� �����. ��� �������, ��� ���������
	_FRACTION_INT_ playerFraction; //������� ������
	BattleForLifeRules *rules; //������ �� ������� ����
	DBIntelligenceData* intelDataRef; //������ �� ������ ����������
public:

	void setPlayerFraction(_FRACTION_INT_  newFraction)
	{
		playerFraction = newFraction;
	}

	Intelligence* getMind()
	{
		return mind;
	}

	void setMind(Intelligence* newMindPtr)
	{
		if (mind != NULL)
		{
			delete mind;
		}

		mind = newMindPtr;
	}

	_FRACTION_INT_ getFraction()
	{
		return playerFraction;
	}

	Player(BattleForLifeRules* p_rules, DBIntelligenceData* dataRef , _FRACTION_INT_ fraction) :
		//mind(p_rules->getGSimCon()->getDBReference(), dataRef , playerFraction),
		intelDataRef(dataRef),
		rules(p_rules), playerFraction(fraction)
	{
		std::cout << "Player constructor\n";
	}

	BattleForLifeRules* getBFLRules()
	{
		return rules;
	}

	virtual ~Player()
	{
		delete mind;
	}
	//������ ����� ������ ������� ��� ����������
	virtual void playerInit(int intelligenceMode);
	//������ ����� ������ ������� ���
	virtual bool makeTurn();

};


#endif // !_PLAYER_H_

