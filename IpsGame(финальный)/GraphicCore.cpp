#include "GraphicCore.h"
#include "Menu.h"

GrCoreReturnValues GraphicCore::GrCoreStartMainFunc(const GrCorePrintData printData, GrCoreInputArgs arg)
{
	system("cls");
	GrCoreReturnValues retVal;
	retVal.val = 0;
	//��������� ��� ������ � ���������� ���� ������������� � ����
	//std::cout << GrCConnector.getGrCDataRef()->throwFullProcLog() << std::endl;

	//����� ���������� ����� ������������ ���� ������ ����������
	switch (arg.flag)
	{
	case _MENU_PAGE_EXIT:
	{
		std::cout << "\nGame ended\n";
		return retVal;

		break;
	}
	case _MENU_PAGE_MAIN:
	{

		std::cout << GrCConnector.getDBReference()->getMenuData()->getMenuString() << std::endl;
		break;

	}
	case _MENU_PAGE_PAUSE:
	{
		std::cout << GrCConnector.getDBReference()->getMenuData()->getMenuString() << std::endl;
		break;
	}
	case _MENU_PAGE_GAME_OVER:
	{
		std::cout << GrCConnector.getDBReference()->getMenuData()->getMenuString() << std::endl;
		break;
	}
	case(_MENU_PAGE_GREETINGS):
	{

		std::cout << _MENU_GREETING_MESSAGE;
		break;
	}
	//������� ����� �� ����� ���� ������ �� ������ ���.����
	case(_MENU_PAGE_GAME_SIM):
	{
		interpretator.convertGameSimDataToArr(); //������������ ������������ ������ ����
		
		workDataInit(); //�������������� ������������� ���������� � �������

		GrCCreateConsoleSTRArrWithSpaces(); //�������� ������� ������� ������� �������� � ����������� �������
		showPossiblePositionInArr(); //���������� ��������� ��� ����������� ������ ����, ��� �������
		GrCShowCursors(); //���������� �������������� �������

		compactSTRArrayToStr(); //������� ������� ����� � ������� ������ ��� ������ �� �����

		std::cout << *getConnector()->getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString();
	}
	default:
		
		break;
	}
	return retVal;
}

//������� ���������� ������� ������� ��� ����.����
GrCoreReturnValues GraphicCore::GrCoreInputHandler(DBGrCoreData* p_DBRawGrCoreData, GrCoreInputArgs args)
{
	//�� ������ ������ ������ ������� ��� ��������
	GrCoreReturnValues GrCInpHandlret;
	GrCInpHandlret.val = 0;

	//int* retVal = &GrCInpHandlret.val;
	GrCorePrintData printData = *p_DBRawGrCoreData->getGrCConsoleOutDataPtr();

	GrCoreReturnValues GrCMainFuncSuccessHandler;
	GrCMainFuncSuccessHandler = GrCoreStartMainFunc(printData, args); //������ ������� ������� ����.����
	//Graphic core main function error handler
	if (GrCMainFuncSuccessHandler.val != 0) //��� ��������� ���������� ������ ��������� ��� ������
	{
		std::cout << "Grapric core Dead\n";
		GrCInpHandlret.val = -1;
	}

	return GrCInpHandlret;
}

//������������� ��������� �������� ������������� ����������
void GraphicCore::workDataInit()
{
	if (workData._SPACE_SIZE <= 0)
	{
		throw "_SPACE_SIZE_LESS_ZERO";
	}

	workData.setGSimArrSize(
		interpretator.getMiddleDataRef()->get2DArayInterface()->getSizeHorizonal()
		,
		interpretator.getMiddleDataRef()->get2DArayInterface()->getSizeVertical()
	);

	//�������� ������� ����� � ��������������� ������ ��� ��������
	workData.getLargeGSimStrArr()->createNewArray(
		workData._SPACE_SIZE + (workData._SPACE_SIZE + 1) * workData.getGSimArrSize().getX()
		,
		workData._SPACE_SIZE + (workData._SPACE_SIZE + 1) * workData.getGSimArrSize().getY()
	);
	workData.getLargeGSimStrArr()->fillArrayBy(" ");

}
//������������� ��������� ��������, ������������� ������� �������
void GraphicCore::GraphicCoreInitialization(OEDataBase* p_DataBase)
{
     //GrCConnector.temp = 0;

	if (NULL == p_DataBase)
	{
		throw GR_CORE_ERR_NO_DATABASE_PTR;
	}
	//������������� ��������������
	interpretator.interpretatorInitialisation(p_DataBase);

	std::cout << "GrCore Init\n";

}

