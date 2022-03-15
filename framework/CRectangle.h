#pragma once
#include "Cshape.h"

//Shape class�� ���
class CRectangle : public CShape
{
private:
	dimension dim;

public:
	CRectangle(position pos, dimension dim):CShape(pos), dim(dim)
	{}

	~CRectangle(){}

	void Draw(HDC hdc) //�θ��� �Լ� ������
	{
		Rectangle(hdc, pos.first, pos.second, dim.first, dim.second);
	}
};