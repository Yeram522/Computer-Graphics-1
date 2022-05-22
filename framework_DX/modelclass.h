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

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>

using namespace std;

struct CBUFFER
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	    XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType //1. 구조체 안에 위치 말고도 색상, 크기, 회전등 바꿀 수 있다!
	{
		XMFLOAT3 position;
	};

public:
	ModelClass(ID3D11Device* device,const WCHAR* modelFilename, const WCHAR* textureFilename);
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	//Instancing
	int GetInstanceCount();
	int GetVertexCount();
	ID3D11ShaderResourceView* GetTexture();

	bool LoadModel(const WCHAR*);
	void ReleaseModel();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

	CBUFFER cbuffer;


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_instanceCount, m_textureCount, m_normalCount, m_faceCount;
	TextureClass* m_Texture;

	InstanceType* instances;//instance position
	ModelType* m_model;
	

	const WCHAR* modelFilename;
	const WCHAR* textureFilename;
};

#endif