////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

TextureClass::TextureClass()
{
	m_textures[0] = 0;
	m_textures[1] = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, const WCHAR* filename, const WCHAR* filename2)
{
	HRESULT result;

	// Load texture data from a file by using DDS texture loader.
	result = CreateDDSTextureFromFile(device, filename, nullptr, &m_textures[0]);
	if (FAILED(result))
	{
		return false;
	}

	//Load the second tecture in
	result = CreateDDSTextureFromFile(device, filename2, nullptr, &m_textures[1]);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_textures[0])
	{
		m_textures[0]->Release();
		m_textures[0] = 0;
	}

	if (m_textures[1])
	{
		m_textures[1]->Release();
		m_textures[1] = 0;
	}

	return;
}


ID3D11ShaderResourceView** TextureClass::GetTextureArray()
{
	return m_textures;
}