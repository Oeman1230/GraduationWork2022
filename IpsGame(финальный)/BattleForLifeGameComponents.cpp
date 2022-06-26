#include "BattleForLifeGameComponents.h"
#include <string>
#include "ArtificialIntelligence.h"

bool BattleForLifeRules::isPlaceAcceptableToMove(int x, int y)
{
		if (x >= gameRuleCon.getArr()->getSizeHorizonal() || x < 0)
		{
			return false;
		}
		if (y >= gameRuleCon.getArr()->getSizeVertical() || y < 0)
		{
			return false;
		}
		if (!gameRuleCon.getArr()->getElem(x, y)->getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE))
		{
			return false;
		}
		return true;
}

#define NOT !

int BattleForLifeRules::countSquaresOfOneFraction(_FRACTION_INT_ curFraction)
{
	int counter = 0;

	for (int y = 0; y < getBFTRulesCon()->getArr()->getSizeVertical(); y++)
	{

		for (int x = 0; x < getBFTRulesCon()->getArr()->getSizeHorizonal(); x++)
		{
			GameBaseObject tempObj;
			tempObj = *getBFTRulesCon()->getArr()->getElem(x, y);
			if ((NOT tempObj.getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE))
				&& tempObj.getGBOFreeDataPtr()->_Equal(std::to_string(curFraction)))
			{
				counter++;
			}

		}

	}
	return counter;
}




bool BattleForLifeRules::moveCell(_FRACTION_INT_ curFraction, int curX, int curY, int newX, int newY)
{
	if (NOT BattleForLifeRules::isPlaceAcceptableToMove(newX, newY))
	{
		
		return false;
	}

	GameBaseObject curObject;
	curObject = *gameRuleCon.getArr()->getElem(curX, curY);

	if (NOT curObject.getGBOFreeDataPtr()->_Equal(std::to_string(curFraction)))
	{
		return false;
	}

	gameRuleCon.getArr()->setElem(curObject, newX, newY);

	gameRuleCon.getArr()->setElem(GameBaseObject(), curX, curY);

	return true;
}


/*
	функция показывает все доступные точки для перемещения.
	Если рядом стоит клетка, то проверяется можно ли через неё перешагнуть
*/
std::vector<vecI2d> BattleForLifeRules::showAllPosiblePositions(int x, int y)
{
	std::vector<vecI2d> retVal;
	
	if (x >= gameRuleCon.getArr()->getSizeHorizonal() || x < 0)
	{
		
		retVal.push_back(_BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC);
		return retVal;
	}
	if (y >= gameRuleCon.getArr()->getSizeVertical() || y < 0)
	{

		retVal.push_back(_BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC);
		return retVal;

	}

#define UP_FROM_CURR y - _NEIGHBOUR_NEAR_POSITION

	//UP FROM CURR POSITION
	if (isPlaceAcceptableToMove(x, UP_FROM_CURR))
	{
		retVal.push_back(vecI2d(x, UP_FROM_CURR));
	}
	else
	{
		if (isPlaceAcceptableToMove(x, UP_FROM_CURR - _NEIGHBOUR_NEAR_POSITION))
		{
			retVal.push_back(vecI2d(x, UP_FROM_CURR - _NEIGHBOUR_NEAR_POSITION));
		}

	}
#undef UP_FROM_CURR

#define DOWN_FROM_CURR y + _NEIGHBOUR_NEAR_POSITION

	//DOWN FROM CURR POSITION
	if (isPlaceAcceptableToMove(x, DOWN_FROM_CURR))
	{
		retVal.push_back(vecI2d(x, DOWN_FROM_CURR));
	}
	else
	{
		if (isPlaceAcceptableToMove(x, DOWN_FROM_CURR + _NEIGHBOUR_NEAR_POSITION))
		{
			retVal.push_back(vecI2d(x, DOWN_FROM_CURR + _NEIGHBOUR_NEAR_POSITION));
		}

	}
#undef DOWN_FROM_CURR

#define LEFT_FROM_CURR x - _NEIGHBOUR_NEAR_POSITION

	//LEFT FROM CURR POSITION
	if (isPlaceAcceptableToMove(LEFT_FROM_CURR, y ))
	{
		retVal.push_back(vecI2d(LEFT_FROM_CURR, y));
	}
	else
	{
		if (isPlaceAcceptableToMove(LEFT_FROM_CURR - _NEIGHBOUR_NEAR_POSITION, y))
		{
			retVal.push_back(vecI2d(LEFT_FROM_CURR - _NEIGHBOUR_NEAR_POSITION, y));
		}

	}
#undef LEFT_FROM_CURR

#define RIGHT_FROM_CURR x + _NEIGHBOUR_NEAR_POSITION

	//RIGHT FROM CURR POSITION
	if (isPlaceAcceptableToMove(RIGHT_FROM_CURR, y))
	{
		retVal.push_back(vecI2d(RIGHT_FROM_CURR, y));
	}
	else
	{
		if (isPlaceAcceptableToMove(RIGHT_FROM_CURR + _NEIGHBOUR_NEAR_POSITION, y))
		{
			retVal.push_back(vecI2d(RIGHT_FROM_CURR + _NEIGHBOUR_NEAR_POSITION, y));
		}

	}
#undef RIGHT_FROM_CURR

	retVal.push_back(_BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC);

	if (retVal[0] == _BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC)
	{
		return retVal;
	}
	retVal.pop_back();
	return retVal;
}

