#include "Menu.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

#include <string>

#include "BattleForLifeGameComponents.h"

#define brk break

void MenuInterface::keyBoardInput()
{
	if (menuCon.getMenuData()->getNeedToSkipInputStatus() == true)
	{
		menuCon.getMenuData()->setNeedToSkipInput(false);
		menuCon.getMenuData()->setKeyCase(_MENU_CASE_NO_ARG);
		return;
	}

	std::string inpStr = std::to_string(_MENU_CASE_START_VALUE);

	ULONGLONG toGo = 1000, start = GetTickCount64();

	int keyInt = _MENU_CASE_START_VALUE;

	while ((start + toGo) >= GetTickCount64())
	{
		if (_kbhit())
		{
			keyInt = _getch();

			menuCon.directLogAppend(std::to_string(keyInt));

			break;
		}
		else
		{
			continue;
		}

	}

	menuCon.getMenuData()->setKeyCase(useMenuSwitch(keyInt));
}

void MenuInterface::solveCommand()
{
	int curPage = menuCon.getMenuData()->getPage();

	switch (curPage)
	{
	case _MENU_PAGE_EXIT:
	{
		brk;
	}
	case _MENU_PAGE_MAIN:
	{
		mainMenuPage();
		brk;
	}
	case _MENU_PAGE_GAME_SIM:
	{
		brk;
	}
	case _MENU_PAGE_GAME_OVER:
	{
		gameOverPage();
		brk;
	}
	case _MENU_PAGE_PAUSE:
	{
		pausePage();
		break;

	}
	case _MENU_PAGE_RESTART_GAME:
	{
		brk;
	}
	default:
		break;
	}
	
	
}

bool MenuInterface::isCaseExists(int keyInt)
{
	if (_MENU_CASE_NO_ARG == keyInt)
	{
		return false;
	}
	return true;

}

#define _MENU_KEY_CURS_UP 38
#define _MENU_KEY_CURS_DOWN 40
#define _MENU_KEY_CURS_LEFT 37
#define _MENU_KEY_CURS_RIGHT 39

#define _MENU_KEY_W 119
#define _MENU_KEY_A 97
#define _MENU_KEY_S 115
#define _MENU_KEY_D 100
#define _MENU_KEY_E 101

#define _MENU_KEY_ESC 27
#define _MENU_KEY_ENTER 13
#define _MENU_KEY_BACKSPACE 8

int MenuInterface::useMenuSwitch(int keyCommand)
{
	switch (keyCommand)
	{
	case _MENU_KEY_CURS_UP:{}
	case _MENU_KEY_W:
	{
		return _MENU_CASE_SET_UP;
		brk;
	}
	case _MENU_KEY_S:{}
	case _MENU_KEY_CURS_DOWN:
	{
		return _MENU_CASE_SET_DOWN;
		brk;
	}
	case _MENU_KEY_A:{}
	case _MENU_KEY_CURS_LEFT:
	{
		return _MENU_CASE_SET_LEFT;
		brk;
	}
	case _MENU_KEY_CURS_RIGHT:{}
	case _MENU_KEY_D:
	{
		return _MENU_CASE_SET_RIGHT;
		brk;
	}
	case _MENU_KEY_ESC:
	{
		return _MENU_CASE_EXIT;
		brk;
	}
	case _MENU_KEY_E: {}
	case _MENU_KEY_ENTER:
	{
		return _MENU_CASE_SET_ENTER;
		brk;
	}
	case _MENU_KEY_BACKSPACE:
	{
		return _MENU_CASE_SET_RESET;
		brk;
	}
	default:
	{
		return _MENU_CASE_NO_ARG;
		break;
	}	
	}

}

#define _MENU_MAIN_PAGE_WIDTH 1
#define _MENU_MAIN_PAGE_HEIGHT 2

