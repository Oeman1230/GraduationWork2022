
#include "Player.h"
#include "GameSimStructs.h"
#include "ArtificialIntelligence.h"

#define brk break

// ������� ������� ������� ��� � ������. ����� ���������� �������� ������� 
bool Player::makeTurn()
{
	//�������� ��������
	getMind()->chooseAction(); 
	bool isSuccess = false;;
	int action = getMind()->giveAction(); //����� ��������
	switch (action) //�������� �� ������ ��������� ��������
	{
	case _BFL_INTELLIGENCE_MOVE_CELL_CUSTOM:
	{
		//�������� ������ �� ������� ������� ������� �� ������. �������� ������ ����� ���������� � ����� �����
		isSuccess = rules->moveCell(
			getFraction(),
			getMind()->getCursorFrom()->getCursorPos(), getMind()->getCursorTo()->getCursorPos()
		);

		getMind()->getCursorFrom()->getCursorPtr()->setVectorI2D(
			getMind()->getCursorTo()->getCursorPos()
		);
		//��������� ���������� ����������� ������
		if (true == isSuccess)
		{
			return true;
		}
		else
		{
			return false;
		}

		brk;
	}
	//������� �� �������� ����� ������
	case _BFL_INTELLIGENCE_CREATE_CQUARE:
	{
		isSuccess = rules->createSquareByPressintEnter();
		//��������� ���������� ��������
		if (true == isSuccess)
		{
			return true;
		}
		else
		{
			return false;
		}
		brk;
	}
	//������� ������ ��������
	case _BFL_INTELLIGENCE_RESET:
	{
		return false;
		brk;
	}
	case _BFL_INTELLIGENCE_CURSOR_MOVE_ACTION:
	{
		brk;
	}
	case _BFL_INTELLIGENCE_NO_ACTION:
	{
		brk;
	}
	case _BFL_INTELLIGENCE_END_OF_TURN:
	{
		return true;
	}
	default:
		break;
	}
	return false;
}

#undef brk
//������������� ��������� �������� ������
void Player::playerInit(int intelligenceMode)
{

	switch (intelligenceMode)
	{
	case _PLAYER_INTELLIGENCE_MODE_PERSON_MIND:
	{
		//����� ������ - ��������
		setMind(
			new PersonIntelligence(rules->getGSimCon()->getDBReference(),
				intelDataRef,
				playerFraction,
				getBFLRules())
		);

		getMind()->intelligenceInit();
		break;
	}
	case _PLAYER_INTELLIGENCE_MODE_COMPUTER_MIND:
	{
		//����� ������ - ����������
		setMind(
			new ArtificialIntelligence(rules->getGSimCon()->getDBReference(),
				intelDataRef,
				playerFraction,
				getBFLRules())
		);

		getMind()->intelligenceInit();
		break;
	}
	default:
		throw _PLAYER_INIT_ERR_INTELLIGENCE_MODE_UNDEF;

		break;
	}

}

