#include "GameBaseComponents.h"



GameBaseObject::GameBaseObject()
{
	setGBOName(_GBC_OBJECT_STANDART_NAME);
	setGBOType(_GBC_OBJECT_TYPE);
	setGBOFreeData(_GBC_OBJECT_STANDART_FREE_DATA);
}

GameBaseObject::~GameBaseObject()
{
	getGBONamePtr()->clear();
	getGBOTypePtr()->clear();
	getGBOFreeDataPtr()->clear();

}

VectorInt2D::VectorInt2D()
{
	setX(_GBO_VECTOR_2D_NOT_SET);
	setY(_GBO_VECTOR_2D_NOT_SET);
	
}

VectorInt2D::VectorInt2D(int X, int Y)
{
	setX(X);
	setY(Y);

}


VectorInt2D::~VectorInt2D()
{

}

Cursor::Cursor(VectorInt2D startPos)
{
	curPos = vecI2d(startPos);
	topAndLeftLimiter.setVectorI2D(__GBO_CURSOR_LIMIT_NOT_SET, __GBO_CURSOR_LIMIT_NOT_SET);
	BottomAndRightLimiter.setVectorI2D(__GBO_CURSOR_LIMIT_NOT_SET, __GBO_CURSOR_LIMIT_NOT_SET);

}

Cursor::Cursor()
{
	curPos = vecI2d(__GBO_CURSOR_START_POS_NOT_SET, __GBO_CURSOR_START_POS_NOT_SET);
	topAndLeftLimiter.setVectorI2D(__GBO_CURSOR_LIMIT_NOT_SET, __GBO_CURSOR_LIMIT_NOT_SET);
	BottomAndRightLimiter.setVectorI2D(__GBO_CURSOR_LIMIT_NOT_SET, __GBO_CURSOR_LIMIT_NOT_SET);


}


void Cursor::setCursor(int X, int Y)
{
	if (isAcceptableToMoveCursor(X, Y))
	{
		curPos.setVectorI2D(X, Y);
	}
	
	
}
void Cursor::setCursor(vecI2d newPos)
{
	setCursor(
		newPos.getX()
		,
		newPos.getY()
	);


}


bool Cursor::isLimitsSet()
{
	if (__GBO_CURSOR_LIMIT_NOT_SET == topAndLeftLimiter.getX() || __GBO_CURSOR_LIMIT_NOT_SET == BottomAndRightLimiter.getX())
	{
		return false;
	}
	if (__GBO_CURSOR_LIMIT_NOT_SET == topAndLeftLimiter.getY() || __GBO_CURSOR_LIMIT_NOT_SET == BottomAndRightLimiter.getY())
	{
		return false;
	}
	return true;
}


bool Cursor::isAcceptableToMoveCursor(int x, int y)
{
	if (!isLimitsSet())
	{
		throw __GBO_CURSOR_ERR_LIMIT_NOT_SET;
	}


	if (x >= BottomAndRightLimiter.getX() || x < topAndLeftLimiter.getX())
	{
		return false;
	}
	if (y >= BottomAndRightLimiter.getY() || y < topAndLeftLimiter.getY())
	{
		return false;
	}


	return true;


}

void Cursor::crsUP()
{

	if (curPos == vecI2d(__GBO_CURSOR_START_POS_NOT_SET, __GBO_CURSOR_START_POS_NOT_SET))
	{
		throw __GBO_CURSOR_ERR_NO_POSITION_SET;
	}

	int curX = curPos.getX();
	int curY = curPos.getY();

	if (isAcceptableToMoveCursor(curX, curY - 1))
	{
		curPos.setY(curY - 1);
	}
	
}
void Cursor::crsDOWN()
{
	int curX = curPos.getX();
	int curY = curPos.getY();

	if (isAcceptableToMoveCursor(curX, curY + 1))
	{
		curPos.setY(curY + 1);
	}
	
}
void Cursor::crsLEFT()
{
	int curX = curPos.getX();
	int curY = curPos.getY();

	if (isAcceptableToMoveCursor(curX - 1, curY))
	{
		curPos.setX(curX - 1);
	}

}
void Cursor::crsRIGHT()
{
	int curX = curPos.getX();
	int curY = curPos.getY();

	if (isAcceptableToMoveCursor(curX + 1, curY))
	{
		curPos.setX(curX + 1);
	}

}