std::string MenuInterface::pausePage()
{
	

	std::vector<std::string> strArr;
	std::string retStr;

	const std::string resumeGame = "Resume game";
	const std::string exitGame = "Exit game";
	const std::string backToMainMenu = "Return to main menu";

	strArr.push_back(resumeGame);
	strArr.push_back(backToMainMenu);
	strArr.push_back(exitGame);

	retStr.append("\n\n");

	Cursor* crsRef = menuCon.getMenuData()->getCursor();
	if (!crsRef->isLimitsSet() || menuCon.getMenuData()->getPausePageStatus() == false)
	{

		menuCon.getMenuData()->setPausePageStatus(true);
		crsRef->setBotRightLim(vecI2d(_MENU_MAIN_PAGE_WIDTH, strArr.size()));
		crsRef->setTopLeftLim(vecI2d(0, 0));
		crsRef->setCursor(vecI2d(0, 0));
	}

	menuCon.directLogAppend(crsRef->getCursorPos().getStrCoords());

	int menuCase = menuCon.getMenuData()->getKeyCase();

	menuCon.directLogAppend(std::to_string(menuCase));
	switch (menuCase)
	{
	case _MENU_CASE_SET_UP:
	{
		crsRef->crsUP();
		brk;
	}
	case _MENU_CASE_SET_DOWN:
	{

		crsRef->crsDOWN();
		brk;
	}
	case _MENU_CASE_SET_ENTER:
	{
		int curY = crsRef->getCursorPos().getY();
		std::string strArrElem = strArr.at(curY);

		if (strArrElem._Equal(resumeGame))
		{
			
			menuCon.getMenuData()->setPage(_MENU_PAGE_GAME_SIM);
			menuCon.getMenuData()->setPausePageStatus(false);
		}
		if (strArrElem._Equal(exitGame))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_EXIT);
			menuCon.getMenuData()->setPausePageStatus(false);
		}
		if (strArrElem._Equal(backToMainMenu))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_MAIN);
			menuCon.getMenuData()->setPausePageStatus(false);

		}

		brk;
	}
	default:
		menuCon.getMenuData()->setKeyCase(_MENU_CASE_NO_ARG);
		break;
	}

	for (int y = 0; y < strArr.size(); y++)
	{
		if (crsRef->getCursorPos().getY() == y)
		{
			retStr.append(">>>>\t");
		}
		else
		{
			retStr.append("\t");
		}

		retStr.append(strArr.at(y));
		retStr.append("\n");
	}

	retStr.append("\n\tGame by Moskalev Yuri Antonovich. \n\n");
	retStr.append("\tNizhniy Novgorod. NGTU. 2022\n\n");
	menuCon.getMenuData()->setMenuString(retStr);

	return retStr;
}

#define _MENU_PAUSE_PAGE_WIDTH 1
#define _MENU_PAUSE_PAGE_HEIGTH 1

