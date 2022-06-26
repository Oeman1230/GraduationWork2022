#include "GameCore.h"
#include "OeDataBase.h"
#include "GraphicCore.h"
#include <iostream>
#include <windows.h>


/*
	GameCore main function. There starts game
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Переменные объявлять в модуле базы данных
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Вызывать переменные только через геттеры
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Передавать в функции указатели
*/

GCReturnValues GameCore::GCstartMainFunc(GCStartingArgs GCInpArgs) 
{
	
	GCInitiateModules(); //инициализирует во всем модулях начальные значения, которые добавляет логика игры

	isGCRunning = true; 
	GCReturnValues GCret; //не используется

	GrCoreInputArgs GrCarg; // аргументы вывода на экран для граф.ядра
	GrCarg.flag = _MENU_PAGE_GREETINGS;
	getDBptr()->getMenuData()->setPage(_MENU_PAGE_MAIN);

	//здесь выводится первое сообщение на экран. 

	getGrCorePtr()->GrCoreInputHandler(							//Вызываем обработчик входа графического ядра
		getDBptr()->getGrCData(),								//Закидываем указатель с данными для граф.ядра
		GrCarg													//аргумент запуска
	);
	
	Sleep(3000);
	while (isGCRunning != false)
	{

		mainMenu.keyBoardInput();//запрашиваем меню для считывания команды с клавиатуры

		GrCarg.flag = getDBptr()->getMenuData()->getPage();

		gameSim_ex.GSimInputHandler(); //запускаем ядро симуляции игры через обработчик ввода

		mainMenu.solveCommand();
		getGrCorePtr()->GrCoreInputHandler(							//Вызываем обработчик входа графического ядра
			getDBptr()->getGrCData(),								//Закидываем указатель с данными для граф.ядра
			GrCarg													//аргумент запуска
		);

		GrCarg.flag = getDBptr()->getMenuData()->getPage();
		//mainMenu.solveCommand();

		getGrCorePtr()->GrCoreInputHandler(							//Вызываем обработчик входа графического ядра
			getDBptr()->getGrCData(),								//Закидываем указатель с данными для граф.ядра
			GrCarg												//аргумент запуска
		);
		int tempInt = getDBptr()->getMenuData()->getPage();
		if (tempInt == _MENU_PAGE_EXIT)
		{
			isGCRunning = false;
			GCret.isSuccess = true;
		}

	}
	
	return GCret;
}

void GameCore::GCInitiateModules()
{
	GrCore_ex.GraphicCoreInitialization(getDBptr());
	gameSim_ex.GameSimulationInitialisation();

}


