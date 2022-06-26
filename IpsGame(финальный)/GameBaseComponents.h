
#ifndef GAMEBASECOMPONENTS_H_
#define GAMEBASECOMPONENTS_H_
#include <string>

#include <iostream>
#include <vector>
#define _GBC_OBJECT_TYPE "GameBaseObject"
#define _GBC_OBJECT_STANDART_NAME "NoGameObjectName"
#define _GBC_OBJECT_STANDART_FREE_DATA "NoFreeData"

class GameBaseObject;
typedef GameBaseObject GBO;

class VectorInt2D;
typedef VectorInt2D vecI2d;

class DynamicIntArray2D;
typedef DynamicIntArray2D DIA2D;

#define GBC_TYPE_VECINT2D "VectorInt2D"

template<class DA>
void delete2DArray(DA** arr, int sizeHorizontal, int sizeVertical)
{
	for (int y = 0; y < sizeVertical; y++)
	{
		for (int x = 0; x < sizeHorizontal; x++)
		{
			delete[] arr[y];
			arr[y] = NULL;
		}

	}
	delete[] arr;
	arr = NULL;
}

/*
	класс игровой клетки
*/

class GameBaseObject
{
public:
	GameBaseObject();
	~GameBaseObject();

	//***************************/

	void setGBOName(std::string NewName) { GBOName = NewName; }
	std::string* getGBONamePtr() { return &GBOName; }

	/*********************************/

	void setGBOType(std::string NewType) { GBOType = NewType; }
	std::string* getGBOTypePtr() { return &GBOType; }

	/*********************************/

	void setGBOFreeData(std::string NewFreeData) { GBOFreeData = NewFreeData; }
	std::string* getGBOFreeDataPtr() { return &GBOFreeData; }

protected:
	std::string GBOName; 
	std::string GBOType; //—троковый тип
	std::string GBOFreeData; //ƒополнительна€ строкова€ информаци€ (используетс€ дл€ храни€ команды игрока)
};

#define _GBO_VECTOR_2D_NOT_SET -2
#define _GBO_VECTOR_ERR_VEC_NOT_INIT "GBO_VECTOR_ERR_VEC_NOT_INIT"


/*
	 ласс математического вектора с несколькими операци€ми над ним
*/

class VectorInt2D
{
	
public:
	VectorInt2D();
	VectorInt2D(int X, int Y);

	bool operator ==(VectorInt2D compareVec)
	{
		
		if (this->getX() == compareVec.getX() && this->getY() == compareVec.getY())
		{
			return true;
		}
		return false;
	}

	bool operator !=(VectorInt2D compareVec)
	{
		if (this->getX() == compareVec.getX() && this->getY() == compareVec.getY())
		{
			return false;
		}
		return true;


	}

	std::string getStrCoords()
	{

		return "X: " + std::to_string(getX()) + "\tY: " + std::to_string(getY());

	}

	~VectorInt2D();

	void setX(int newCoordX) { vecCoordX = newCoordX; }
	int getX() 
	{

		return vecCoordX; 
	}

	void setY(int newCoordY) { vecCoordY = newCoordY; }
	int getY() 
	{ 

		return vecCoordY; 
	}

	void setVectorI2D(int newX, int newY) { vecCoordX = newX; vecCoordY = newY; }
	void setVectorI2D(vecI2d newVec) { vecCoordX = newVec.getX(); vecCoordY = newVec.getY(); }

protected:
	int vecCoordX = _GBO_VECTOR_2D_NOT_SET;
	int vecCoordY = _GBO_VECTOR_2D_NOT_SET;
};

#define __GBO_CURSOR_LIMIT_NOT_SET -1
#define __GBO_CURSOR_START_POS_NOT_SET -2

#define __GBO_VECTOR_GSIM_OUT_OF_RANGE -3
#define __GBO_VECTOR_GSIM_OUT_OF_RANGE_VEC vecI2d(__GBO_VECTOR_GSIM_OUT_OF_RANGE, __GBO_VECTOR_GSIM_OUT_OF_RANGE)

#define __GBO_CURSOR_ERR_LIMIT_NOT_SET "GBO_CURSOR_ERR_LIMIT_NOT_SET"
#define __GBO_CURSOR_ERR_NO_POSITION_SET "GBO_CURSOR_ERR_NO_POSITION_SET"
#define __GBO_CURSOR_VEC_NOT_SET vecI2d(__GBO_CURSOR_START_POS_NOT_SET, __GBO_CURSOR_START_POS_NOT_SET)

/*
	 ласс курсора
	 урсор - показывает местоположение клетки и позвол€ет работать точечно с ней
	—одержатс€ действи€ над курсором
*/

class Cursor
{
private:
	VectorInt2D curPos, //позици€ курсора
				topAndLeftLimiter, //ограничитель сверху и слева
				BottomAndRightLimiter; //ограничитель снизу и справа

public:
	Cursor(VectorInt2D startPos);
	Cursor();
	vecI2d getCursorPos()
	{
		return curPos;
		
	}
	void setCursor(int X, int Y);
	void setCursor(vecI2d newPos);
	vecI2d* getCursorPtr()
	{
		return &curPos;
	}

	bool isLimitsSet();

	void setTopLeftLim(vecI2d lim)
	{
		topAndLeftLimiter = vecI2d(lim);
	}
	void setBotRightLim(vecI2d lim)
	{
		BottomAndRightLimiter = vecI2d(lim);
	}

	void crsUP();

	void crsDOWN();

	void crsLEFT();

	void crsRIGHT();

	bool isAcceptableToMoveCursor(int x, int y);
};

#endif


