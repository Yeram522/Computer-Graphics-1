#pragma once
#include "Cshape.h"

//Shape class를 상속
class CRectangle : public CShape
{
private:
	dimension dim;

public:
	CRectangle(position pos, dimension dim):CShape(pos), dim(dim)
	{}

	~CRectangle(){}

	void Draw(HDC hdc) //부모의 함수 재정의
	{
		Rectangle(hdc, pos.first, pos.second, dim.first, dim.second);
	}
};