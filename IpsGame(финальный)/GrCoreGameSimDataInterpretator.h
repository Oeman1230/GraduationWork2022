
//GrCoreGameSimDataInterpretator
#ifndef GRAPHICCORE_GAMESIMDATA_INTERPRETATOR_H_
#define GRAPHICCORE_GAMESIMDATA_INTERPRETATOR_H_

#include "OeDataBase.h"
#include "GameSimulation.h"

#define GR_CORE_INTERPRET_ERR_NO_CONNECTOR_PTR "GR_CORE_INTERPRET_ERR_NO_CONNECTOR_PTR"
#define GR_CORE_INTERPRET_ERR_NOT_FULL_INIT "GR_CORE_INTERPRET_ERR_NOT_FULL_INIT"
#define GR_CORE_CONNECTOR_ERR_NO_DATA_BASE_PTR "GR_CORE_CONNECTOR_ERR_NO_DATA_BASE_PTR"

/*
	Коннектор графического ядра с базой данных
	Хранит в себе прямой доступ к данным граф.ядра


*/

//GrCoreDBConnector(p_DataBase)
class GrCoreDBConnector : public OEDBConnector {

public:
	GrCoreDBConnector(OEDataBase* p_DataBase) : OEDBConnector(p_DataBase)
	{

		if (NULL == p_DataBase)
		{
			throw GR_CORE_CONNECTOR_ERR_NO_DATA_BASE_PTR;
		}

		GrCDataReference = getDBReference()->getGrCData();
		convertedGameSimArrayRef = GrCDataReference->getMiddleData()->get2DArayInterface();
		charArrayRef = GrCDataReference->getMiddleData()->getCharArr();


	}

	DBIntelligenceData* getPlayerOneData()
	{
		return getDBReference()->getPlayerOneData();
	}

	DBIntelligenceData* getPlayerTwoData()
	{
		return getDBReference()->getPlayerTwoData();
	}

	DBGrCoreData* getGrCDataRef()
	{
		return GrCDataReference;
	}

	DynamicIntArray2DTemplated<std::string>* getConvGSimArrRef()
	{

		return convertedGameSimArrayRef;
	}

	DynamicIntArray2DTemplated<std::string>* getCharArrRef()
	{

		return charArrayRef;
	}

protected:
	
	DBGrCoreData* GrCDataReference;
	DynamicIntArray2DTemplated<std::string>* convertedGameSimArrayRef;
	
	DynamicIntArray2DTemplated<std::string>* charArrayRef;

};


/*
	Интерпретатор данных игровой симулации
	Модуль считывает и переводит все данные игры в удобные для работы
	- объекты, которые не зависят от своих оригиналов и не меняют их структуры

*/

class GrCoreGameSimDataInterpretator;

/*GrCoreGameSimDataInterpretator(GrCoreDBConnector* newGrCConRef)
|| (GrCoreDBConnector* newGrCConRef, GameSimConnector* newGameSimConRef)*/
class GrCoreGameSimDataInterpretator
{

public:

	const StringSTD INTRP_EMPTY_GAMEOBJ_ = ".";
	const StringSTD INTRP_SMTH_IN_GAMEOBJ = "1";

	GrCoreGameSimDataInterpretator(GrCoreDBConnector* newGrCConRef, GameSimConnector* newGameSimConRef)
	{
		GrCConReference = newGrCConRef;
		middleDataRef = GrCConReference->getGrCDataRef()->getMiddleData();

		GameSimConReference = newGameSimConRef;
		gameSimDataRef = GameSimConReference->getGameSimDataRef();

	}
	
	GrCoreGameSimDataInterpretator(GrCoreDBConnector* newGrCConRef):

		GameSimConReference(NULL), GrCConReference(newGrCConRef),

		middleDataRef(GrCConReference->getGrCDataRef()->getMiddleData()),

		gameSimDataRef(GrCConReference->getDBReference()->getGameSimDataPtr())

	{

		std::cout << "Interpr construct start\n";

		if (NULL == newGrCConRef)
		{
			throw GR_CORE_INTERPRET_ERR_NO_CONNECTOR_PTR;
		}

		std::cout << "Interpr construct end\n";
	}

	void interpretatorInitialisation(OEDataBase* p_DataBase);

	~GrCoreGameSimDataInterpretator()
	{
		GrCConReference = NULL;
	}

	GrCoreDBConnector* getGrCConRef()
	{
		return GrCConReference;
	}

	GameSimConnector* getGameSimConRef()
	{
		return GameSimConReference;
	}

	bool isNOTGrCInterprFullInitialised()
	{
		if (NULL == GrCConReference || NULL == gameSimDataRef)
			return true;
		return false;
	}

	void interpretateBaseGameSimInfoToGraphicCoreInfo();

	void convertGameSimDataToArr();

	void setMiddleDataRef(GrCoreMiddleWorkingData* ref)
	{
		middleDataRef = ref;
	}

	GrCoreMiddleWorkingData* getMiddleDataRef()
	{
		return middleDataRef;
	}

	DBGameSimData* getGameSimData()
	{
		return gameSimDataRef;
	}

private:
	
	GrCoreDBConnector* GrCConReference;
	GrCoreMiddleWorkingData* middleDataRef;

	GameSimConnector* GameSimConReference;
	DBGameSimData* gameSimDataRef;

};
typedef GrCoreGameSimDataInterpretator GrCInterpr;


#endif GRAPHICCORE_GAMESIMDATA_INTERPRETATOR_H_// !

