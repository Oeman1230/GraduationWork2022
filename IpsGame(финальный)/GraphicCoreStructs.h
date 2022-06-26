


#ifndef GRAPHICCORESTRUCTS_H_
#define GRAPHICCORESTRUCTS_H_

#include <iostream>
#include <string>
#include <sstream>
#include "GameBaseComponents.h"
#include "Vector2DTemplate.h"


#define GRC_PRINT_LINE 1
#define GRC_PRINT_TO_LINE_END 2
#define GRC_PRINT_INT_ARRAY 3
#define GRC_PRINT_STR_ARRAY_BY_MAIN_ONLY 4

typedef std::string StringSTD;

class GrCoreMiddleWorkingData
{

private:
	DynamicIntArray2DTemplated<std::string> convertedGameSimArray;
	std::string convertedGameSimArrayStr;
	DynamicIntArray2DTemplated<std::string> charArray;

public:

	DynamicIntArray2DTemplated<std::string>* get2DArayInterface() 
	{ 
		return &convertedGameSimArray;
	}

	DynamicIntArray2DTemplated<std::string>* getConvrGSimArr()
	{
		return &convertedGameSimArray;
	}

	std::string* getConvertedGSimArrToStr()
	{
		return &convertedGameSimArrayStr;
	}

	DynamicIntArray2DTemplated<std::string>* getCharArr()
	{
		return &charArray;
	}

	void setConvertedArray(DynamicIntArray2DTemplated<std::string> newArr)
	{
		convertedGameSimArray = newArr;
	}

	GrCoreMiddleWorkingData(){}

};

class GrCorePrintData
{
public:
	std::string outputPrintData;

	std::string* getOutputString() { return &consoleOutputStr; }

protected:

	//PUT HERE REAL ONJECTS.
	//not pointer

	std::string consoleOutputStr;
};

class GrCoreGraphicInfo
{
public:
	GrCoreGraphicInfo() : consoleOutputStrStream(NULL) {}
	std::ostringstream* getOutStrStreamPtr() { return &consoleOutputStrStream; }

protected:
	std::ostringstream consoleOutputStrStream;
};

#define _GRC_STRUCTS_WORKDATA_ERR_NO_LARGE_ARR "GRC_STRUCTS_WORKDATA_ERR_NO_LARGE_ARR"

/*
	int _SPACE_SIZE || 2DArrr<String> LargeArr
	vec2D getGSimArrSize || vecI2d getLargeArrMaxSides
*/
class GrCMiddleWorkProcessData
{
public:
	DynamicIntArray2DTemplated<std::string>* getLargeGSimStrArr()
	{
		return &largeConsoleGSimStrArr;
	}

	vecI2d getLargeArrMaxSides()
	{

		largeArrSizeX = largeConsoleGSimStrArr.getSizeHorizonal();
		largeArrSizeY = largeConsoleGSimStrArr.getSizeVertical();

		if (largeArrSizeX == 0 || largeArrSizeY == 0)
		{
			throw _GRC_STRUCTS_WORKDATA_ERR_NO_LARGE_ARR;
		}

		return vecI2d(largeArrSizeX, largeArrSizeY);
	}

	void setGSimArrSize(int sizeX, int sizeY)
	{
		GSimArrSizeX = sizeX;
		GSimArrSizeY = sizeY;

	}

	VectorInt2D getGSimArrSize()
	{

		return vecI2d(GSimArrSizeX, GSimArrSizeY);

	}

	void setFraction(unsigned short int newFraction)
	{
		fraction = newFraction;
	}

	unsigned short int getFraction()
	{
		return fraction;
	}

	const int _SPACE_SIZE = 2;

private:
	DynamicIntArray2DTemplated<std::string> largeConsoleGSimStrArr;

	unsigned short int fraction;

	int GSimArrSizeX;
	int GSimArrSizeY;

	int largeArrSizeX;
	int largeArrSizeY;

};


struct GrCoreInputArgs
{
	int flag;
};

/*
	This struct contains output data type and it's params
*/

struct GrCoreReturnValues
{
	int val;
};

//class GrCoreDBConnector;

const std::string TabSpace = "\t";
const std::string Space = " ";
const std::string endll = "\n";

#endif // !GRAPHICCORESTRUCTS_H_
