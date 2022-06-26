
#ifndef _PERSON_INTELLIGENCE_H_
#define _PERSON_INTELLIGENCE_H_

#include "Intelligence.h"
#include "BattleForLifeGameComponents.h"

/*
	����� ���������� ������-��������
	����� ��������� ��� ����������� ��� ���� ���������
	-������� � ����������
	
*/

class PersonIntelligence : public Intelligence
{
private:
public:
	PersonIntelligence(OEDataBase* p_dataBase, DBIntelligenceData* dataRef, _FRACTION_INT_ fraction, BattleForLifeRules* rulesRef)
		: Intelligence(p_dataBase, dataRef, fraction, rulesRef)
	{

	}
	~PersonIntelligence() {}

	void intelligenceInit();
	void chooseAction();

	void menuCommandEnter();
	void menuCommandMove();
	void menuCommandReset();
	void menuComEnterFromCursorAction();
};


#endif // !_PERSON_INTELLIGENCE_H_
