////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass(Shape _shape, Position _pos, Direction _dir)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	shape = _shape;
	pos = _pos;
	dir = _dir;

	switch (_shape)
	{
	case Shape::TRIANGLE:
		// Set the number of vertices in the vertex array.
		m_vertexCount = 3;

		// Set the number of indices in the index array.
		m_indexCount = 3;
		break;
	case Shape::PENTAGON:
		// Set the number of vertices in the vertex array.
		m_vertexCount = 6;

		// Set the number of indices in the index array.
		m_indexCount = 15;
		break;
	case Shape::HOUSE:
		// Set the number of vertices in the vertex array.
		m_vertexCount = 5;

		// Set the number of indices in the index array.
		m_indexCount = 9;
		break;
	case Shape::CROSS:
		// Set the number of vertices in the vertex array.
		m_vertexCount = 8;

		// Set the number of indices in the index array.
		m_indexCount = 12;
		break;
	default:
		break;
	}
	

	
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

CBUFFER ModelClass::updateMatrix(CBUFFER cb)
{
	static float Time = 0.0f; Time += 0.001f;
	switch (dir)
	{
	case Direction::Y:
		cbuffer.viewMatrix = cb.viewMatrix *XMMatrixRotationY(Time);
		break;
	case Direction::Z:
		cbuffer.viewMatrix = cb.viewMatrix * XMMatrixRotationZ(Time);
		break;
	case Direction::X:
		cbuffer.viewMatrix = cb.viewMatrix * XMMatrixRotationX(Time);
		break;
	default:
		break;
	}
	cbuffer.worldMatrix = cb.worldMatrix;
	
	cbuffer.projectionMatrix = cb.projectionMatrix;

	return cbuffer;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


//여기다가 그림그린다.
void ModelClass::drawVertex(VertexType* vertices, unsigned long* indices)
{
	switch (shape)
	{
	case Shape::TRIANGLE:
		drawTriangle(vertices,indices);
		break;
	case Shape::PENTAGON:
		drawPentagon(vertices, indices);
		break;
	case Shape::HOUSE:
		drawHouse(vertices, indices);
		break;
	case Shape::CROSS:
		drawCross(vertices, indices);
		break;
	default:
		break;
	}
}

void ModelClass::drawTriangle(VertexType* vertices, unsigned long* indices)
{
	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom left.
	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.0f + pos.x, 1.0f + pos.y, 0.0f + pos.z);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	// Create the triangle in the clockwise order (counterclockwise: back face culling).
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
}

void ModelClass::drawHouse(VertexType* vertices, unsigned long* indices)
{
	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom left.
	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(-1.0f + pos.x, 1.0f + pos.y, 0.0f + pos.z);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(1.0f + pos.x, 1.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(0.0f + pos.x, 2.5f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[4].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	// Create the triangle in the clockwise order (counterclockwise: back face culling).
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	indices[3] = 1;  // Bottom left.
	indices[4] = 3;  // Top middle.
	indices[5] = 2;  // Bottom right.

	indices[6] = 4;  // Bottom left.
	indices[7] = 3;  // Top middle.
	indices[8] = 1;  // Bottom right.
}

void ModelClass::drawCross(VertexType* vertices, unsigned long* indices)
{
	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-0.1f + pos.x, 0.3f + pos.y, 0.0f + pos.z);  // Bottom left.
	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.1f + pos.x, 0.3f + pos.y, 0.0f + pos.z);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(0.1f + pos.x, -0.3f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-0.1f + pos.x, -0.3f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(-0.3f + pos.x, 0.1f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[4].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = XMFLOAT3(0.3f + pos.x, 0.1f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[5].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[6].position = XMFLOAT3(0.3f + pos.x, -0.1f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[6].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[7].position = XMFLOAT3(-0.3f + pos.x, -0.1f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[7].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	// Create the triangle in the clockwise order (counterclockwise: back face culling).
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	indices[3] = 0;  // Bottom left.
	indices[4] = 2;  // Top middle.
	indices[5] = 3;  // Bottom right.

	indices[6] = 4;  // Bottom left.
	indices[7] = 5;  // Top middle.
	indices[8] = 6;  // Bottom right.

	indices[9] = 4;  // Bottom left.
	indices[10] = 6;  // Top middle.
	indices[11] = 7;  // Bottom right.
}

void ModelClass::drawPentagon(VertexType* vertices, unsigned long* indices)
{
	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(0.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);  // center.
	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(0.0f + pos.x, 1.0f + pos.y, 0.0f + pos.z);  // Top middle.
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(0.5f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(-0.5f + pos.x, -1.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[4].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = XMFLOAT3(-1.0f + pos.x, 0.0f + pos.y, 0.0f + pos.z);  // Bottom right.
	vertices[5].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// Load the index array with data.
	// Create the triangle in the clockwise order (counterclockwise: back face culling).
	indices[0] = 1;  // Bottom left.
	indices[1] = 2;  // center
	indices[2] = 0;  // Bottom right.

	indices[3] = 0;  // center
	indices[4] = 2;  // Bottom right.
	indices[5] = 3;  // Bottom right.

	indices[6] = 0;  // center
	indices[7] = 3;  // Bottom right.
	indices[8] = 4;  // Bottom right.

	indices[9] = 0;  // center
	indices[10] = 4;  // Bottom right.
	indices[11] = 5;  // Bottom right.

	indices[12] = 0;  // center
	indices[13] = 5;  // Bottom right.
	indices[14] = 1;  // Bottom right.
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	drawVertex(vertices, indices);

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

// This sets the vertex buffer and index buffer as active on the input assembler in the GPU. 
// Once the GPU has an active vertex buffer, it can then use the shader to render that buffer. 
// This function also defines how those buffers should be drawn such as triangles, lines, fans, 
// and etc using the IASetPrimitiveTopology DirectX function.
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}