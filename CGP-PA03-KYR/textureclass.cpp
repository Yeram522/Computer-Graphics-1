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


bool TextureClass::Initialize(ID3D11Device* device,  vector<const WCHAR*> filenames)
{
	HRESULT result;

	//texture file ¼ø¼­: ambidient, diffuse, normal, specular
	for (int i = 0; i < filenames.size(); i++)
	{
		result = CreateDDSTextureFromFile(device, filenames[i], nullptr, &m_textures[i]);
		if (FAILED(result))
		{
			return false;
		}
	}
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