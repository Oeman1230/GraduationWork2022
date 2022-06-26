#include "GameCore.h"
#include "OeDataBase.h"
#include "GraphicCore.h"
#include <iostream>
#include <windows.h>


/*
	GameCore main function. There starts game
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	���������� ��������� � ������ ���� ������
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	�������� ���������� ������ ����� �������
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	���������� � ������� ���������
*/

GCReturnValues GameCore::GCstartMainFunc(GCStartingArgs GCInpArgs) 
{
	
	GCInitiateModules(); //�������������� �� ���� ������� ��������� ��������, ������� ��������� ������ ����

	isGCRunning = true; 
	GCReturnValues GCret; //�� ������������

	GrCoreInputArgs GrCarg; // ��������� ������ �� ����� ��� ����.����
	GrCarg.flag = _MENU_PAGE_GREETINGS;
	getDBptr()->getMenuData()->setPage(_MENU_PAGE_MAIN);

	//����� ��������� ������ ��������� �� �����. 

	getGrCorePtr()->GrCoreInputHandler(							//�������� ���������� ����� ������������ ����
		getDBptr()->getGrCData(),								//���������� ��������� � ������� ��� ����.����
		GrCarg													//�������� �������
	);
	
	Sleep(3000);
	while (isGCRunning != false)
	{

		mainMenu.keyBoardInput();//����������� ���� ��� ���������� ������� � ����������

		GrCarg.flag = getDBptr()->getMenuData()->getPage();

		gameSim_ex.GSimInputHandler(); //��������� ���� ��������� ���� ����� ���������� �����

		mainMenu.solveCommand();
		getGrCorePtr()->GrCoreInputHandler(							//�������� ���������� ����� ������������ ����
			getDBptr()->getGrCData(),								//���������� ��������� � ������� ��� ����.����
			GrCarg													//�������� �������
		);

		GrCarg.flag = getDBptr()->getMenuData()->getPage();
		//mainMenu.solveCommand();

		getGrCorePtr()->GrCoreInputHandler(							//�������� ���������� ����� ������������ ����
			getDBptr()->getGrCData(),								//���������� ��������� � ������� ��� ����.����
			GrCarg												//�������� �������
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


