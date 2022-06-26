#include "PersonIntelligence.h"
#include "GameBaseComponents.h"
#include "GameSimStructs.h"

#define brk break
void PersonIntelligence::intelligenceInit()
{
	int x = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeHorizonal();
	int y = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeVertical();

	if (x <= 0 || y <= 0)
	{
		throw "NO_WALUES";
	}


	getCursorFrom()->setTopLeftLim(vecI2d(0, 0));
	getCursorFrom()->setBotRightLim(vecI2d(x, y));
	getCursorFrom()->setCursor(x / 2, y / 2);

	getCursorTo()->setTopLeftLim(vecI2d(0, 0));
	getCursorTo()->setBotRightLim(vecI2d(x, y));
	getCursorTo()->setCursor(x / 2, y / 2);


}

//Действие при нажатии enter
void PersonIntelligence::menuComEnterFromCursorAction()
{
	//Если клетка из моей команды
	if (isSquareInMyTeam(getCursorFrom()->getCursorPos().getX(),
		getCursorFrom()->getCursorPos().getY()
	))
	{
		GameBaseObject curObject;
		curObject = *intelCon.getGSimDataRef()->getArrTemplInterface()->getElem(
			getCursorFrom()->getCursorPos().getX(),
			getCursorFrom()->getCursorPos().getY()
		);

		if (!curObject.getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE)) //Если не пустая клетка
		{
			std::vector<vecI2d> possiblePosArr;
			intelCon.getIntelligenceDataRef()->clearPossiblePos(); //очищаем предыдущие доступные ходы
			possiblePosArr = getRules()->showAllPosiblePositions(getCursorFrom()->getCursorPos()); //показываем доступыне ходы
			intelCon.getIntelligenceDataRef()->setPossiblePlayerPos(possiblePosArr); //отправляем в БД информацию о доступных полях
		}

		intelCon.getIntelligenceDataRef()->swapCursor(); //меняем курсор 
		intelCon.getIntelligenceDataRef()->getCursorTo()->setCursor(
			intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos()
		); //двигаем положение курсора конечной точки в положение курсора изначальной точки

	}

}

//комманда для сброса текущего действия, если у него несколько шагов
void PersonIntelligence::menuCommandReset()
{
	if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _TO_CURSOR) //если сейчас курсор конечной точки
	{
		intelCon.getIntelligenceDataRef()->getCurrCusor()->setCursor
		(
			intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos()
		); //перемещаем курсор конечной точки, в точку, откуда мы хотели совершить действие ранее
		intelCon.getIntelligenceDataRef()->swapCursor(); //меняем курсор конечной точки на курсор началбной точки
	}
	intelCon.getIntelligenceDataRef()->clearPossiblePos(); //убираем все доступные действия для клетки

}
//Обратка вариантов действий при нажатие на enter 
void PersonIntelligence::menuCommandEnter()
{

	if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _FROM_CURSOR) //если сейчас курсор начальной точки
	{

		menuComEnterFromCursorAction(); //Выполняем действие для курсора в первый раз

		return;
	}
	else if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _TO_CURSOR //если текущий курсор - это конечная точка
		&& getElemByCursor(getCurrCursor())->getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE))
	{
		
		if (intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos() //если положения двух курсоров совпадают
			== intelCon.getIntelligenceDataRef()->getCursorTo()->getCursorPos())
		{
			if (getRules()->whatFractionSurrounds(getCurrCursor()->getCursorPos()) == playerFraction) 
				//проверяем окружает ли моя команда клетку
			{
				intelCon.directLogAppend("_BFL_INTELLIGENCE_CREATE_CQUARE"); 

				setAction(_BFL_INTELLIGENCE_CREATE_CQUARE);//задаём комманду создания клетки 
				intelCon.getIntelligenceDataRef()->swapCursor(); //меняем курсор
				return;
			}
			menuCommandReset(); //если не моя команда, то сбрасываем ход
			return;

		}

		//если два курсора не находятся на одном месте

		std::vector<vecI2d> possibleTurns = intelCon.getIntelligenceDataRef()->getPossiblePlayerPos();

		std::vector<vecI2d>::iterator iter = possibleTurns.begin();

		
		while (iter != possibleTurns.end())
		{
			if ((*iter) == intelCon.getIntelligenceDataRef()->getCursorTo()->getCursorPos())
			{
				std::cout << "ff";
				setAction(_BFL_INTELLIGENCE_MOVE_CELL_CUSTOM); //даём команду на перемещение
				intelCon.getIntelligenceDataRef()->swapCursor(); //меняем курсоры
				intelCon.directLogAppend("_BFL_INTELLIGENCE_MOVE_CELL_CUSTOM");
				intelCon.getIntelligenceDataRef()->clearPossiblePos(); //очищаем доступные ходы
			}
			++iter;
		}


		return;
	}
	menuCommandReset(); //если ни одно условие не совпало, то сбрасываем ход
	setAction(_BFL_INTELLIGENCE_RESET);
}


void PersonIntelligence::chooseAction()
{
	switch (intelCon.getGSimDataRef()->getGameSimMenuMode())
	{
	case _GAMESIM_MODE_MOVE_CELL_UP:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsUP();

		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_DOWN:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsDOWN();
		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_LEFT:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsLEFT();
		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_RIGHT:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsRIGHT();
		brk;
	}
	case _GAMESIM_MODE_CELL_ENTER:
	{
		menuCommandEnter();
		brk;
	}
	case _GAMESIM_MODE_CELL_RESET:
	{
		menuCommandReset();
		setAction(_BFL_INTELLIGENCE_RESET);
		brk;
	}

	default:
		break;
	}
}

#undef brk
