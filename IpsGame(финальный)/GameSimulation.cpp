#include "GameSimulation.h"
#include "GameBaseComponents.h"
#define brk break

#define NOT !

void GameSimulation::GameSimulationInitialisation()
{
	if (NULL == GSimCon.getDBReference())
	{
		throw GAMESIMULATION_CONNECTOR_ERR_NO_DATABASE_PTR;

	}

	int GSimSizeX, GSimSizeY;
	GSimSizeX = GSimCon.getGameSimDataRef()->getGSimArrSizeHorizontal();
	GSimSizeY = GSimCon.getGameSimDataRef()->getGSimArrSizeVertical();

	if (GSimSizeX == _GSIM_ARR_SIZE_NOT_SET || GSimSizeY == _GSIM_ARR_SIZE_NOT_SET)
	{
		//стандартные размеры массива
		GSimCreateStartBaseGameElements(_GSIM_ARR_SIZE_X, _GSIM_ARR_SIZE_Y);
	}
	else
	{
		GSimCreateStartBaseGameElements(GSimSizeX, GSimSizeY);
	}

	//Задает стартовые значения игры
	
	//Инициализируем значения игрока и выьирам тим интеллекта
	//humanPlaterOne.playerInit(_PLAYER_INTELLIGENCE_MODE_PERSON_MIND); //Обычный игрок

	humanPlaterOne.playerInit(_PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND); //Компьютер
	//Для того, чтобы показать работоспособность основных элементов, выключаю компьютерного игрока 
	humanPlaterTwo.playerInit(_PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND); //и ставлю обычного

}



//Функция проверяет в зависимости от данных с меню, какие операции стоит совершить
void GameSimulation::GSimInputHandler()
{
	if (isGameSim_NOT_FullInit())
	{
		return;
	}

	switch (GSimCon.getMenuDataRef()->getPage())
	{
	case _MENU_PAGE_RESTART_GAME:
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_GAME_SIM);

		int GSimSizeX, GSimSizeY;
		GSimSizeX = GSimCon.getGameSimDataRef()->getGSimArrSizeHorizontal();
		GSimSizeY = GSimCon.getGameSimDataRef()->getGSimArrSizeVertical();

		if (GSimSizeX == _GSIM_ARR_SIZE_NOT_SET || GSimSizeY == _GSIM_ARR_SIZE_NOT_SET)
		{
			//стандартные размеры массива
			GSimCreateStartBaseGameElements(_GSIM_ARR_SIZE_X, _GSIM_ARR_SIZE_Y);
			return;
		}

		GSimCreateStartBaseGameElements(GSimSizeX, GSimSizeY);

		return;
		break;
	}
	case _MENU_PAGE_GAME_SIM:
	{
		break;
	}
	case _MENU_PAGE_PLAY_WITH_BOT:
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_RESTART_GAME);
		humanPlaterOne.playerInit(_PLAYER_INTELLIGENCE_MODE_PERSON_MIND); //Обычный игрок
		humanPlaterTwo.playerInit(_PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND);

		return;
	}
	case _MENU_PAGE_PLAY_BY_BOTS:
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_RESTART_GAME);
		humanPlaterOne.playerInit(_PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND); 
		humanPlaterTwo.playerInit(_PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND);

		return;
	}
	case _MENU_PAGE_PLAY_PERSON_WITH_PERSON:
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_RESTART_GAME);
		humanPlaterOne.playerInit(_PLAYER_INTELLIGENCE_MODE_PERSON_MIND);
		humanPlaterTwo.playerInit(_PLAYER_INTELLIGENCE_MODE_PERSON_MIND);

		return;
	}
	case _MENU_PAGE_CHANGE_ARR_SIZE:
	{

		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_MAIN);

		int GSimSizeX, GSimSizeY;
		GSimSizeX = GSimCon.getGameSimDataRef()->getGSimArrSizeHorizontal();
		GSimSizeY = GSimCon.getGameSimDataRef()->getGSimArrSizeVertical();

		if (GSimSizeX == _GSIM_ARR_SIZE_NOT_SET || GSimSizeY == _GSIM_ARR_SIZE_NOT_SET)
		{
			//стандартные размеры массива
			GSimCreateStartBaseGameElements(_GSIM_ARR_SIZE_X, _GSIM_ARR_SIZE_Y);
			return;
		}
		GSimCreateStartBaseGameElements(GSimSizeX, GSimSizeY);

		return;
	}

	default:
		return;
		break;
	}

	int menuCase = GSimCon.getMenuDataRef()->getKeyCase();
	
	switch (menuCase)
	{

	case _MENU_CASE_SET_UP:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_MOVE_CELL_UP);

		break;
	}

	case _MENU_CASE_SET_DOWN:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_MOVE_CELL_DOWN);

		break;
	}

	case _MENU_CASE_SET_LEFT:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_MOVE_CELL_LEFT);
		break;
	}

	case _MENU_CASE_SET_RIGHT:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_MOVE_CELL_RIGHT);
		brk;
	}
	case _MENU_CASE_SET_ENTER:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_CELL_ENTER);
		brk;
	}
	case _MENU_CASE_SET_RESET:
	{
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_CELL_RESET);

		brk;
	}
	case _MENU_CASE_EXIT:
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_PAUSE);

		return;
	}

	default:
		GSimCon.getGameSimDataRef()->setGameSimMenuMode(_GAMESIM_MODE_NO_COMMAND);

		break;
	}

	GameSim::GSimStartMainFunction();
}


