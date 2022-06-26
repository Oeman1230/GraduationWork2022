
#ifndef BATTLEFORLIFECOMPONENTS_H_
#define BATTLEFORLIFECOMPONENTS_H_

#include "GameBaseComponents.h"
#include "GameSimConnector.h"
#include <vector>

#define _BFL_TYPE_CREATURE_SQUARE "creatureSquare"
#define _BFL_STANDART_NAME "creatureSquareName"

#define _BFL_TEAM_ERR_NO_FRACTION_CHOSEN "BFL_TEAM_ERR_NO_FRACTION_CHOSEN"

#define _BFL_TEAM_NONE 0
#define _BFL_TEAM_UP_SIDE 2
#define _BFL_TEAM_DOWN_SIDE 1

#define _BFL_RULES_NECESSARY_SQUARES 3

#define _FRACTION_INT_ short unsigned int


/*
	Коннектор игровых правил с БД
*/


class BattleForLifeConnector : public OEDBConnector
{
private:
	GameSimConnector* GSimCon;
	DynamicIntArray2DTemplated<GameBaseObject>* gObjArr;

public:

	BattleForLifeConnector(GameSimConnector* GSimConRef) : OEDBConnector(GSimConRef->getDBReference()), GSimCon(GSimConRef)
	{}
	DynamicIntArray2DTemplated<GameBaseObject>* getArr()
	{
		return getDBReference()->getGameSimDataPtr()->getArrTemplInterface();
	}

	GameSimConnector* getGSimCon()
	{
		return GSimCon;
	}

};


#define _BFL_RULES_POSSIBLE_POS_NOT_FOUND -2

/* || vecI2d(_BFL_RULES_POSSIBLE_POS_NOT_FOUND, _BFL_RULES_POSSIBLE_POS_NOT_FOUND) || */
#define _BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC vecI2d(_BFL_RULES_POSSIBLE_POS_NOT_FOUND, _BFL_RULES_POSSIBLE_POS_NOT_FOUND)

/*
	Класс правил игры "Борьба за жизнь"
	Содержатся игровые действия и события
	Класс выполняет действия над реальными объектами по условиям правил игры

*/

class BattleForLifeRules
{
private:

	BattleForLifeConnector gameRuleCon; //коннектор 
	_FRACTION_INT_ fractionTurn = _BFL_TEAM_NONE; //текущая команда на данном ходу

public:
	BattleForLifeRules(GameSimConnector* GameSimCon) : gameRuleCon(GameSimCon) 
	{
		std::cout << "Rules Constr\n";
	}

	BattleForLifeConnector* getBFTRulesCon()
	{
		return &gameRuleCon;
	}

	GameSimConnector* getGSimCon()
	{
		return gameRuleCon.getGSimCon();
	}

	bool isPlaceAcceptableToMove(int X, int Y); //доступно ли место для перемещения

	void setCurrPlayingFraction(_FRACTION_INT_ currentFraction)
	{
		fractionTurn = currentFraction;
	}

	_FRACTION_INT_ getCurrPlayingFraction()
	{
		return fractionTurn;
	}

	void swapFraction() //меняем текущую команду
	{
		switch (getCurrPlayingFraction())
		{

		case _BFL_TEAM_DOWN_SIDE:
		{
			fractionTurn = _BFL_TEAM_UP_SIDE;
			break;
		}

		case _BFL_TEAM_UP_SIDE:
		{
			fractionTurn = _BFL_TEAM_DOWN_SIDE;
			break;
		}
		case _BFL_TEAM_NONE:
		{
			throw _BFL_TEAM_ERR_NO_FRACTION_CHOSEN;
		}
		default:
			break;
		}
	}

	bool moveCell(_FRACTION_INT_ curFraction, int curX, int curY, int newX, int newY); //двигаем клетку по координатам

	bool moveCell(_FRACTION_INT_ curFraction, vecI2d vecFrom, vecI2d vecTo)//двигаем клетку по координатам векторов
	{
		return moveCell(
		//
			curFraction, vecFrom.getX(), vecFrom.getY(), vecTo.getX(), vecTo.getY()
		//
		);
	}
	//0 - //Nothing surrounds//	||	1 - _BFL_TEAM_DOWN_SIDE	||	2 - _BFL_TEAM_UP_SIDE
	_FRACTION_INT_ whatFractionSurrounds(int X, int Y); //проверяем какие клетки окружают текущую
	//0 - //Nothing surrounds//	||	1 - _BFL_TEAM_DOWN_SIDE	||	2 - _BFL_TEAM_UP_SIDE
	_FRACTION_INT_ whatFractionSurrounds(VectorInt2D currentPosition)
	{
		
		return whatFractionSurrounds(
			currentPosition.getX()
			,
			currentPosition.getY()
		);

	}

	bool createSquareByPressintEnter(); //Создание новой клетки, при соблюдении условий

	GameBaseObject createSquareWithTeam(_FRACTION_INT_ fraction); //Созданием клетки с указанием команды

	void destroySquareInSurroundings(); //уничтожение клетки в окружении врагов

	int countSquaresOfOneFraction(_FRACTION_INT_ curFraction); //посчитать все клетки из одной команды

	bool isGameOver();

	std::vector<vecI2d> showAllPosiblePositions(int X, int Y); //выдать все доступные точки для перемещения
	std::vector<vecI2d> showAllPosiblePositions(VectorInt2D currentPosition)
	{
		return showAllPosiblePositions(
			currentPosition.getX()
			,
			currentPosition.getY()
		);
	}

	const int _NEIGHBOUR_NEAR_POSITION = 1;
};

#endif // !BATTLEFORLIFECOMPONENTS_H_

