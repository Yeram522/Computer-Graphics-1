#include "modelclass.h"

class Square : public ModelClass
{
public:
	Square():ModelClass(4)
	{

	}

	//void drawVertex(VertexType* vertices, unsigned long* indices) 
	//{
	//	// Load the vertex array with data.
	//	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	//	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//	vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	//	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//	vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	//	vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//	// Load the index array with data.
	//	// Create the triangle in the clockwise order (counterclockwise: back face culling).
	//	indices[0] = 0;  // Bottom left.
	//	indices[1] = 1;  // Top middle.
	//	indices[2] = 2;  // Bottom right.
	//}

};