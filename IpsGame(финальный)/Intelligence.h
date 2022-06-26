

#ifndef _INTELLIGENCE_H_
#define _INTELLIGENCE_H_


#include "OeDataBase.h"
#include "BattleForLifeGameComponents.h"

#define _BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_FROM "_BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_FROM"
#define _BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_TO "_BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_TO"

#define _BFL_INTELLIGENCE_NO_ACTION 0
#define _BFL_INTELLIGENCE_CURSOR_MOVE_ACTION 1
#define _BFL_INTELLIGENCE_MOVE_CELL_CUSTOM 2
#define _BFL_INTELLIGENCE_END_OF_TURN 3
#define _BFL_INTELLIGENCE_CREATE_CQUARE 4
#define _BFL_INTELLIGENCE_RESET 5

#define _BFL_INTELLIGENCE_DYNAMIC_GBO_ARR DynamicIntArray2DTemplated<GameBaseObject>

/*
	Коннектор данных интеллекта из БД с самим интеллектом 
*/

class IntelligenceConnector : public OEDBConnector
{
protected:
	DBGameSimData* GSimDataRef;
	DBIntelligenceData* intelDataRef;

public:
	IntelligenceConnector(OEDataBase* p_OEDataBase, DBIntelligenceData* intelDatRef) : OEDBConnector(p_OEDataBase)
	{
		intelDataRef = intelDatRef;
		playerCursorFrom = intelDataRef->getCursorFrom();
		playerCursorTo = intelDataRef->getCursorTo();
		GSimDataRef = getDBReference()->getGameSimDataPtr();
	}

	DBIntelligenceData* getIntelligenceDataRef()
	{
		return intelDataRef;
	}

	DBGameSimData* getGSimDataRef()
	{
		return GSimDataRef;
	}

	Cursor* playerCursorFrom;
	Cursor* playerCursorTo;

	~IntelligenceConnector()
	{
		playerCursorFrom = NULL;
		playerCursorTo = NULL;
		intelDataRef = NULL;
		GSimDataRef = NULL;
	}

};

/*
	Базовый класс интеллекта игрока
	Здесь содержатся общие и обязательные для всех игроков команды
*/

class Intelligence
{
protected:
	_FRACTION_INT_ playerFraction; //Текущая команда
	IntelligenceConnector intelCon; //Коннектор
	int chosenAction = _BFL_INTELLIGENCE_NO_ACTION; //Действие интеллекта
	BattleForLifeRules* BFLRules; //Ссылка на правила игры

public:

	_FRACTION_INT_ getFraction()
	{
		return playerFraction;
	}

	_BFL_INTELLIGENCE_DYNAMIC_GBO_ARR* getArr()
	{
		return intelCon.getGSimDataRef()->getArrTemplInterface();
	}

	Intelligence(OEDataBase* p_OEDataBase, DBIntelligenceData* dataRef, _FRACTION_INT_ fraction, BattleForLifeRules* rules) :
		playerFraction(fraction), intelCon(p_OEDataBase, dataRef),
		BFLRules(rules) {}

	Cursor* getCursorFrom()
	{
		if (NULL == intelCon.playerCursorFrom)
		{
			throw _BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_FROM;
		}

		return intelCon.playerCursorFrom;
	}
	Cursor* getCursorTo()
	{
		if (NULL == intelCon.playerCursorTo)
		{
			throw _BFC_INTELLIGENCE_CONNECTOR_ERR_NO_VEC_TO;
		}

		return intelCon.playerCursorTo;
	}

	Cursor* getCurrCursor()
	{
		return intelCon.getIntelligenceDataRef()->getCurrCusor();

	}

	GameBaseObject* getElemByCursor(Cursor* cursor)
	{
		GameBaseObject* retObj;
		retObj = intelCon.getGSimDataRef()->getArrTemplInterface()->getElem(
			cursor->getCursorPos().getX(),
			cursor->getCursorPos().getY()
		);
		return retObj;

	}

	BattleForLifeRules* getRules()
	{
		return BFLRules;
	}

	void setAction(int action)
	{
		chosenAction = action;
	}

	//обязательная для выполения функция выдачи команды
	int giveAction()
	{
		int temp = chosenAction;
		chosenAction = _BFL_INTELLIGENCE_NO_ACTION;
		return temp;
	}

	virtual ~Intelligence()
	{
		BFLRules = NULL;
	}

	virtual bool isSquareInMyTeam(int x, int y)
	{
		GameBaseObject curObject;
		curObject = *intelCon.getGSimDataRef()->getArrTemplInterface()->getElem(x, y);

		if (curObject.getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE))
		{
			return true;
		}

		if (!curObject.getGBOFreeDataPtr()->_Equal(std::to_string(playerFraction)))
		{
			return false;
		}
		return true;

	}
	//обязательная для исполнения функция инициализации
	virtual void intelligenceInit() {};
	//обязательная для исполнения функция выбора действия
	virtual void chooseAction() {};
};


#endif // !_INTELLIGENCE_H_
