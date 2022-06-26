
#ifndef MENU_H_
#define MENU_H_
#include "OeDataBase.h"
#include "OEDataBaseData.h"

#define _MENU_CASE_NO_ARG -1


#define _MENU_PAGE_EXIT 0
#define _MENU_PAGE_GREETINGS 1
#define _MENU_PAGE_MAIN 2
#define _MENU_PAGE_GAME_SIM 3
#define _MENU_PAGE_PAUSE 4
#define _MENU_PAGE_GAME_OVER 5
#define _MENU_PAGE_RESTART_GAME 6

#define _MENU_CASE_START_VALUE -999

#define _MENU_CASE_EXIT 0
#define _MENU_CASE_SET_UP 1
#define _MENU_CASE_SET_DOWN 2
#define _MENU_CASE_SET_LEFT 3
#define _MENU_CASE_SET_RIGHT 4
#define _MENU_CASE_SET_ENTER 5
#define _MENU_CASE_SET_RESET 6
#define _MENU_PAGE_PLAY_WITH_BOT 7
#define _MENU_PAGE_PLAY_BY_BOTS 8
#define _MENU_PAGE_PLAY_PERSON_WITH_PERSON 9
#define _MENU_PAGE_CHANGE_ARR_SIZE 10

class MenuConnector : public OEDBConnector
{
private:
	DBMenuData* menuDataRef;

public:
	MenuConnector(OEDataBase* p_dataBase) : OEDBConnector(p_dataBase)
	{
		menuDataRef = getDBReference()->getMenuData();
	}

	DBMenuData* getMenuData()
	{
		return menuDataRef;
	}
};

class MenuInterface
{
private:

	MenuConnector menuCon;

public:
	MenuInterface(OEDataBase* p_dataBase) : menuCon(p_dataBase){}

	void keyBoardInput();
	std::string pausePage();
	void solveCommand();
	bool isCaseExists(int keyInt);
	int useMenuSwitch(int keyCommand);
	std::string mainMenuPage();
	std::string gameOverPage();

};

//"BATTLE FOR LIFE"
const std::string _MENU_GREETING_MESSAGE("\n\n\t\
###   ##  ##### ##### #     #####   #####  ####  ####   \n\t\
#  # #  #   #     #   #     #       #     #    # #   #  \n\t\
###  #  #   #     #   #     ####    ###   #    # ####   \n\t\
#  # ####   #     #   #     #       #     #    # #   #  \n\t\
###  #  #   #     #   ##### #####   #      ####  #    # \n\
\n\t\t\t\
#     ##### ##### ##### \n\t\t\t\
#       #   #     #     \n\t\t\t\
#       #   ###   ###   \n\t\t\t\
#       #   #     #     \n\t\t\t\
##### ##### #     ##### \n\
");


#endif // !MENU_H_
