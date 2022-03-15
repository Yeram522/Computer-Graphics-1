#pragma once
#include "Cshape.h"

class CCircle : public CShape
{
private:
	int rad;
public:
	CCircle(position pos, int rad) : CShape(pos), rad(rad)
	{}

	~CCircle(){}

	void Draw(HDC hdc) //�θ��� �Լ� ������
	{
		Ellipse(hdc, pos.first- rad, pos.second -rad , pos.first+rad , pos.second+rad );
	}

};