std::string MenuInterface::mainMenuPage()
{
	std::vector<std::string> strArr;
	std::string retStr;

	const std::string exitGame = "Exit game";
	const std::string playWithBot = "Person VS Robot";
	const std::string playerWithPlayer = "Person VS Person";
	const std::string botVSbot = "Robot VS Robot";
	const std::string changeArrSize = "Change Game Sim array size";

	strArr.push_back(playWithBot);
	strArr.push_back(botVSbot);
	strArr.push_back(playerWithPlayer);
	strArr.push_back(changeArrSize);

	strArr.push_back(exitGame);

	Cursor* crsRef = menuCon.getMenuData()->getCursor();
	if (!crsRef->isLimitsSet() || menuCon.getMenuData()->getMainMenuStatus() == false)
	{

		menuCon.getMenuData()->setMainMenuActive(true);
		crsRef->setBotRightLim(vecI2d(_MENU_MAIN_PAGE_WIDTH, strArr.size()));
		crsRef->setTopLeftLim(vecI2d(0, 0));
		crsRef->setCursor(vecI2d(0, 0));
	}

	retStr.append("\n");
	retStr.append("\tBattle for life\n\n");
	
	retStr.append("\t-WASD- for navigation. ENTER button for selection command\n\n");

	menuCon.directLogAppend(crsRef->getCursorPos().getStrCoords());

	int menuCase = menuCon.getMenuData()->getKeyCase();

	menuCon.directLogAppend(std::to_string(menuCase));
	switch (menuCase)
	{
	case _MENU_CASE_SET_UP:
	{
		crsRef->crsUP();

		brk;
	}
	case _MENU_CASE_SET_DOWN:
	{

		crsRef->crsDOWN();
		brk;
	}
	case _MENU_CASE_SET_ENTER:
	{
		int curY = crsRef->getCursorPos().getY();
		std::string strArrElem = strArr.at(curY);

		if (strArrElem._Equal(exitGame))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_EXIT);
			menuCon.getMenuData()->setMainMenuActive(false);
		}
		if (strArrElem._Equal(playWithBot))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_PLAY_WITH_BOT);
			menuCon.getMenuData()->setMainMenuActive(false);

		}
		if (strArrElem._Equal(botVSbot))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_PLAY_BY_BOTS);
			menuCon.getMenuData()->setMainMenuActive(false);


		}
		if (strArrElem._Equal(playerWithPlayer))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_PLAY_PERSON_WITH_PERSON);
			menuCon.getMenuData()->setMainMenuActive(false);
		}
		if (strArrElem._Equal(changeArrSize))
		{
			std::cout << "\nInsert horizontal size.\nMinimum 3. Max 7: ";
			int sizeH = -1, sizeV = -1;
			std::cin >> sizeH;
			if (sizeH > 7 || sizeH < 3)
			{
				std::cout << "\nUnvalid arr size. Try Again";
				Sleep(1000);
				return "Unvalid";
			}
			std::cout << "\nInsert vertical size.\nMinimum 3. Max 7: ";
			std::cin >> sizeV;
			if (sizeV > 7 || sizeV < 3)
			{
				std::cout << "\nUnvalid arr size. Try Again";
				Sleep(1000);
				return "Unvalid";
			}
			menuCon.getDBReference()->getGameSimDataPtr()->setGSimArrSizeHorizontal(sizeH);
			menuCon.getDBReference()->getGameSimDataPtr()->setGSimArrSizeVertical(sizeV);

			menuCon.getMenuData()->setPage(_MENU_PAGE_CHANGE_ARR_SIZE);
			menuCon.getMenuData()->setMainMenuActive(false);
			menuCon.getMenuData()->setNeedToSkipInput(true);
		}

		brk;
	}
	default:
		menuCon.getMenuData()->setKeyCase(_MENU_CASE_NO_ARG);
		break;
	}

	for (int y = 0; y < strArr.size(); y++)
	{
		if (crsRef->getCursorPos().getY() == y)
		{
			retStr.append(">>>>\t");
		}
		else
		{
			retStr.append("\t");
		}

		retStr.append(strArr.at(y));

		if (strArr.at(y)._Equal(changeArrSize)
			&& menuCon.getDBReference()->getGameSimDataPtr()->getGSimArrSizeHorizontal() != _GSIM_ARR_SIZE_NOT_SET
			&& menuCon.getDBReference()->getGameSimDataPtr()->getGSimArrSizeVertical() != _GSIM_ARR_SIZE_NOT_SET
			)
		{
			retStr.append(" GSim size("
				+ std::to_string(menuCon.getDBReference()->getGameSimDataPtr()->getGSimArrSizeHorizontal())
				+ " , "
				+ std::to_string(menuCon.getDBReference()->getGameSimDataPtr()->getGSimArrSizeVertical())
				+ ")"
			);

		}
		retStr.append("\n");
	}

	retStr.append("\n\tGame by Moskalev Yuri Antonovich. \n\n");
	retStr.append("\tNizhniy Novgorod. NGTU. 2022\n\n");

	menuCon.getMenuData()->setMenuString(retStr);

	return retStr;
}

