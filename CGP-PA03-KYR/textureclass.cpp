////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

TextureClass::TextureClass()
{
	
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
	m_texCount = filenames.size();
	m_textures = new ID3D11ShaderResourceView*[m_texCount];// 동적배열 크기 할당
	//texture file 순서: ambidient, diffuse, normal, specular
	for (int i = 0; i < m_texCount; i++)
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

	//texture file 순서: ambidient, diffuse, normal, specular
	for (int i = 0; i < m_texCount; i++)
	{
		m_textures[i]->Release();
		m_textures[i] = 0;
	}

	return;
}


ID3D11ShaderResourceView** TextureClass::GetTextureArray()
{
	return m_textures;
}