//�������, ������� ������� ������ ����� �� ��������� ������ ������, ��� �������������� ��������
void GraphicCore::GrCCreateConsoleSTRArrWithSpaces()
{
	int consX = workData.getLargeGSimStrArr()->getSizeHorizonal();
	int consY = workData.getLargeGSimStrArr()->getSizeVertical();

	int maxX, maxY;
	maxX = GrCConnector.getConvGSimArrRef()->getSizeHorizonal();
	maxY = GrCConnector.getConvGSimArrRef()->getSizeVertical();
	
	int countY = 0;
	//�������� ������ �� ������� � ����� ������������� ������ � "�������" ������ � ������������ �� �������

	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			std::string elem = *GrCConnector.getGrCDataRef()->getMiddleData()->getConvrGSimArr()->getElem(x, y);
			int convX = coordFormula(x);
			int convY = coordFormula(y);
			workData.getLargeGSimStrArr()->setElem(elem, convX, convY);
		}

	}

}
//������� ��������� ��������� ������ � ���� ������ ��� ������ �� �����
void GraphicCore::compactSTRArrayToStr()
{
	GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->clear();

	int consX = workData.getLargeGSimStrArr()->getSizeHorizonal();
	int consY = workData.getLargeGSimStrArr()->getSizeVertical();

	if (GrCConnector.getDBReference()->getGameSimDataPtr()->getCurrentFractionTurn() == _BFL_TEAM_UP_SIDE)
	{
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("     Up team Turn\n");
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
		for (int i = 0; i < consX + 6; i++)
		{
			
			GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("V");
		}
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n");
	}
	else
	{
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n\n");
	}


	GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
	for (int i = 0; i < consX + 6; i++)
	{	
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("_");
	}
	GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n");

	for (int y = 0; y < consY; y++)
	{
		/////////
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("|| ");


		////////////
		for (int x = 0; x < consX; x++)
		{
			////////



			///////
			GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append(
			
				*workData.getLargeGSimStrArr()->getElem(x, y)

			);
			//////
			

			//////
		}
		/////////////

		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append(" ||");

		/////////////
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n");
	}

	if (GrCConnector.getDBReference()->getGameSimDataPtr()->getCurrentFractionTurn() == _BFL_TEAM_DOWN_SIDE)
	{

		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
		for (int i = 0; i < consX + 6; i++)
		{
			
			GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("^");
		}
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n");
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\t\t\t");
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("     Down team Turn\n");

	}
	else
	{
		GrCConnector.getGrCDataRef()->getGrCConsoleOutDataPtr()->getOutputString()->append("\n\n\n");
	}

	return;

}

#define wrkd_space workData._SPACE_SIZE
//������� ��� ������ ��������� ���������� ������� � ���������� "��������" �������
int GraphicCore::coordFormula(int coord)
{
	
	return (wrkd_space + (wrkd_space + 1) * coord);

}

vecI2d GraphicCore::convertGSimCoordToLargeArrCoords(vecI2d gSimCoords)
{
	if (gSimCoords.getX() >= workData.getGSimArrSize().getX() || gSimCoords.getX() < 0 ||
		gSimCoords.getY() >= workData.getGSimArrSize().getY() || gSimCoords.getY() < 0)
	{
		return __GBO_VECTOR_GSIM_OUT_OF_RANGE_VEC;
	}

	vecI2d retVec; 

	int coordFormulaX = coordFormula(gSimCoords.getX());
	int coordFormulaY = coordFormula(gSimCoords.getY());

	retVec = vecI2d(coordFormulaX, coordFormulaY);

	return retVec;

}

//�������� "��������" ��������
#define _UP_CURSOR_STR "V"
#define _DOWN_CURSOR_STR "^"
#define _LEFT_CURSOR_STR ">"
#define _RIGHT_CURCOR_STR "<"

#define _UP_CURSOR_PREV_STR "!"
#define _DOWN_CURSOR_PREV_STR "A"
#define _LEFT_CURSOR_PREV_STR "-"
#define _RIGHT_CURCOR_PREV_STR "-"

#define _PRINT_CURSOR_MODE_PREV 1
#define _PRINT_CURSOR_MODE_CURR 2

