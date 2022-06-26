

#ifndef _GAMESIMULATION_H_
#define _GAMESIMULATION_H_

#include "OeDataBase.h"
#include "Menu.h"
#include "Player.h"
#include "BattleForLifeGameComponents.h"
#include "GameSimConnector.h"
#include "GameSimStructs.h"

#define GAMESIMULATION_ERR_NO_DATABASE_PTR "GAMESIMULATION_ERR_NO_DATABASE_PTR"

/*
	������ ��������� �������� ��������
	����� ����������� ������ ���� �� ���� ������ ����� 

*/

class GameSimulation;
typedef GameSimulation GameSim;

class GameSimulation
{
private:
	GameSimConnector GSimCon; //��������� ���.���� � ����� ������
	BattleForLifeRules gameRule; //������ � ��������� ���
	Player humanPlaterOne; //���������� ������ �����
	Player humanPlaterTwo; //���������� ������ ������

public:

	

	GameSimulation(OEDataBase* dataBasePtr) : 
		humanPlaterOne(&gameRule, GSimCon.getDBReference()->getPlayerOneData(), _BFL_TEAM_DOWN_SIDE),
		humanPlaterTwo(&gameRule, GSimCon.getDBReference()->getPlayerTwoData(), _BFL_TEAM_UP_SIDE),
		gameRule(&GSimCon),  GSimCon(dataBasePtr)
	{
		std::cout << "Game sim constr\n";
	}

	//������������� ��������� �������� ���.����, ������������� ������� �������
	void GameSimulationInitialisation();
	
	void setGameSimulationRepherence(OEDataBase* dataBasePtr) { GSimCon.setDBReference(dataBasePtr); }

	bool isGameSim_NOT_FullInit()
	{
		if (NULL == GSimCon.getDBReference() || NULL == GSimCon.getGameSimDataRef())
		{
			return true;
		}
		return false;


	}

	~GameSimulation()
	{
		GSimCon.~GameSimConnector();
	}

	void GSimInputHandler(void); //���������� ������� �������
	void GSimStartMainFunction(void); //������� ������� ������� ���������
	void GSimCreateStartBaseGameElements(int arrSizeX, int arrSizeY); //�������������� ��������� ������� ������
	
	GameSimConnector* getConnector()
	{
		return &GSimCon;
	}


};





#endif // !_GAMESIMULATION_H_
