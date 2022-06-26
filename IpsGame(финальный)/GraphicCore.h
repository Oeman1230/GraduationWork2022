


#ifndef GRAPHICCORE_H_
#define GRAPHICCORE_H_
#include <iostream>
#include "GraphicCoreStructs.h"



#include "OeDataBase.h"
#include "GrCoreGameSimDataInterpretator.h"

#define GR_CORE_ERR_NO_DATABASE_PTR "GR_CORE_ERR_NO_DATABASE_PTR";

class GrCMiddleWorkProcessData;

/*
	Модуль графического ядра игры
	-Здесь реализована логика вывода на экран данных
	-Так же здесь происходит выбор каким образом необъодимо показывать данные

*/

//GraphicCore (OEDataBase* p_DataBase)
class GraphicCore
{



public:
       
	GraphicCore(OEDataBase* p_DataBase) : GrCConnector(p_DataBase), interpretator(&GrCConnector)
	{
		std::cout << "GrCore Constr\n";
	
	}

	//Инициализация начальных значений, накладываемых игровой логикой
	void GraphicCoreInitialization(OEDataBase* p_DataBase);
	
	//обработчких входных значений в графическое ядро
	GrCoreReturnValues GrCoreInputHandler(DBGrCoreData* p_DBRawGrCoreData, GrCoreInputArgs args);

	void compactSTRArrayToStr();

	void GrCCreateConsoleSTRArrWithSpaces();

	int coordFormula(int coord);

	vecI2d convertGSimCoordToLargeArrCoords(vecI2d gSimCoords);

	vecI2d convertGSimCoordToLargeArrCoords(int gSimX, int gSimY)
	{

		return convertGSimCoordToLargeArrCoords(vecI2d(gSimX, gSimY));
	}
    
	void GrCShowCursors();

	GrCoreDBConnector* getConnector()
	{
		return &GrCConnector;
	}

	GrCMiddleWorkProcessData* getWrkData()
	{
		return &workData;
	}
	
	void showPossiblePositionInArr();

private:
	/*
		Главная функция графического ядра
		args:GrCorePrintData, GrCoreInputArgs
	*/
	
	void workDataInit();

    GrCoreDBConnector GrCConnector; //Коннектор граф.ядра. Наследник коннектора БД
	GrCoreGameSimDataInterpretator interpretator; //Интерпретатор данных игры в графическом виде

	GrCMiddleWorkProcessData workData; //данные для удобной работы в пределах модуля

	GrCoreReturnValues GrCoreStartMainFunc(GrCorePrintData, GrCoreInputArgs);

};
typedef GraphicCore GrC_t;

#endif // !GRAPHICCORE_H_