//������� �� ������ ��������� "��������" ������� �� "��������" �������� 
void setCursorConvertedCoords(GrCMiddleWorkProcessData* workData, vecI2d vec, int printCursorMode)
{
	switch (printCursorMode)
	{
	case _PRINT_CURSOR_MODE_CURR:
	{
		workData->getLargeGSimStrArr()->setElem(_UP_CURSOR_STR, vec.getX(), vec.getY() - 1);
		workData->getLargeGSimStrArr()->setElem(_DOWN_CURSOR_STR, vec.getX(), vec.getY() + 1);
		workData->getLargeGSimStrArr()->setElem(_LEFT_CURSOR_STR, vec.getX() - 1, vec.getY());
		workData->getLargeGSimStrArr()->setElem(_RIGHT_CURCOR_STR, vec.getX() + 1, vec.getY());
		break;
	}
	case _PRINT_CURSOR_MODE_PREV:
	{
		workData->getLargeGSimStrArr()->setElem(_UP_CURSOR_PREV_STR, vec.getX(), vec.getY() - 1);
		workData->getLargeGSimStrArr()->setElem(_DOWN_CURSOR_PREV_STR, vec.getX(), vec.getY() + 1);
		workData->getLargeGSimStrArr()->setElem(_LEFT_CURSOR_PREV_STR, vec.getX() - 1, vec.getY());
		workData->getLargeGSimStrArr()->setElem(_RIGHT_CURCOR_PREV_STR, vec.getX() + 1, vec.getY());
		break;
	}

	default:
		break;
	}
}

#define _PRINT_POSSIBLE_POSITION_SQUARE_STR "o"
//������� ������� �� ����� ��������� ���� ��� ������ ��� �������� ������
void GraphicCore::showPossiblePositionInArr()
{

	std::vector<vecI2d> possiblePos;
	switch (interpretator.getGameSimData()->getCurrentFractionTurn())
	{

	case _BFL_TEAM_DOWN_SIDE:
	{
		
		possiblePos = GrCConnector.getPlayerOneData()->getPossiblePlayerPos();

		break;
	}

	case _BFL_TEAM_UP_SIDE:
	{
		possiblePos = GrCConnector.getPlayerTwoData()->getPossiblePlayerPos();
		
		break;

	}
	case _BFL_TEAM_NONE:
	{
		//throw _BFL_TEAM_ERR_NO_FRACTION_CHOSEN;
		return;
		break;
	}

	default:
	{
		return;
		break;
	}
	}
	if (possiblePos.empty())
	{
		return;
	}


	if (possiblePos[0] == _BFL_RULES_POSSIBLE_POS_NOT_FOUND_VEC)
	{
		return;
	}

	for (int i = 0; i < possiblePos.size(); i++)
	{

		workData.getLargeGSimStrArr()->setElem(_PRINT_POSSIBLE_POSITION_SQUARE_STR,
			coordFormula(possiblePos.at(i).getX()),
			coordFormula(possiblePos.at(i).getY()));

	}
	possiblePos.clear();

}
//������� ��� ������ �� ����� �������� �������� ������
void GraphicCore::GrCShowCursors()
{


	switch (interpretator.getGameSimData()->getCurrentFractionTurn())
	{

	case _BFL_TEAM_DOWN_SIDE:
	{
		vecI2d GSimPlayerOneVecCurr = GrCConnector.getPlayerOneData()->getCurrCusor()->getCursorPos();
		vecI2d GSimPlayerOneVecFrom = GrCConnector.getPlayerOneData()->getCursorFrom()->getCursorPos();

		vecI2d playerOneVecCurr = convertGSimCoordToLargeArrCoords(GSimPlayerOneVecCurr);
		vecI2d playerOneVecFrom = convertGSimCoordToLargeArrCoords(GSimPlayerOneVecFrom);

		setCursorConvertedCoords(&workData, playerOneVecFrom, _PRINT_CURSOR_MODE_PREV);
		setCursorConvertedCoords(&workData, playerOneVecCurr, _PRINT_CURSOR_MODE_CURR);

		break;
	}

	case _BFL_TEAM_UP_SIDE:
	{
		vecI2d GSimPlayerTwoVecCurr = GrCConnector.getPlayerTwoData()->getCurrCusor()->getCursorPos();
		vecI2d GSimPlayerTwoVecFrom = GrCConnector.getPlayerTwoData()->getCursorFrom()->getCursorPos();

		vecI2d playerTwoVecCurr = convertGSimCoordToLargeArrCoords(GSimPlayerTwoVecCurr);
		vecI2d playerTwoVecFrom = convertGSimCoordToLargeArrCoords(GSimPlayerTwoVecFrom);

		setCursorConvertedCoords(&workData, playerTwoVecFrom, _PRINT_CURSOR_MODE_PREV);
		setCursorConvertedCoords(&workData, playerTwoVecCurr, _PRINT_CURSOR_MODE_CURR);
		
		break;
	}
	case _BFL_TEAM_NONE:
	{
		//throw _BFL_TEAM_ERR_NO_FRACTION_CHOSEN;
	}
	default:
	{
		break;
	}
	}

}

#undef wrkd_space


