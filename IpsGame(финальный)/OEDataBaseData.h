


#ifndef _OEDATABASE_DATA_
#define _OEDATABASE_DATA_

#include "GraphicCoreStructs.h"
#include "Vector2DTemplate.h"
#include "GameBaseComponents.h"

#include "GameSimStructs.h"

class DBGrCoreData;
class DBGrCoreData
{
public:

	void setGrCConsoleOutData(GrCorePrintData newGrCConsoleOut) { ConsoleOut = newGrCConsoleOut; }
	GrCorePrintData* getGrCConsoleOutDataPtr() { return &ConsoleOut; }

	GrCoreMiddleWorkingData* getMiddleData() { return &middleData; }

	DBGrCoreData()
	{
		ConsoleOut = GrCorePrintData();
	}
	~DBGrCoreData(){}

	void appendProcLog(std::string newMessage)
	{
		processLog.append(newMessage + "\n");
	}

	std::string throwFullProcLog()
	{
		std::string retStr = processLog;
		processLog.clear();
		return retStr;
	}

private:

	//PUT HERE REAL ONJECTS.
	//not pointer

	GrCorePrintData ConsoleOut;
	std::string processLog;
	GrCoreMiddleWorkingData  middleData;

};

#define _FROM_CURSOR 0
#define _TO_CURSOR 1
#define _UNS_SHORT_INT unsigned short int
#define _DB_INTELLIGENCE_DATA_NO_SWAP_CURSORES -1

class DBIntelligenceData
{

protected:

	Cursor playerCursorFrom;
	Cursor playerCursorTo;

	_UNS_SHORT_INT currCursor = _FROM_CURSOR;

	std::vector<vecI2d> possiblePlayerPos;
public:

	std::vector<vecI2d> getPossiblePlayerPos()
	{
		return possiblePlayerPos;
	}

	std::vector<vecI2d> givePossiblePlayerPos()
	{
		std::vector<vecI2d> temp = possiblePlayerPos;
		possiblePlayerPos.clear();
		return temp;
	}

	void clearPossiblePos()
	{
		possiblePlayerPos.clear();
	}

	void setPossiblePlayerPos(std::vector<vecI2d> curPossiblePos)
	{
		possiblePlayerPos.clear();
		possiblePlayerPos = curPossiblePos;
	}

	DBIntelligenceData() {}

	_UNS_SHORT_INT getCurrCursorNum()
	{
		return currCursor;
	}

	Cursor* getCurrCusor()
	{
		switch (getCurrCursorNum())
		{
		case _FROM_CURSOR:
		{
			return &playerCursorFrom;

			break;
		}
		case _TO_CURSOR:
		{
			return &playerCursorTo;
			break;
		}


		default:
			break;
		}
		return NULL;
	}

	_UNS_SHORT_INT swapCursor()
	{
		if (currCursor == _FROM_CURSOR)
		{
			currCursor = _TO_CURSOR;
			return currCursor;
		}
		else if (currCursor == _TO_CURSOR)
		{
			currCursor = _FROM_CURSOR;
			return currCursor;
		}

		return _DB_INTELLIGENCE_DATA_NO_SWAP_CURSORES;

	}

	Cursor* getCursorFrom()
	{
		return &playerCursorFrom;
	}
	Cursor* getCursorTo()
	{
		return &playerCursorTo;
	}

	void setCursorFrom(VectorInt2D cursorFrom)
	{
		playerCursorFrom.setCursor(cursorFrom.getX(), cursorFrom.getY());
	}

	void setCursorTo(VectorInt2D cursorTo)
	{
		playerCursorTo.setCursor(cursorTo.getX(), cursorTo.getY());
	}

};

class DBGameSimData;
class DBGameSimData
{
public:
	DBGameSimData()
	{
		std::cout << "DBGameSimData constr" << std::endl;
	}
	~DBGameSimData() {}

	DynamicIntArray2DTemplated<GameBaseObject>* getArrTemplInterface()
	{
		return &gameSimGBOArr2DTempl;

	}

	void setGameSimMenuMode(int newMode)
	{
		gameSimMenuInputMode = newMode;
	}

	int getGameSimMenuMode()
	{
		return gameSimMenuInputMode;
	}

	void setCurrFractionTurn(unsigned short int fraction)
	{
		currentFractionTurn = fraction;
	}

	unsigned short int getCurrentFractionTurn()
	{
		return currentFractionTurn;

	}

	DBIntelligenceData* getPlayerOneData()
	{
		return &PlayerOneData;
	}

	DBIntelligenceData* getPlayerTwoData()
	{
		return &PlayerTwoData;
	}

	void setGSimArrSizeHorizontal(int newSize)
	{
		GSimArrSizeHor = newSize;

	}

	int getGSimArrSizeHorizontal()
	{
		return GSimArrSizeHor;
	}

	void setGSimArrSizeVertical(int newSize)
	{
		GSimArrSizeVert = newSize;
	}

	int getGSimArrSizeVertical()
	{
		return GSimArrSizeVert;
	}


private:

	DynamicIntArray2DTemplated<GameBaseObject> gameSimGBOArr2DTempl;
	unsigned short int currentFractionTurn;

	int gameSimMenuInputMode = 0;

	int GSimArrSizeHor = _GSIM_ARR_SIZE_NOT_SET;
	int GSimArrSizeVert = _GSIM_ARR_SIZE_NOT_SET;

	DBIntelligenceData PlayerOneData;
	DBIntelligenceData PlayerTwoData;

};

class DBMenuData
{
private:

	std::string menuString;

	int keyInputInt;
	int keyCase;

	bool isNeedToSkipInput = false;

	bool isMainMenuActive = true;
	bool isPausePageActive = false;
	bool isGameOverPageActive = false;

	unsigned short int losedFraction = 0;

	int menuPage;

	Cursor menuCursor;
public:
	DBMenuData(){}

	void setLosedFraction(unsigned short int team)
	{
		losedFraction = team;
	}

	unsigned short int getLosedFraction()
	{
		return losedFraction;
	}

	void setNeedToSkipInput(bool onOff)
	{
		isNeedToSkipInput = onOff;
	}

	bool getNeedToSkipInputStatus()
	{
		return isNeedToSkipInput;
	}

	void setGameOverMenu(bool onOff)
	{
		isGameOverPageActive = onOff;
	}

	bool getGameOverPageStatus()
	{
		return isGameOverPageActive;
	}

	void setMenuString(std::string newStr)
	{
		menuString = newStr;
	}

	void setMainMenuActive(bool onOff)
	{
		isMainMenuActive = onOff;
	}

	bool getMainMenuStatus()
	{
		return isMainMenuActive;
	}

	void setPausePageStatus(bool onOff)
	{
		isPausePageActive = onOff;
	}

	bool getPausePageStatus()
	{
		return isPausePageActive;
	}

	std::string getMenuString()
	{
		return menuString;
	}

	void setPage(int newPage)
	{
		setNeedToSkipInput(true);
		menuPage = newPage;
	}

	int getPage()
	{
		return menuPage;
	}

	Cursor* getCursor()
	{
		return &menuCursor;
	}

	void setKeyCase(int cse)
	{
		keyCase = cse;
	}

	int getKeyCase()
	{
		return keyCase;
	}


	int* getKeyInputInt()
	{
		return &keyInputInt;
	}

	void setKeyInputInt(int intInput)
	{
		keyInputInt = intInput;

	}

};

#endif // !_OEDATABASE_DATA_

