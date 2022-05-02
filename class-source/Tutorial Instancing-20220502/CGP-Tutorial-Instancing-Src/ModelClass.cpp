#include "stdafx.h"
#include "TextureClass.h"
#include "modelclass.h"


ModelClass::ModelClass()
{
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, const WCHAR* textureFilename)
{
	// 정점 및 인덱스 버퍼를 초기화합니다.
	if (!InitializeBuffers(device))
	{
		return false;
	}

	// 이 모델의 텍스처를 로드합니다.
	return LoadTexture(device, textureFilename);
}


void ModelClass::Shutdown()
{
	// 모델 텍스쳐를 반환합니다.
	ReleaseTexture();

	// 버텍스 및 인덱스 버퍼를 종료합니다.
	ShutdownBuffers();
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// 그리기를 준비하기 위해 그래픽 파이프 라인에 꼭지점과 인덱스 버퍼를 놓습니다.
	RenderBuffers(deviceContext);
}


int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}


int ModelClass::GetInstanceCount()
{
	return m_instanceCount;
}


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	// 정점 배열의 정점 수를 설정합니다.
	m_vertexCount = 3;

	// 정점 배열을 만듭니다.
	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 정점 배열에 값을 설정합니다.
	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].texture = XMFLOAT2(0.5f, 0.0f);

	vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].texture = XMFLOAT2(1.0f, 1.0f);

	// 정적 정점 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 이제 정점 버퍼를 만듭니다.
	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// 이제 버텍스 버퍼가 생성되고로드 된 버텍스 배열을 해제한다.
	delete [] vertices;
	vertices = 0;

	// 배열의 인스턴스 수를 설정합니다.
	m_instanceCount = 4;

	// 인스턴스 배열을 만듭니다.
	InstanceType* instances = new InstanceType[m_instanceCount];
	if(!instances)
	{
		return false;
	}

	// 데이터로 인스턴스 배열을 로드합니다.
	instances[0].position = XMFLOAT3(-1.5f, -1.5f, 5.0f);
	instances[1].position = XMFLOAT3(-1.5f,  1.5f, 5.0f);
	instances[2].position = XMFLOAT3( 1.5f, -1.5f, 5.0f);
	instances[3].position = XMFLOAT3( 1.5f,  1.5f, 5.0f);

	// 인스턴스 버퍼의 설명을 설정합니다.
	D3D11_BUFFER_DESC instanceBufferDesc;
    instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
    instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instanceBufferDesc.CPUAccessFlags = 0;
    instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// 하위 리소스 구조에 인스턴스 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA instanceData;
    instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// 인스턴스 버퍼를 만듭니다.
	if(FAILED(device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer)))
	{
		return false;
	}

	// 인스턴스 버퍼가 생성되고로드되었으므로 인스턴스 배열을 해제합니다.
	delete [] instances;
	instances = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// 인스턴스 버퍼를 해제합니다.
	if(m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// 정점 버퍼를 해제합니다.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 버퍼 오프셋과 스트라이드를 설정합니다.
	unsigned int strides[2] = { sizeof(VertexType), sizeof(InstanceType) };
	unsigned int offsets[2] = { 0, 0 };

	// 포인터의 배열을 정점 버퍼와 인스턴스 버퍼로 설정합니다.
	ID3D11Buffer* bufferPointers[2] = { m_vertexBuffer, m_instanceBuffer };

	// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

    // 이 꼭지점 버퍼에서 렌더링되어야하는 프리미티브 유형을 설정합니다.이 경우에는 삼각형입니다.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


bool ModelClass::LoadTexture(ID3D11Device* device, const WCHAR* filename)
{
	// 텍스처 오브젝트를 생성한다.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// 텍스처 오브젝트를 초기화한다.
	return m_Texture->Initialize(device, filename);
}


void ModelClass::ReleaseTexture()
{
	// 텍스처 오브젝트를 릴리즈한다.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}