

#ifndef _ARTIFICIAL_INTELLIGENCE_H
#define _ARTIFICIAL_INTELLIGENCE_H


#include "Vector2DTemplate.h"
#include "AIRecursionData.h"
#include "Intelligence.h"

class ArtificialIntelligence : public Intelligence
{
private:
	int prevListSize = 0;

	AIRecursionData recurseData;
public:
	ArtificialIntelligence(OEDataBase* p_OEDataBase,
		DBIntelligenceData* dataRef, _FRACTION_INT_ fraction, BattleForLifeRules* rules) :
		Intelligence(p_OEDataBase, dataRef, fraction, rules){}

	AIRecursionData* getRecurseData()
	{
		return &recurseData;
	}

	int MinMax(AIRecursionData recursionPos, AIVecPosFromPosTo turnPos, int level, bool isMax, _FRACTION_INT_ myTeam);

	void intelligenceInit();

	void chooseAction();

	AIRecursionData convertGSimArrToRecursionData(OEDataBase* dbref);

	AIRecursionData convertGSimArrToRecursionData()
	{
		return convertGSimArrToRecursionData(intelCon.getDBReference());
	}

	~ArtificialIntelligence(){}

	bool isSquareInMyTeam(int, int) { return false; }
};
typedef ArtificialIntelligence AI;


#endif // !_ARTIFICIAL_INTELLIGENCE

