#include "ArtificialIntelligence.h"
#include "GameSimStructs.h"


#include <math.h>
#include <limits>
#define brk break
#include "Menu.h"
#include <random>

void AI::intelligenceInit()
{

	int x = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeHorizonal();
	int y = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeVertical();

	if (x <= 0 || y <= 0)
	{
		throw "NO_WALUES";
	}


	getCursorFrom()->setTopLeftLim(vecI2d(0, 0));
	getCursorFrom()->setBotRightLim(vecI2d(x, y));


	getCursorTo()->setTopLeftLim(vecI2d(0, 0));
	getCursorTo()->setBotRightLim(vecI2d(x, y));

	switch(getFraction())
	{
	case _BFL_TEAM_UP_SIDE:
	{

		getCursorFrom()->setCursor(0, 0);

		getCursorTo()->setCursor(0,0);

		brk;
	}
	case _BFL_TEAM_DOWN_SIDE:
	{
		getCursorFrom()->setCursor(x - 1, y - 1);

		getCursorTo()->setCursor(x - 1, y - 1);
		brk;
	}
	default:
		break;
	}

	getRecurseData()->setFraction(getFraction());

	getRecurseData()->curSituation.createNewArray(getArr()->getSizeHorizonal(), getArr()->getSizeVertical());

}


AIRecursionData AI::convertGSimArrToRecursionData(OEDataBase* dbref)
{
	DynamicIntArray2DTemplated<GameBaseObject>* arrRef;
	
	arrRef = dbref->getGameSimDataPtr()->getArrTemplInterface();
	arrRef->getSizeVertical();
	
	for (int y = 0; y < arrRef->getSizeVertical(); y++)
	{

		for (int x = 0; x < arrRef->getSizeHorizonal(); x++)
		{
			int swtch;
			try
			{
				swtch = std::stoi(*arrRef->getElem(x, y)->getGBOFreeDataPtr());
			}
			catch (std::invalid_argument)
			{
				//intelCon.directLogAppend("Ai conv err");
				getRecurseData()->curSituation.setElem(_BFL_TEAM_NONE, x, y);
				continue;
			}

			switch (swtch)
			{
			case _BFL_TEAM_UP_SIDE:
			{
				getRecurseData()->curSituation.setElem(_BFL_TEAM_UP_SIDE, x, y);

				break;
			}
			case _BFL_TEAM_DOWN_SIDE:
			{
				getRecurseData()->curSituation.setElem(_BFL_TEAM_DOWN_SIDE, x, y);
				break;
			}
			case _BFL_TEAM_NONE:
			{
				getRecurseData()->curSituation.setElem(_BFL_TEAM_NONE, x, y);
				break;
			}

			default:
				break;
			}

		}

	}

	return *getRecurseData();
}

class TempMinMaxValues
{
public:
	int value;
	AIVecPosFromPosTo pos;
};

class ValuesCount
{
public:

	ValuesCount(int val, int valCount) : value(val), valueCount(valCount){}

	int value;
	int valueCount;
};


void AI::chooseAction()
{
	convertGSimArrToRecursionData();

	std::vector<AIVecPosFromPosTo> possibleTurns = getRecurseData()->getAllPossibleTurns(playerFraction);

	std::vector<vecI2d> enemiesPoses;

	int index = 0;

	std::vector<int> maxValuesIndexes;

	int max = std::numeric_limits<int>::min();
	std::vector<AIVecPosFromPosTo>::iterator iter = possibleTurns.begin();
	while (iter != possibleTurns.end())
	{
		int tempX = (*iter).posTo.getX(), tempY = (*iter).posTo.getY();

		AIRecursionData innerRec;
		innerRec = *getRecurseData();

		AIVecPosFromPosTo it = (*iter);
		int iterVal;

		if (it.action == _BFL_INTELLIGENCE_CREATE_CQUARE)
		{
			iterVal = innerRec.createMyTeamSquareValue(&(innerRec.curSituation), playerFraction);
		}
		else
		{
			innerRec.moveSquare(*iter);
			iterVal = getRecurseData()->calcSquareVal(&(innerRec.curSituation), 0, 0, playerFraction);
		}

		if (max < iterVal)
		{
			if (!maxValuesIndexes.empty())
			{
				maxValuesIndexes.clear();
			}
			
			max = iterVal;
			maxValuesIndexes.push_back(index);

		}
		else if (max == iterVal)
		{
			maxValuesIndexes.push_back(index);

		}

		index++;
		++iter;
	}

	AIVecPosFromPosTo retVal;

	std::random_device randomiser;
	std::mt19937 gener(randomiser());

	if (maxValuesIndexes.size() - 1 < 0)
	{
		return;
	}
	
	std::uniform_int_distribution<> dist(0, maxValuesIndexes.size()-1);

	int randIndex = maxValuesIndexes.at(dist(gener));

	AIVecPosFromPosTo randomVec = possibleTurns.at(randIndex);
	intelCon.playerCursorFrom->setCursor(randomVec.posFrom);
	intelCon.playerCursorTo->setCursor(randomVec.posTo);

	if (randomVec.action == _BFL_INTELLIGENCE_CREATE_CQUARE)
	{
		intelCon.playerCursorFrom->setCursor(randomVec.posTo);
		intelCon.playerCursorTo->setCursor(randomVec.posTo);

		setAction(_BFL_INTELLIGENCE_CREATE_CQUARE);

		return;
	}

	setAction(_BFL_INTELLIGENCE_MOVE_CELL_CUSTOM);
}



#undef brk