bool BattleForLifeRules::isGameOver()
{
	AIAnalysisData helpData;
	int freeSquares = 0;
	const int _MINIMUM_EMPTY_SQUARES = 5;

	helpData.curSituation.createNewArray(getBFTRulesCon()->getArr()->getSizeHorizonal(),
		getBFTRulesCon()->getArr()->getSizeVertical());

	int upTeam = 0, downTeam = 0;

	for (int y = 0; y < getBFTRulesCon()->getArr()->getSizeVertical(); y++)
	{
		for (int x  = 0; x < getBFTRulesCon()->getArr()->getSizeHorizonal(); x++)
		{
			GameBaseObject elem = *getBFTRulesCon()->getArr()->getElem(x, y);

			if (elem.getGBOFreeDataPtr()->_Equal(std::to_string(_BFL_TEAM_NONE)))
			{
				freeSquares++;
			}
			int swtch;
			try
			{
				swtch = std::stoi(*getBFTRulesCon()->getArr()->getElem(x, y)->getGBOFreeDataPtr());
			}
			catch (std::invalid_argument)
			{
				//intelCon.directLogAppend("Ai conv err");
				helpData.curSituation.setElem(_BFL_TEAM_NONE, x, y);
				continue;
			}
			switch (swtch)
			{
			case _BFL_TEAM_UP_SIDE:
			{
				helpData.curSituation.setElem(_BFL_TEAM_UP_SIDE, x, y);
				upTeam++;
				break;
			}
			case _BFL_TEAM_DOWN_SIDE:
			{
				helpData.curSituation.setElem(_BFL_TEAM_DOWN_SIDE, x, y);
				downTeam++;
				break;
			}
			case _BFL_TEAM_NONE:
			{
				helpData.curSituation.setElem(_BFL_TEAM_NONE, x, y);
				break;
			}
			default:
				break;
			}
		}
	}

	if (freeSquares > _MINIMUM_EMPTY_SQUARES)
	{
		return false;
	}
	
	//helpData
	helpData.AiFraction = _BFL_TEAM_UP_SIDE;
	std::vector<AIVecPosFromPosTo> allTurnsUp;
	allTurnsUp = helpData.getAllPossibleTurns(helpData.AiFraction);

	std::vector<AIVecPosFromPosTo> allTurnsDown;
	helpData.AiFraction = _BFL_TEAM_DOWN_SIDE;
	allTurnsDown = helpData.getAllPossibleTurns(helpData.AiFraction);


	if (0 == allTurnsUp.size() || 0 == allTurnsDown.size() || downTeam == 0 || upTeam == 0)
	{
		if (upTeam > downTeam)
		{
			gameRuleCon.getDBReference()->getMenuData()->setLosedFraction(_BFL_TEAM_DOWN_SIDE);
		}
		else if (upTeam < downTeam)
		{
			gameRuleCon.getDBReference()->getMenuData()->setLosedFraction(_BFL_TEAM_UP_SIDE);
		}
		else
		{
			gameRuleCon.getDBReference()->getMenuData()->setLosedFraction(_BFL_TEAM_NONE);
		}

		return true;
	}
	return false;

}

