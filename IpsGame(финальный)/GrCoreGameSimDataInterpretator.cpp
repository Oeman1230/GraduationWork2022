#include "GrCoreGameSimDataInterpretator.h"

//������������� ��������� �������� �������������, ������������� ������� �������
void GrCoreGameSimDataInterpretator::interpretateBaseGameSimInfoToGraphicCoreInfo()
{
	//����� ����������� ���.���� � �������� �������� ���� ��� ������
	if (isNOTGrCInterprFullInitialised())
		throw GR_CORE_INTERPRET_ERR_NOT_FULL_INIT;;

	int horizontal = getGameSimData()->getArrTemplInterface()->getSizeHorizonal();
	int vertical = getGameSimData()->getArrTemplInterface()->getSizeVertical();


	

	getMiddleDataRef()->get2DArayInterface()->createNewArray(horizontal, vertical);
	

}

//typedef 


//������� �������� ������ ���� � ������ ��� ������ �� �����
void GrCoreGameSimDataInterpretator::convertGameSimDataToArr()
{
	if (isNOTGrCInterprFullInitialised())
	{
		throw GR_CORE_INTERPRET_ERR_NOT_FULL_INIT;
		return;
	}
	interpretateBaseGameSimInfoToGraphicCoreInfo();

	//std::cout << "getSize err in Interpr convert\n";
	int horizontal = getGameSimData()->getArrTemplInterface()->getSizeHorizonal();
	int vertical = getGameSimData()->getArrTemplInterface()->getSizeVertical();

	//�������� �� ������� �������� ������� ������� �������� 
	for (int y = 0; y < vertical; y++)
	{
		for (int x = 0; x < horizontal; x++)
		{
			GameBaseObject* gameSimElem;

			gameSimElem = getGameSimData()->getArrTemplInterface()->getElem(x, y);


			//���������� ���������� ������� � ������������� � "����������" ��� ������� �������
			if (_GBC_OBJECT_TYPE == *gameSimElem->getGBOTypePtr())
			{
				getMiddleDataRef()->get2DArayInterface()->setElem(INTRP_EMPTY_GAMEOBJ_, x, y);
			}
			else
			{
				
				if (gameSimElem->getGBOFreeDataPtr()->_Equal(_GBC_OBJECT_STANDART_FREE_DATA))
				{
					return;
				}

				getMiddleDataRef()->get2DArayInterface()->setElem(
					*gameSimElem->getGBOFreeDataPtr(),
					x, y);
			}

		}

	}
}

void GrCoreGameSimDataInterpretator::interpretatorInitialisation(OEDataBase* p_DataBase)
{
	if (NULL == p_DataBase)
	{
		throw GR_CORE_CONNECTOR_ERR_NO_DATA_BASE_PTR;
	}
}