void GameSimulation::GSimStartMainFunction()
{
	gameRule.destroySquareInSurroundings();
	if (gameRule.isGameOver() == true)
	{
		GSimCon.getMenuDataRef()->setPage(_MENU_PAGE_GAME_OVER);
		return;
	}

	//Каждый такт цикла проверяется какой игрок
	switch (gameRule.getCurrPlayingFraction())
	{

	case _BFL_TEAM_DOWN_SIDE:
	{

		GSimCon.getGameSimDataRef()->setCurrFractionTurn(gameRule.getCurrPlayingFraction()); //Показывает текущего игрока
		GSimCon.directLogAppend("_BFL_TEAM_DOWN_SIDE");
		if (humanPlaterOne.makeTurn() == true) //При успешном выполнении хода
		{
			gameRule.swapFraction(); //передаём другому игроку ход
			GSimCon.getGameSimDataRef()->setCurrFractionTurn(_BFL_TEAM_UP_SIDE);
		}

		break;
	}

	case _BFL_TEAM_UP_SIDE:
	{
		GSimCon.getGameSimDataRef()->setCurrFractionTurn(gameRule.getCurrPlayingFraction());
		GSimCon.directLogAppend("_BFL_TEAM_UP_SIDE");
		if (humanPlaterTwo.makeTurn() == true)
		{
			gameRule.swapFraction();
			GSimCon.getGameSimDataRef()->setCurrFractionTurn(_BFL_TEAM_DOWN_SIDE);
		}
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
//Инициализация начальных значений игровых элементов
void GameSimulation::GSimCreateStartBaseGameElements(int arrSizeX, int arrSizeY)
{
	gameRule.setCurrPlayingFraction(_BFL_TEAM_DOWN_SIDE);

	GSimCon.getGameSimDataRef()->getArrTemplInterface()->createNewArray(arrSizeX, arrSizeY);

	GameBaseObject tempObj;
	tempObj.setGBOType(_BFL_TYPE_CREATURE_SQUARE);
	tempObj.setGBOName(_BFL_STANDART_NAME);

	for (int x = 0; x < arrSizeX; x++)
	{
		tempObj.setGBOFreeData(std::to_string(_BFL_TEAM_UP_SIDE));
		GSimCon.getGBOArr()->setElem(tempObj, x, 0);
		tempObj.setGBOFreeData(std::to_string(_BFL_TEAM_DOWN_SIDE));
		GSimCon.getGBOArr()->setElem(tempObj, x, arrSizeY - 1);
	}

}

#undef NOT
#undef brk


