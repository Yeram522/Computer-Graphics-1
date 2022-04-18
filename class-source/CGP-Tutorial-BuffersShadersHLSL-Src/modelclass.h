////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

enum class Shape
{
	TRIANGLE,
	PENTAGON,
	HOUSE,
	CROSS,//표창
};

enum class Direction
{
	X,
	Y,
	Z,
};

struct Position
{
	float x;
	float y;
	float z;
};

// a struct to define the constant buffer
struct CBUFFER
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//Color LightColor;
	//Color AmbientColor;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType ///vertex 정보
	{
		XMFLOAT3 position;
	    XMFLOAT4 color;
	};

public:
	ModelClass(Shape shape,Position pos,Direction dir);
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	CBUFFER updateMatrix(CBUFFER);
	Shape shape;
	Position pos;
	CBUFFER cbuffer;//내가 만든거
	Direction dir;
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	
	void drawVertex(VertexType* vertices, unsigned long* indices);
	void drawTriangle(VertexType* vertices, unsigned long* indices);
	void drawPentagon(VertexType* vertices, unsigned long* indices);
	void drawHouse(VertexType* vertices, unsigned long* indices);
	void drawCross(VertexType* vertices, unsigned long* indices);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	
	//vertex buffer =  position    indexBuffer  = 정점의 순서
	int m_vertexCount, m_indexCount;
};

#endif