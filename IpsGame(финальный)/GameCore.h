



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
	����� ���������� ���������� ���� ���� ����.
	���� �������� ������ ������� � ���� ������

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

	OEDataBase DataBase;		//��������� ������ ���� ������
	GraphicCore GrCore_ex;		//��������� ������ ����.����
	GameSimulation gameSim_ex;	//��������� ������ ���.����
	MenuInterface mainMenu;		//��������� ������ ����

	bool isGCRunning; // is game active. 
};

#endif // !GAMECORE_H_

