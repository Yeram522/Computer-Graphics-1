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
	ModelClass(int n);
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	
	void drawVertex(VertexType* vertices, unsigned long* indices);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	//vertex buffer =  position    indexBuffer  = 정점의 순서
	int m_vertexCount, m_indexCount;
};

#endif