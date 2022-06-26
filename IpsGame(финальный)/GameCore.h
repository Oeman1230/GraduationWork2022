



#ifndef GAMECORE_H_
#define GAMECORE_H_

#include "OeDataBase.h"
#include "GraphicCoreStructs.h"
#include "GraphicCore.h"

#include "GameSimulation.h"
#include "Menu.h"

/*
	Core input params:
	int: flag
*/
struct GCStartingArgs
{
	int testFlag;

};

/*
	Core ending values
	int: Value
	bool: isSuccess
*/
struct GCReturnValues
{
	int testRetVal;
	bool isSuccess;
};

/*
	Здесь содержится объявление ядра всей игры.
	Ядро содержит другие подядра и базу данныъ

*/
class GameCore
{
public:
	//starts main loop
	GCReturnValues GCstartMainFunc(GCStartingArgs GCInpArgs); 

	void GCInitiateModules();
	
	GameCore() : GrCore_ex(getDBptr()) , gameSim_ex(getDBptr()),
							mainMenu(getDBptr()), DataBase()
	{
		isGCRunning = false;
	
	}

	GraphicCore getGrCore()
	{
		return GrCore_ex;
	}

	GraphicCore* getGrCorePtr()
	{
		return &GrCore_ex;
	}
	OEDataBase* getDBptr() { return &DataBase; }

private:

	OEDataBase DataBase;		//экземпляр модуля базы данных
	GraphicCore GrCore_ex;		//экземпляр модуля граф.ядра
	GameSimulation gameSim_ex;	//экземпляр модуля сим.игры
	MenuInterface mainMenu;		//экземпляр модуля меню

	bool isGCRunning; // is game active. 
};

#endif // !GAMECORE_H_