//проверяет команду и записывает в счетчик
void fractionCheckSTR(std::string curFractionStr, unsigned short int* counter1, unsigned short int* counter2)
{
	_FRACTION_INT_ curFrac = 10;
	try
	{
		curFrac = std::stoi(curFractionStr);
	}
	catch (std::invalid_argument& invArg)
	{
		
		return;
	}
	catch (std::out_of_range)
	{
		return;

	}

	switch (curFrac)
	{
	case _BFL_TEAM_UP_SIDE:
	{
		(*counter1)++;
		break;
	}
	case _BFL_TEAM_DOWN_SIDE:
	{
		(*counter2)++;
		break;
	}

	default:
		break;
	}


}


#define shortLimitCheck gameRuleCon.getArr()->isCoordInLimits
//Проверка какие клетки откружают текущую по координатам
_FRACTION_INT_ BattleForLifeRules::whatFractionSurrounds(int x, int y)
{
	//vecI2d curPos(x, y);
	if (NOT shortLimitCheck(x, y))
	{
		return _BFL_TEAM_NONE;
	}


	unsigned short int count = 0;
	unsigned short int fractionOne = 0;
	unsigned short int fractionTwo = 0;
	GameBaseObject tempElem;


	if (shortLimitCheck(x, y - 1)
		&& gameRuleCon.getArr()->getElem(x, y - 1)->getGBOTypePtr()->_Equal(_BFL_TYPE_CREATURE_SQUARE))
	{
		fractionCheckSTR(*gameRuleCon.getArr()->getElem(x, y - 1)->getGBOFreeDataPtr(),
			&fractionOne,	&fractionTwo
		);
	}

	if (shortLimitCheck(x, y + 1)
		&& gameRuleCon.getArr()->getElem(x, y + 1)->getGBOTypePtr()->_Equal(_BFL_TYPE_CREATURE_SQUARE))
	{
		fractionCheckSTR(*gameRuleCon.getArr()->getElem(x, y + 1)->getGBOFreeDataPtr(),
			&fractionOne, &fractionTwo
		);
	}

	if (shortLimitCheck(x - 1, y)
		&& gameRuleCon.getArr()->getElem(x - 1, y)->getGBOTypePtr()->_Equal(_BFL_TYPE_CREATURE_SQUARE))
	{
		fractionCheckSTR(*gameRuleCon.getArr()->getElem(x - 1, y)->getGBOFreeDataPtr(),
			&fractionOne, &fractionTwo
		);
	}

	if (shortLimitCheck(x + 1, y)
		&& gameRuleCon.getArr()->getElem(x + 1, y)->getGBOTypePtr()->_Equal(_BFL_TYPE_CREATURE_SQUARE))
	{
		fractionCheckSTR(*gameRuleCon.getArr()->getElem(x + 1, y)->getGBOFreeDataPtr(),
			&fractionOne, &fractionTwo
		);
	}
	//Выдача каких клеток больше
	if (fractionOne >= _BFL_RULES_NECESSARY_SQUARES)
	{
		return _BFL_TEAM_UP_SIDE;
	}
	if (fractionTwo >= _BFL_RULES_NECESSARY_SQUARES)
	{
		return _BFL_TEAM_DOWN_SIDE;
	}

	return _BFL_TEAM_NONE;

}

