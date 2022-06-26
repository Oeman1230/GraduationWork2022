
#include <iostream>
#include "GameCore.h"
#include <string>
#include <cstdio>
#include <cstdlib>

#include "Vector2DTemplate.h"
#include "GameBaseComponents.h"

int main()
{
	//Непосредственно сам экземпляр игры
	GameCore GC_ex;
	GCStartingArgs arg; //это dummy аргументы, которые здесь не играют роли
	arg.testFlag = 1;
	GC_ex.GCstartMainFunc(arg); //запуск главного цикла игры

    system("pause");
    
	return 0;
}
