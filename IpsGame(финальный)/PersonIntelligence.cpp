#include "PersonIntelligence.h"
#include "GameBaseComponents.h"
#include "GameSimStructs.h"

#define brk break
void PersonIntelligence::intelligenceInit()
{
	int x = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeHorizonal();
	int y = intelCon.getGSimDataRef()->getArrTemplInterface()->getSizeVertical();

	if (x <= 0 || y <= 0)
	{
		throw "NO_WALUES";
	}


	getCursorFrom()->setTopLeftLim(vecI2d(0, 0));
	getCursorFrom()->setBotRightLim(vecI2d(x, y));
	getCursorFrom()->setCursor(x / 2, y / 2);

	getCursorTo()->setTopLeftLim(vecI2d(0, 0));
	getCursorTo()->setBotRightLim(vecI2d(x, y));
	getCursorTo()->setCursor(x / 2, y / 2);


}

//�������� ��� ������� enter
void PersonIntelligence::menuComEnterFromCursorAction()
{
	//���� ������ �� ���� �������
	if (isSquareInMyTeam(getCursorFrom()->getCursorPos().getX(),
		getCursorFrom()->getCursorPos().getY()
	))
	{
		GameBaseObject curObject;
		curObject = *intelCon.getGSimDataRef()->getArrTemplInterface()->getElem(
			getCursorFrom()->getCursorPos().getX(),
			getCursorFrom()->getCursorPos().getY()
		);

		if (!curObject.getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE)) //���� �� ������ ������
		{
			std::vector<vecI2d> possiblePosArr;
			intelCon.getIntelligenceDataRef()->clearPossiblePos(); //������� ���������� ��������� ����
			possiblePosArr = getRules()->showAllPosiblePositions(getCursorFrom()->getCursorPos()); //���������� ��������� ����
			intelCon.getIntelligenceDataRef()->setPossiblePlayerPos(possiblePosArr); //���������� � �� ���������� � ��������� �����
		}

		intelCon.getIntelligenceDataRef()->swapCursor(); //������ ������ 
		intelCon.getIntelligenceDataRef()->getCursorTo()->setCursor(
			intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos()
		); //������� ��������� ������� �������� ����� � ��������� ������� ����������� �����

	}

}

//�������� ��� ������ �������� ��������, ���� � ���� ��������� �����
void PersonIntelligence::menuCommandReset()
{
	if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _TO_CURSOR) //���� ������ ������ �������� �����
	{
		intelCon.getIntelligenceDataRef()->getCurrCusor()->setCursor
		(
			intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos()
		); //���������� ������ �������� �����, � �����, ������ �� ������ ��������� �������� �����
		intelCon.getIntelligenceDataRef()->swapCursor(); //������ ������ �������� ����� �� ������ ��������� �����
	}
	intelCon.getIntelligenceDataRef()->clearPossiblePos(); //������� ��� ��������� �������� ��� ������

}
//������� ��������� �������� ��� ������� �� enter 
void PersonIntelligence::menuCommandEnter()
{

	if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _FROM_CURSOR) //���� ������ ������ ��������� �����
	{

		menuComEnterFromCursorAction(); //��������� �������� ��� ������� � ������ ���

		return;
	}
	else if (intelCon.getIntelligenceDataRef()->getCurrCursorNum() == _TO_CURSOR //���� ������� ������ - ��� �������� �����
		&& getElemByCursor(getCurrCursor())->getGBOTypePtr()->_Equal(_GBC_OBJECT_TYPE))
	{
		
		if (intelCon.getIntelligenceDataRef()->getCursorFrom()->getCursorPos() //���� ��������� ���� �������� ���������
			== intelCon.getIntelligenceDataRef()->getCursorTo()->getCursorPos())
		{
			if (getRules()->whatFractionSurrounds(getCurrCursor()->getCursorPos()) == playerFraction) 
				//��������� �������� �� ��� ������� ������
			{
				intelCon.directLogAppend("_BFL_INTELLIGENCE_CREATE_CQUARE"); 

				setAction(_BFL_INTELLIGENCE_CREATE_CQUARE);//����� �������� �������� ������ 
				intelCon.getIntelligenceDataRef()->swapCursor(); //������ ������
				return;
			}
			menuCommandReset(); //���� �� ��� �������, �� ���������� ���
			return;

		}

		//���� ��� ������� �� ��������� �� ����� �����

		std::vector<vecI2d> possibleTurns = intelCon.getIntelligenceDataRef()->getPossiblePlayerPos();

		std::vector<vecI2d>::iterator iter = possibleTurns.begin();

		
		while (iter != possibleTurns.end())
		{
			if ((*iter) == intelCon.getIntelligenceDataRef()->getCursorTo()->getCursorPos())
			{
				std::cout << "ff";
				setAction(_BFL_INTELLIGENCE_MOVE_CELL_CUSTOM); //��� ������� �� �����������
				intelCon.getIntelligenceDataRef()->swapCursor(); //������ �������
				intelCon.directLogAppend("_BFL_INTELLIGENCE_MOVE_CELL_CUSTOM");
				intelCon.getIntelligenceDataRef()->clearPossiblePos(); //������� ��������� ����
			}
			++iter;
		}


		return;
	}
	menuCommandReset(); //���� �� ���� ������� �� �������, �� ���������� ���
	setAction(_BFL_INTELLIGENCE_RESET);
}


void PersonIntelligence::chooseAction()
{
	switch (intelCon.getGSimDataRef()->getGameSimMenuMode())
	{
	case _GAMESIM_MODE_MOVE_CELL_UP:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsUP();

		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_DOWN:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsDOWN();
		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_LEFT:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsLEFT();
		brk;
	}
	case _GAMESIM_MODE_MOVE_CELL_RIGHT:
	{
		setAction(_BFL_INTELLIGENCE_CURSOR_MOVE_ACTION);
		intelCon.getIntelligenceDataRef()->getCurrCusor()->crsRIGHT();
		brk;
	}
	case _GAMESIM_MODE_CELL_ENTER:
	{
		menuCommandEnter();
		brk;
	}
	case _GAMESIM_MODE_CELL_RESET:
	{
		menuCommandReset();
		setAction(_BFL_INTELLIGENCE_RESET);
		brk;
	}

	default:
		break;
	}
}

#undef brk
