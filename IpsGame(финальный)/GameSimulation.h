

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
	ћодуль симул€ции игрового процесса
	«десь выполн€етс€ логика игры за один прогон цикла 

*/

class GameSimulation;
typedef GameSimulation GameSim;

class GameSimulation
{
private:
	GameSimConnector GSimCon; // оннектор сим.игры с базой данных
	BattleForLifeRules gameRule; //ќбъект с правилами гры
	Player humanPlaterOne; //Ёкземпл€ры игрока снизу
	Player humanPlaterTwo; //Ёкземпл€ры игрока сверху

public:

	

	GameSimulation(OEDataBase* dataBasePtr) : 
		humanPlaterOne(&gameRule, GSimCon.getDBReference()->getPlayerOneData(), _BFL_TEAM_DOWN_SIDE),
		humanPlaterTwo(&gameRule, GSimCon.getDBReference()->getPlayerTwoData(), _BFL_TEAM_UP_SIDE),
		gameRule(&GSimCon),  GSimCon(dataBasePtr)
	{
		std::cout << "Game sim constr\n";
	}

	//»нициализаци€ начальных значений сим.игры, накладываемых игровой логикой
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

	void GSimInputHandler(void); //ќбработчик входных комманд
	void GSimStartMainFunction(void); //главна€ функци€ игровой симул€ции
	void GSimCreateStartBaseGameElements(int arrSizeX, int arrSizeY); //»нициализирует начальные игровые данные
	
	GameSimConnector* getConnector()
	{
		return &GSimCon;
	}


};





#endif // !_GAMESIMULATION_H_
