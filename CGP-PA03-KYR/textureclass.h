////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, vector<const  WCHAR*> filenames);
	bool Initialize(ID3D11Device*, const  WCHAR* filenames);

	void Shutdown();

	ID3D11ShaderResourceView** GetTextureArray();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_textures[4];
};

#endif