#define _MENU_GAME_OVER_PAGE_WIDTH 1
#define _MENU_GAME_OVER_PAGE_HEIGHT 2


std::string MenuInterface::gameOverPage()
{
	
	std::vector<std::string> strArr;
	std::string retStr;

	const std::string restartGame = "Restart game";
	const std::string exitGame = "Exit game";
	const std::string backToMainMenu = "Return to main menu";

	strArr.push_back(restartGame);
	strArr.push_back(backToMainMenu);
	strArr.push_back(exitGame);

	Cursor* crsRef = menuCon.getMenuData()->getCursor();
	if (!crsRef->isLimitsSet() || menuCon.getMenuData()->getGameOverPageStatus() == false)
	{

		menuCon.getMenuData()->setGameOverMenu(true);
		crsRef->setBotRightLim(vecI2d(_MENU_GAME_OVER_PAGE_WIDTH, strArr.size()));
		crsRef->setTopLeftLim(vecI2d(0, 0));
		crsRef->setCursor(vecI2d(0, 0));
	}

	retStr.append("\n\n");

	menuCon.directLogAppend(crsRef->getCursorPos().getStrCoords());

	int menuCase = menuCon.getMenuData()->getKeyCase();

	menuCon.directLogAppend(std::to_string(menuCase));
	switch (menuCase)
	{
	case _MENU_CASE_SET_UP:
	{
		crsRef->crsUP();
		brk;
	}
	case _MENU_CASE_SET_DOWN:
	{

		crsRef->crsDOWN();
		brk;
	}
	case _MENU_CASE_SET_ENTER:
	{
		int curY = crsRef->getCursorPos().getY();
		std::string strArrElem = strArr.at(curY);

		if (strArrElem._Equal(restartGame))
		{

			menuCon.getMenuData()->setPage(_MENU_PAGE_RESTART_GAME);
			menuCon.getMenuData()->setPausePageStatus(false);
			menuCon.getMenuData()->setNeedToSkipInput(true);
		}
		if (strArrElem._Equal(exitGame))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_EXIT);
			menuCon.getMenuData()->setPausePageStatus(false);
		}
		if (strArrElem._Equal(backToMainMenu))
		{
			menuCon.getMenuData()->setPage(_MENU_PAGE_MAIN);
			menuCon.getMenuData()->setPausePageStatus(false);
			menuCon.getMenuData()->setNeedToSkipInput(true);

		}
		brk;
	}
	default:
		menuCon.getMenuData()->setKeyCase(_MENU_CASE_NO_ARG);
		break;
	}

	if (menuCon.getDBReference()->getMenuData()->getLosedFraction() == _BFL_TEAM_UP_SIDE)
	{
		retStr.append("\tThe Up team lose the game\n\n");
	}
	else if (menuCon.getDBReference()->getMenuData()->getLosedFraction() == _BFL_TEAM_DOWN_SIDE)
	{
		retStr.append("\tThe Down team lose the game\n\n");
	}
	else if(menuCon.getDBReference()->getMenuData()->getLosedFraction() == _BFL_TEAM_NONE)
	{
		retStr.append("\tFriendship won the game\n\n");
	}

	for (int y = 0; y < strArr.size(); y++)
	{
		if (crsRef->getCursorPos().getY() == y)
		{
			retStr.append(">>>>\t");
		}
		else
		{
			retStr.append("\t");
		}

		retStr.append(strArr.at(y));
		retStr.append("\n");
	}

	retStr.append("\n\tGame by Moskalev Yuri Antonovich. \n\n");
	retStr.append("\tNizhniy Novgorod. NGTU. 2022\n\n");

	menuCon.getMenuData()->setMenuString(retStr);
	return retStr;
}


#undef brk

