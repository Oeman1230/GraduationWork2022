
#ifndef GAMEELEMENTS_H_
#define GAMEELEMENTS_H_
#include <string>

class GEobject;
/*
	GameElementsMainClass
	Содержит в себе всё связаннное и игрой, игровым процессом, игровой логикой

*/
class GameElementsMainClass
{
public:


public:



};
class GEobject
{
public:
	//object name

	void setGEOName(std::string newName) { GEObjName = newName; }
	std::string* getGEONamePtr() { return &GEObjName; }
	//object valut
	void setGEOValue(int newVal){ GEObjValue = newVal; }
	int* getGEOValuePtr() { return &GEObjValue; }
	GEobject()
	{
		setGEOName("0");
		setGEOValue(0);
	}
	~GEobject()
	{

	}
private:
	std::string GEObjName;
	int GEObjValue;

};

#endif // !GAMEELEMENTS_H_
