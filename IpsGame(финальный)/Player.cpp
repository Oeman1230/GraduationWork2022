
#include "Player.h"
#include "GameSimStructs.h"
#include "ArtificialIntelligence.h"

#define brk break

// Функция попытки сделать ход у игрока. Здесь выбираются варианты событий 
bool Player::makeTurn()
{
	//Выбираем действие
	getMind()->chooseAction(); 
	bool isSuccess = false;;
	int action = getMind()->giveAction(); //Выдаём действие
	switch (action) //выбираем из списка доступных действий
	{
	case _BFL_INTELLIGENCE_MOVE_CELL_CUSTOM:
	{
		//Движение клетки из позиции первого курсора во второй. Временно клетки можно перемещать в любое место
		isSuccess = rules->moveCell(
			getFraction(),
			getMind()->getCursorFrom()->getCursorPos(), getMind()->getCursorTo()->getCursorPos()
		);

		getMind()->getCursorFrom()->getCursorPtr()->setVectorI2D(
			getMind()->getCursorTo()->getCursorPos()
		);
		//Обработка успешности перемещения клетки
		if (true == isSuccess)
		{
			return true;
		}
		else
		{
			return false;
		}

		brk;
	}
	//Команда по созданию своей клетки
	case _BFL_INTELLIGENCE_CREATE_CQUARE:
	{
		isSuccess = rules->createSquareByPressintEnter();
		//Обработка успешности создания
		if (true == isSuccess)
		{
			return true;
		}
		else
		{
			return false;
		}
		brk;
	}
	//Команда сброса курсоров
	case _BFL_INTELLIGENCE_RESET:
	{
		return false;
		brk;
	}
	case _BFL_INTELLIGENCE_CURSOR_MOVE_ACTION:
	{
		brk;
	}
	case _BFL_INTELLIGENCE_NO_ACTION:
	{
		brk;
	}
	case _BFL_INTELLIGENCE_END_OF_TURN:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

#undef brk
//Инициализация начальных значений игрока
void Player::playerInit(int intelligenceMode)
{

	switch (intelligenceMode)
	{
	case _PLAYER_INTELLIGENCE_MODE_PERSON_MIND:
	{
		//Выбор игрока - человека
		setMind(
			new PersonIntelligence(rules->getGSimCon()->getDBReference(),
				intelDataRef,
				playerFraction,
				getBFLRules())
		);

		getMind()->intelligenceInit();
		break;
	}
	case _PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND:
	{
		//выбор игрока - компьютера
		setMind(
			new ArtificialIntelligence(rules->getGSimCon()->getDBReference(),
				intelDataRef,
				playerFraction,
				getBFLRules())
		);

		getMind()->intelligenceInit();
		break;
	}
	default:
		throw _PLAYER_INIT_ERR_INTELLIGENCE_MODE_UNDEF;

		break;
	}

}

