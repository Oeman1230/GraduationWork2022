
#include <iostream>
#include "GameCore.h"
#include <string>
#include <cstdio>
#include <cstdlib>

#include "Vector2DTemplate.h"
#include "GameBaseComponents.h"

int main()
{
	//��������������� ��� ��������� ����
	GameCore GC_ex;
	GCStartingArgs arg; //��� dummy ���������, ������� ����� �� ������ ����
	arg.testFlag = 1;
	GC_ex.GCstartMainFunc(arg); //������ �������� ����� ����

    system("pause");
    
	return 0;
}
