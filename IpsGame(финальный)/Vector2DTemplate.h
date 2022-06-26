


#ifndef VECTOR2DTEMPLATE_H_
#define VECTOR2DTEMPLATE_H_

#define _DYNAMIC_2D_ARRAY_TEMPLATE_TYPE "_DYNAMIC_2D_ARRAY_TEMPLATE_TYPE"
#include <vector>
#include <string>


template<class T>
class DynamicIntArray2DTemplated
{
private:
	int sizeHorizonal{ 0 };
	int sizeVertical{ 0 };

protected:

	std::vector<std::vector<T>> dynamicVectorArray;

	std::string type;




public:

	DynamicIntArray2DTemplated()
	{
		setType(_DYNAMIC_2D_ARRAY_TEMPLATE_TYPE);
		DynamicIntArray2DTemplated::sizeHorizonal = 0;
		DynamicIntArray2DTemplated::sizeVertical = 0;
	}

	void setType(std::string newType) { type = newType; }

	void setHorizontal(int newHorizontal)
	{
		sizeHorizonal = newHorizontal;
	}
	void setVertical(int newVertical)
	{
		sizeVertical = newVertical;
	}

	int getSizeHorizonal() { return sizeHorizonal; }
	int getSizeVertical() { return sizeVertical; }

	long int getSurfaceArea() { return (sizeHorizonal + 1) * (sizeVertical + 1); }

	std::string getType() { return type; };

	bool isCoordInLimits(int x, int y)
	{
		if (x < 0 || x >= getSizeHorizonal())
		{
			return false;
		}
		if (y < 0 || y >= getSizeVertical())
		{
			return false;
		}
		return true;
	}

	std::vector<std::vector<T>>* getArray() { return &dynamicVectorArray; }

	bool setElem(T newElem, int X, int Y)
	{
		if (getSizeHorizonal() < X || getSizeVertical() < Y || X < 0 || Y < 0)
		{
			return false;
		}
		dynamicVectorArray[Y][X] = newElem;

		return true;
	}

	T* getElem(int X, int Y)
	{
		T* elem;
		elem = &dynamicVectorArray.at(Y).at(X);
		return elem;
	}

	std::vector<std::vector<T>>* createNewArray(int newHorizontal, int newVertical)
	{
		if (dynamicVectorArray.size() != NULL)
		{
			deleteArr();
		}

		T tempElem;

		for (int y = 0; y < newVertical; y++)
		{

			std::vector<T> tempVec;

			for (int x = 0; x < newHorizontal; x++)
			{
				tempVec.push_back(tempElem);
			}

			dynamicVectorArray.push_back(tempVec);
		}

		DynamicIntArray2DTemplated::setHorizontal(newHorizontal);
		DynamicIntArray2DTemplated::setVertical(newVertical);

		return &dynamicVectorArray;
	}

	void fillArrayBy(T elem)
	{
		if (NULL == getArray())
			return;
		for (int y = 0; y < sizeVertical; y++)
		{
			for (int x = 0; x < sizeHorizonal; x++)
			{
				dynamicVectorArray[y][x] = elem;

			}
		}

	}

	void fillArrayBy()
	{
		T newElem = T();
		fillArrayBy(newElem);
	}

	void deleteArr()
	{
		int tempX = sizeHorizonal;
		int tempY = sizeVertical;

		if (NULL == getArray())
			return;
		for (int y = 0; y < sizeVertical; y++)
		{
			dynamicVectorArray.at(y).clear();
		}

		dynamicVectorArray.clear();

		DynamicIntArray2DTemplated::setHorizontal(0);
		DynamicIntArray2DTemplated::setVertical(0);

	}

	void recreateArray()
	{
		int tempX = sizeHorizonal;
		int tempY = sizeVertical;

		if (NULL == getArray())
			return;
		for (int y = 0; y < sizeVertical; y++)
		{
			dynamicVectorArray.at(y).clear();
		}

		createNewArray(tempX, tempY);
		fillArrayBy();

	}

	bool deleteElem(int X, int Y)
	{
		if (NULL == getElem(X, Y))
		{
			return false;
		}
		else
		{
			delete dynamicVectorArray[Y][X];
		}
		dynamicVectorArray[Y][X] = NULL;
		return true;

	}
};




#endif // !VECTOR2DTEMPLATE_H_
