#include "AIRecursionData.h"
bool isPlaceAcceptableToMove(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, int x, int y);

void fractionCheck(_FRACTION_INT_ curFrac, unsigned short int* counter1, unsigned short int* counter2)
{

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


_FRACTION_INT_ AIRecursionData::getMyEnemy(_FRACTION_INT_ me)
{
	switch (me)
	{
	case _BFL_TEAM_UP_SIDE:
	{
		return _BFL_TEAM_DOWN_SIDE;
		break;
	}
	case _BFL_TEAM_DOWN_SIDE:
	{
		return _BFL_TEAM_UP_SIDE;
		break;
	}
	case _BFL_TEAM_NONE:
	{
		return _BFL_TEAM_NONE;
		break;
	}
	default:
		break;
	}
	return _BFL_TEAM_NONE;
}


AISquareSurroundsInfo whatFractionSurrounds(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation, int x, int y)
	//unsigned short MODE = _AI_INTEL_DATA_MODE_SHOW_FRACTION)
{

	AISquareSurroundsInfo retVal;

	int fractionNone = 0;
	unsigned short int contUpTeam = 0, countDownTeam = 0;


	int left = 0, up = 0, right = 0, down = 0;

	if (currSituation->isCoordInLimits( x - 1, y))
	{
		left = *currSituation->getElem(x - 1, y);
	}
	if (currSituation->isCoordInLimits(x + 1, y))
	{
		right = *currSituation->getElem(x + 1, y);
	}
	if (currSituation->isCoordInLimits(x, y - 1))
	{
		up = *currSituation->getElem(x, y - 1);
	}
	if (currSituation->isCoordInLimits(x, y + 1))
	{
		down = *currSituation->getElem(x, y + 1);
	}

	fractionCheck(up, &contUpTeam, &countDownTeam);
	fractionCheck(right, &contUpTeam, &countDownTeam);
	fractionCheck(down, &contUpTeam, &countDownTeam);
	fractionCheck(left, &contUpTeam, &countDownTeam);

	retVal.downTeamCount = countDownTeam;
	retVal.upTeamCount = contUpTeam;

	if (retVal.upTeamCount >= 3 )
	{
		retVal.cellFraction = _BFL_TEAM_UP_SIDE;
	}
	else if(retVal.downTeamCount >= 3)
	{
		retVal.cellFraction = _BFL_TEAM_DOWN_SIDE;
	}
	else
	{
		retVal.cellFraction = _BFL_TEAM_NONE;
	}
	
	return retVal;
}

bool AIRecursionData::isEnemySurroundedByMe(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation, _FRACTION_INT_ myFract, int x, int y)
{
	_FRACTION_INT_ chosenCell;
	chosenCell = *currSituation->getElem(x, y);
	if (chosenCell == getMyEnemy(myFract) && whatFractionSurrounds(currSituation, x, y).cellFraction == myFract)
	{
		return true;


	}
	return false;

}


bool canCreateCellInSurrounding(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation, _FRACTION_INT_ myFract, int x, int y)
{
	if (whatFractionSurrounds(currSituation, x, y).cellFraction == myFract)
	{
		return true;
	}
	else
	{
		return false;
	}

}

std::vector<AIVecPosFromPosTo> AIRecursionData::showPlacesToCreateMyCquare(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation,
	_FRACTION_INT_ fract, std::vector<AIVecPosFromPosTo> myTeamPositions)
{
	int maxX = curSituation->getSizeHorizonal();
	int maxY = curSituation->getSizeVertical();

	std::vector<AIVecPosFromPosTo> retVec;

	std::vector<AIVecPosFromPosTo>::iterator iter = myTeamPositions.begin();

	while (iter != myTeamPositions.end())
	{
		AIVecPosFromPosTo it = *iter;

		if (whatFractionSurrounds(curSituation, it.posTo.getX(), it.posTo.getY()).cellFraction == fract)
		{
			it.action = _BFL_INTELLIGENCE_CREATE_CQUARE;
			retVec.push_back(it);
		}

		++iter;
	}

	return retVec;
}



bool isPlaceAcceptableToMove(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, int x, int y)
{


	if (!curSituation->isCoordInLimits(x, y))
	{
		return false;
	}
	if (*curSituation->getElem(x, y) == _BFL_TEAM_NONE)
	{


		return true;
	}

	return false;;

}

int AIRecursionData::createMyTeamSquareValue(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSiation, _FRACTION_INT_ myFraction)
{
	int maxX = currSiation->getSizeHorizonal();
	int maxY = currSiation->getSizeVertical();

	std::vector<AIVecPosFromPosTo> canCreateSquVec;

	canCreateSquVec = showPlacesToCreateMyCquare(currSiation, myFraction,
		getAllPossibleToMoveMyCells(currSiation, myFraction));

	return canCreateSquVec.size() * _AI_RECURSION_CAN_CREATE_MY_SQUARE;


}


int AIRecursionData::killEnemySquareValue(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSiation, _FRACTION_INT_ myFraction)
{
	int maxX = currSiation->getSizeHorizonal();
	int maxY = currSiation->getSizeVertical();

	int enemyWictimCount = 0;

	std::vector<AIVecPosFromPosTo> mySquares;
	mySquares = getAllPossibleToMoveMyCells(currSiation, myFraction);

	std::vector<AIVecPosFromPosTo>::iterator iter = mySquares.begin();

	while (iter != mySquares.end())
	{
		AIVecPosFromPosTo it = *iter;
		AIRecursionData innerRec;
		innerRec = *this;
		innerRec.moveSquare(it);

		std::vector<vecI2d> allSquaresOfMyTeam;

		for (int y = 0; y < innerRec.curSituation.getSizeVertical(); y++)
		{
			for (int x = 0; x < innerRec.curSituation.getSizeHorizonal(); x++)
			{

				if (isSquareInMyTeamRecurce(&(innerRec.curSituation), myFraction, x, y))
				{
					allSquaresOfMyTeam.push_back(vecI2d(x, y));

				}
			}
		}

		std::vector<vecI2d>::iterator innerIter = allSquaresOfMyTeam.begin();

		while (innerIter != allSquaresOfMyTeam.end())
		{
			vecI2d curSquare;
			curSquare = *innerIter;

			int curX = curSquare.getX(), curY = curSquare.getY();

			int up = curY - 1, down = curY + 1,
				left = curX - 1, right = curX + 1;


			if (currSiation->isCoordInLimits(curX, up))
			{
				if (isEnemySurroundedByMe(currSiation, myFraction , curX, up))
				{
					enemyWictimCount++;
				}
			}
			if (currSiation->isCoordInLimits(curX, down))
			{
				if (isEnemySurroundedByMe(currSiation, myFraction, curX, down))
				{
					enemyWictimCount++;
				}
			}
			if (currSiation->isCoordInLimits(left, curY))
			{
				if (isEnemySurroundedByMe(currSiation, myFraction, left, curY))
				{
					enemyWictimCount++;
				}
			}
			if (currSiation->isCoordInLimits(right, curY))
			{
				if (isEnemySurroundedByMe(currSiation, myFraction, right, curY))
				{
					enemyWictimCount++;
				}
			}

			++innerIter;
		}

		++iter;
	}

	return enemyWictimCount * _Ai_RECURSION_CAN_KILL_ENEMY;

}


#define _NEIGHBOUR_NEAR_POSITION 1
std::vector<vecI2d> showAllPosiblePositions(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation,
	_FRACTION_INT_ frac, int x, int y)
{
	std::vector<vecI2d> retVal;

	if (!curSituation->isCoordInLimits(x, y))
	{
		vecI2d tempVec;
		retVal.push_back(tempVec);
		return retVal;
	}

	int
		leftCell = x - 1, leftLeftCell = leftCell - 1,
		rightCell = x + 1, rightRightCell = rightCell + 1,
		upCell = y - 1, upUpCell = upCell - 1,
		downCell = y + 1, downDownCell = downCell + 1;

	if (!isPlaceAcceptableToMove(curSituation, leftCell, y))
	{
		if (isPlaceAcceptableToMove(curSituation, leftLeftCell, y))
		{
			vecI2d tempVec;
			tempVec = vecI2d(leftLeftCell, y);
			retVal.push_back(tempVec);
		}
	}
	else 
	{
		vecI2d tempVec;

		tempVec= vecI2d(leftCell, y);
		retVal.push_back(tempVec);
	}

	if (!isPlaceAcceptableToMove(curSituation, rightCell, y))
	{
		if (isPlaceAcceptableToMove(curSituation, rightRightCell, y))
		{
			vecI2d tempVec;

			tempVec = vecI2d(rightRightCell, y);
			retVal.push_back(tempVec);
		}
	}
	else
	{
		vecI2d tempVec;

		tempVec = vecI2d(rightCell, y);
		retVal.push_back(tempVec);
	}
	/////////////

	if (!isPlaceAcceptableToMove(curSituation, x, upCell))
	{
		if (isPlaceAcceptableToMove(curSituation, x, upUpCell))
		{
			vecI2d tempVec;

			tempVec = vecI2d(x, upUpCell);
			retVal.push_back(tempVec);
		}
	}
	else 
	{
		vecI2d tempVec;

		tempVec= vecI2d(x, upCell);
		retVal.push_back(tempVec);
	}
	
	if (!isPlaceAcceptableToMove(curSituation, x, downCell))
	{
		if (isPlaceAcceptableToMove(curSituation, x, downDownCell))
		{
			vecI2d tempVec;

			tempVec = vecI2d(x, downDownCell);
			retVal.push_back(tempVec);
		}
	}
	else
	{
		vecI2d tempVec;

		tempVec = vecI2d(x, downCell);
		retVal.push_back(tempVec);
	}
	
	return retVal;
}










#define shortLimitCheck curSituation->isCoordInLimits
#define NOT !
#define _AI_NOT_EQUAL_TEAM_NONE != _BFL_TEAM_NONE

int AIRecursionData::calcSquareVal(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, int X, int Y, _FRACTION_INT_ frac)
{

	unsigned short int enemyCount = 0;
	unsigned short int myTeamCount = 0;
	_FRACTION_INT_ tempTeam;

	for (int y = 0; y < curSituation->getSizeVertical(); y++)
	{
		for (int x = 0; x < curSituation->getSizeHorizonal(); x++)
		{

			if (shortLimitCheck(x, y) && curSituation->getElem(x, y) _AI_NOT_EQUAL_TEAM_NONE)
			{
				tempTeam = *curSituation->getElem(x, y);
				if (frac == tempTeam)
				{
					myTeamCount++;
				}
				if (tempTeam == getMyEnemy(frac))
				{
					enemyCount++;

				}

			}

		}

	}

	int retSquareValue = 0;
	retSquareValue = _AI_MY_TEAM_SQUARES_VALUE * myTeamCount - enemyCount * _AI_ENEMY_TEAM_SQUARES_VALUE;
	
	int canKillEnemysCount = AIRecursionData::killEnemySquareValue(curSituation, frac);
	retSquareValue += canKillEnemysCount;

	int canBeKilledByEnemysCount = - AIRecursionData::killEnemySquareValue(curSituation, getMyEnemy(frac));
	retSquareValue += canBeKilledByEnemysCount;

	return retSquareValue;
}

#undef shortLimitCheck
#undef NOT
#undef _AI_NOT_EQUAL_TEAM_NONE

bool AIRecursionData::isSquareInMyTeamRecurce(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* curSituation, _FRACTION_INT_ curFraction, int x, int y)
{
	_FRACTION_INT_ curObject;
	curObject = *curSituation->getElem(x, y);

	if (curObject != curFraction)
	{
		return false;
	}
	return true;

}

void AIRecursionData::moveSquare(AIVecPosFromPosTo newPos)
{
	if (!curSituation.isCoordInLimits(newPos.posTo.getX(), newPos.posTo.getY()))
	{
		return;
	}
	_FRACTION_INT_ tempElem;
	tempElem = *curSituation.getElem(newPos.posFrom.getX(), newPos.posFrom.getY());

	curSituation.setElem(_BFL_TEAM_NONE, newPos.posFrom.getX(), newPos.posFrom.getY());
	curSituation.setElem(tempElem, newPos.posTo.getX(), newPos.posTo.getY());


}

std::vector<AIVecPosFromPosTo> AIRecursionData::getAllPossibleToMoveMyCells(_AI_INTELLIGENCE_FRACTION_DYNAMIC_ARR* currSituation, _FRACTION_INT_ myTeam)
{
	std::vector<AIVecPosFromPosTo> retVec;

	std::vector<vecI2d> allSquaresOfMyTeam;

	for (int y = 0; y < currSituation->getSizeVertical(); y++)
	{
		for (int x = 0; x < currSituation->getSizeHorizonal(); x++)
		{

			if (isSquareInMyTeamRecurce(currSituation, myTeam, x, y))
			{
				allSquaresOfMyTeam.push_back(vecI2d(x, y));

			}
		}
	}

	std::vector<vecI2d>::iterator myTeamSqIter = allSquaresOfMyTeam.begin();
	while (myTeamSqIter != allSquaresOfMyTeam.end())
	{
		vecI2d curSq;
		curSq = (*myTeamSqIter);

		std::vector<vecI2d> posibbleCurTurns = showAllPosiblePositions(currSituation, myTeam,
			curSq.getX(), curSq.getY());

		if (!posibbleCurTurns.empty())
		{
			std::vector<vecI2d>::iterator possibleTurnIter = posibbleCurTurns.begin();
			while (possibleTurnIter != posibbleCurTurns.end())
			{
				vecI2d curPossibleTurn = *possibleTurnIter;
				if (isPlaceAcceptableToMove(currSituation, curPossibleTurn.getX(), curPossibleTurn.getY()))
				{
					AIVecPosFromPosTo FTPosToRetValVec;
					FTPosToRetValVec.posFrom = curSq;
					FTPosToRetValVec.posTo = curPossibleTurn;
					FTPosToRetValVec.value = _BFL_INTELLIGENCE_MOVE_CELL_CUSTOM;
					retVec.push_back(FTPosToRetValVec);
				}
				++possibleTurnIter;
			}
		}

		++myTeamSqIter;
	}

	return retVec;
}


std::vector<AIVecPosFromPosTo> AIRecursionData::getAllPossibleTurns(_FRACTION_INT_ myTeam)
{
	std::vector<AIVecPosFromPosTo> retVec;

	

	retVec = getAllPossibleToMoveMyCells(&curSituation, myTeam);

	std::vector<AIVecPosFromPosTo> createCellTurns;
	createCellTurns = showPlacesToCreateMyCquare(&curSituation, myTeam, retVec);

	if (!createCellTurns.empty())
	{
		std::vector<AIVecPosFromPosTo>::iterator iter = createCellTurns.begin();

		while (iter != createCellTurns.end())
		{
			retVec.push_back(*iter);

			++iter;
		}
	}

	return retVec;

}

bool AIRecursionData::wasPosInTurnList(vecI2d curPos)
{

	for (int i = 0; i < previousPos.size(); i++)
	{
		if (curPos == previousPos[i])
		{
			return true;
		}
	}
	return false;

}

#undef brk



