////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
struct Color
{
	float red;
	float green;
	float blue;
	float alpha = 1.0f;
};



class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void chageBckColor(Color color);
	void changeFillMode(D3D11_FILL_MODE mode);
	bool changeBright(bool, HWND);
private:
	bool Render();
	Color bckColor;
private:
	D3DClass* m_D3D;
	ID3D11Buffer* pCBuffer;                // the pointer to the constant buffer
	CameraClass* m_Camera;
	vector<ModelClass*> m_Models;
	ColorShaderClass* m_ColorShader;
};

#endif