#pragma once
#include <windows.h>
#include <vector>
using namespace std;

typedef pair<int,int> position;
typedef pair<int,int> dimension;

class CShape 
{
protected:
	position pos;

public:
	CShape(position pos):pos(pos)
	{}

	~CShape()
	{}

	virtual void Draw(HDC hdc) = 0
	{}
};