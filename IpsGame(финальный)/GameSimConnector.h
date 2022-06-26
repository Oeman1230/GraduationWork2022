

#ifndef _GAME_SIMULATION_CONNECTOR_H_
#define _GAME_SIMULATION_CONNECTOR_H_

#include "OeDataBase.h"


#define GAMESIMULATION_CONNECTOR_ERR_NO_DATABASE_PTR "GAMESIMULATION_CONNECTOR_ERR_NO_DATABASE_PTR"

class GameSimConnector;
class GameSimConnector : public OEDBConnector
{
public:

	GameSimConnector(OEDataBase* dataBasePtr) : OEDBConnector(dataBasePtr),
		GameSimDataReference(getDBReference()->getGameSimDataPtr()),
		menuData(getDBReference()->getMenuData())

	{
		GBOArrRef = getGameSimDataRef()->getArrTemplInterface();
		std::cout << "game sim connector constructor\n";

	}

	~GameSimConnector()
	{
		OEDBConnector::~OEDBConnector();
	}

	DBGameSimData* getGameSimDataRef()
	{
		return GameSimDataReference;
	}

	DBMenuData* getMenuDataRef()
	{
		return menuData;
	}

	DynamicIntArray2DTemplated<GameBaseObject>* getGBOArr()
	{
		return GBOArrRef;
	}

	int getGBOArrMaxX()
	{
		return getGameSimDataRef()->getArrTemplInterface()->getSizeHorizonal();
	}

	int getGBOArrMaxY()
	{
		return getGameSimDataRef()->getArrTemplInterface()->getSizeVertical();
	}


protected:
	DBMenuData* menuData;
	DynamicIntArray2DTemplated<GameBaseObject>* GBOArrRef;
	DBGameSimData* GameSimDataReference;

};

#endif // !_GAME_SIMULATION_CONNECTOR_H_

