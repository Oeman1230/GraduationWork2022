



#ifndef OEDATABASE_H_
#define OEDATABASE_H_

/*
	Class OEDataBase:
	�������� ����:
	DBGrCoredata GrCData
	..............

*/

#include "OeDataBasePrototypes.h"

#include "GraphicCoreStructs.h"
#include "GameBaseComponents.h"
#include "OEDataBaseData.h"

class OEDBConnector;

#define OEDATABASE_CONNECTOR_ERR_NO_DB_PTR "OEDATABASE_CONNECTOR_ERR_NO_DATABASE_PTR"

/*
	���� ������ �� ����� ������� ����������� � ���������, 
	� ������� ���� ������������� ������������ ����� ��������
	��� ��������� �������� ��������������� ����������� ������
	
*/
class OEDataBase
{
public:
	OEDataBase()
	{
		std::cout << "Data base constr \n";
	}
	~OEDataBase(){}

	DBGameSimData* getGameSimDataPtr()
	{
		return &GameSimData;
	}

	DBGrCoreData* getGrCData()
	{ 
		return &GrCData; 
	}

	DBMenuData* getMenuData()
	{

		return &MenuData;
	}

	DBIntelligenceData* getPlayerOneData()
	{
		return GameSimData.getPlayerOneData();
	}

	DBIntelligenceData* getPlayerTwoData()
	{
		return GameSimData.getPlayerTwoData();
	}

private:
	DBGrCoreData GrCData; //������ ����.����
	DBGameSimData GameSimData; //������ ���� ���.����
	DBMenuData MenuData; //������ � ����

};

/*
	��������� - ��� ��������� ������� � ���� ������ � � �����������
	� ������� ������ ����� ���� ���� ����������, �� ��� ��� ������ ���������
	- ����� ������ ������� � ����.
	����� ������� ����� ��� ���������� ���� ������

*/
class OEDBConnector{
      
public:
       OEDataBase* getDBReference(){ return DBReference; }
       void setDBReference(OEDataBase* DataBaseReference)
       { 
		   DBReference = DataBaseReference; 
	   }
	   //OEDBConnector() {}
       OEDBConnector( OEDataBase* p_DataBase)
	   { 
		   if (NULL == p_DataBase)
		   {
			   throw OEDATABASE_CONNECTOR_ERR_NO_DB_PTR;
		   }
		   DBReference = p_DataBase; 
	   }
       
	   void directLogAppend(std::string log)
	   {
		   getDBReference()->getGrCData()->appendProcLog(log);

	   }
	   ~OEDBConnector() { DBReference = NULL; }
protected:
       OEDataBase* DBReference;

};

#endif // OEDATABASE_H_