//функция уничтожение клетки, окруженной врагами
void BattleForLifeRules::destroySquareInSurroundings()
{
	int maxX = gameRuleCon.getArr()->getSizeHorizonal();
	int maxY = gameRuleCon.getArr()->getSizeVertical();
	
	for (int y = 0; y < maxY; y++)
	{

		for (int x = 0; x < maxX; x++)
		{
			switch (whatFractionSurrounds(x, y))
			{
			case _BFL_TEAM_NONE:
			{
				break;
			}
			case _BFL_TEAM_UP_SIDE:
			{
				if (gameRuleCon.getArr()->getElem(x, y)->getGBOFreeDataPtr()->_Equal(std::to_string(_BFL_TEAM_DOWN_SIDE)))
				{
					gameRuleCon.getArr()->setElem(GameBaseObject(), x, y);
				}

				break;
			}
			case _BFL_TEAM_DOWN_SIDE:
			{
				if (gameRuleCon.getArr()->getElem(x, y)->getGBOFreeDataPtr()->_Equal(std::to_string(_BFL_TEAM_UP_SIDE)))
				{
					gameRuleCon.getArr()->setElem(GameBaseObject(), x, y);
				}

				break;
			}


			default:
				break;
			}

		}

	}

}
//Создание клетки в текущей позии
bool BattleForLifeRules::createSquareByPressintEnter()
{

	_FRACTION_INT_ fractionTurn = gameRuleCon.getGSimCon()->getGameSimDataRef()->getCurrentFractionTurn();

	vecI2d curFractionSquarePos;

	switch (fractionTurn)
	{

	case _BFL_TEAM_UP_SIDE:
	{
		curFractionSquarePos = gameRuleCon.getDBReference()->getPlayerTwoData()->getCursorTo()->getCursorPos();
		break;
	}
	case _BFL_TEAM_DOWN_SIDE:
	{
		curFractionSquarePos = gameRuleCon.getDBReference()->getPlayerOneData()->getCursorTo()->getCursorPos();
		break;
	}

	default:
		break;
	}

	_FRACTION_INT_ fraction = whatFractionSurrounds(
		//GSimCon->getDBReference()->getIntelligenceData()->getCursorTo()->getCursorPos()
		curFractionSquarePos
	);

	switch (fraction)
	{
	case _BFL_TEAM_UP_SIDE:
	{
		gameRuleCon.getArr()->setElem(createSquareWithTeam(_BFL_TEAM_UP_SIDE),

			gameRuleCon.getDBReference()->getPlayerTwoData()->getCursorTo()->getCursorPos().getX(),
			gameRuleCon.getDBReference()->getPlayerTwoData()->getCursorTo()->getCursorPos().getY()
			);
		return true;
		break;
	}
	case _BFL_TEAM_DOWN_SIDE:
	{

		gameRuleCon.getArr()->setElem(createSquareWithTeam(_BFL_TEAM_DOWN_SIDE),
			gameRuleCon.getDBReference()->getPlayerOneData()->getCursorTo()->getCursorPos().getX(),
			gameRuleCon.getDBReference()->getPlayerOneData()->getCursorTo()->getCursorPos().getY()
		);
		return true;

		break;
	}
	{
	default:
		break;
	}
	}

	return false;

}

GameBaseObject BattleForLifeRules::createSquareWithTeam(_FRACTION_INT_ fraction)
{
	GameBaseObject retObj;
	retObj.setGBOName(_BFL_STANDART_NAME);
	retObj.setGBOType(_BFL_TYPE_CREATURE_SQUARE);
	retObj.setGBOFreeData(std::to_string(fraction));
	return retObj;

}

#undef shortLimitCheck
#undef NOT
