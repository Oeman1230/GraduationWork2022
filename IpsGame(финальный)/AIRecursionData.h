
#ifndef _AI_RECURSION_DATA_H
#define _AI_RECURSION_DATA_H

#include "Vector2DTemplate.h"
#include "BattleForLifeGameComponents.h"
#include "GameSimStructs.h"
#include "Intelligence.h"

#include <list>
#include <math.h>
#include <limits>

#define _AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR DynamicIntArray2DTemplated<_FRACTION_INT_>

#define _AI_INTELLIGENCE_ERR_CURRENT_FRACTION_NOT_SET "AI_INTELLIGENCE_ERR_CURRENT_FRACTION_NOT_SET"

#define _AI_INTEL_DATA_MODE_SHOW_FRACTION 1
#define _AI_INTEL_DATA_MODE_SHOW_MAX_COUNT 2


class AIVecPosFromPosTo
{
public:
	AIVecPosFromPosTo(){}
	AIVecPosFromPosTo(vecI2d newPosFrom, vecI2d newPosTo):
		posFrom(newPosFrom) , posTo(newPosTo){}

	vecI2d posFrom = _BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC;
	vecI2d posTo = _BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC;
	int value = 0;
	int action = _BFL_INTELLIGENCE_NO_ACTION;
	bool operator>(AIVecPosFromPosTo comp)
	{
		if (value >= comp.value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<(AIVecPosFromPosTo comp)
	{
		if (value <= comp.value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator==(AIVecPosFromPosTo comp)
	{
		if (value == comp.value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};


class AISquareSurroundsInfo
{
public:
	_FRACTION_INT_ cellFraction = _BFL_TEAM_NONE;
	unsigned short upTeamCount = 0;
	unsigned short downTeamCount = 0;
};

class AIRecursionData
{
private:
	std::vector<vecI2d> previousPos;
	std::list<AIVecPosFromPosTo> prevPosList;
	
public:
	AIRecursionData() {}

	AIRecursionData(_FRACTION_INT_ fraction) :
		AiFraction(fraction){}

	_FRACTION_INT_ getMyEnemy(_FRACTION_INT_ me);
	bool wasPosInTurnList(vecI2d curPos);

	bool isSquareInMyTeamRecurce(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, _FRACTION_INT_ curFraction, int x, int y);

	DynamicIntArray2DTemplated<_FRACTION_INT_> curSituation;
	std::vector<AIVecPosFromPosTo> getAllPossibleTurns(_FRACTION_INT_ myTeam);

	_FRACTION_INT_ AiFraction;

	void moveSquare(AIVecPosFromPosTo newPos);

	void setFraction(_FRACTION_INT_ fract)
	{
		AiFraction = fract;
	}

	void addToPrevPos(vecI2d curPos)
	{
		previousPos.push_back(curPos);

	}

	std::list<AIVecPosFromPosTo>* getPrevPosList()
	{
		return &prevPosList;
	}

	void addToPrevPosList(AIVecPosFromPosTo curPos)
	{
		prevPosList.push_back(curPos);

	}

	bool isPosInPrevList(AIVecPosFromPosTo curPos)
	{
		std::list<AIVecPosFromPosTo>::iterator list_iter = prevPosList.begin();

		while (list_iter != prevPosList.end())
		{
			if ((*list_iter) == curPos)
			{
				return true;
			}


		}
		return false;

	}
	void deletePosFromPrevList(AIVecPosFromPosTo curPos)
	{

		std::list<AIVecPosFromPosTo>::iterator iter = prevPosList.begin();
		while (iter!=prevPosList.end())
		{
			if ((*iter).operator==(curPos))
			{
				prevPosList.erase(iter);
				return;
			}
			++iter;

		}

	}
	std::vector<AIVecPosFromPosTo> showPlacesToCreateMyCquare(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation,
		_FRACTION_INT_ fract, std::vector<AIVecPosFromPosTo> myTeamPositions);

	void addPosToPrevList(AIVecPosFromPosTo curPos)
	{
		prevPosList.push_back(curPos);

	}
	void deletePosFromPreviosVec(vecI2d curPos)
	{
		for (int i = 0; i < previousPos.size(); i++)
		{
			if (curPos == previousPos[i])
			{
				previousPos.erase(previousPos.begin() + i);
			}
		}
	}
	int createMyTeamSquareValue(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSiation, _FRACTION_INT_ myFraction);

	bool isEnemySurroundedByMe(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation, _FRACTION_INT_ myFract, int x, int y);

	int killEnemySquareValue(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSiation, _FRACTION_INT_ myFraction);

	int calcSquareVal(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, int X, int Y, _FRACTION_INT_ frac);

	std::vector<AIVecPosFromPosTo> getAllPossibleToMoveMyCells(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation,
		_FRACTION_INT_ myTeam);

	static const int _AI_MY_TEAM_SQUARES_VALUE = 10;
	static const int _AI_MY_TEAM_SQUARES_COUNT_MODIFIER = 2;
	static const int _AI_ENEMY_TEAM_SQUARES_VALUE = 10;
	static const int _AI_ENEMY_TEAM_SQUARES_COUNT_MODIFIER = 3;
	static const int _AI_RECURSION_LEAF = 4;
	static const int _AI_RECURSION_CAN_CREATE_MY_SQUARE = 400;
	static const int _Ai_RECURSION_CAN_KILL_ENEMY = 600;

};
typedef AIRecursionData AIAnalysisData;

#endif // !_AI_RECURSION_DATA_H

