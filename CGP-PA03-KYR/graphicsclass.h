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
#include "lightshaderclass.h"
#include "lightclass.h"

using namespace DirectX;

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
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void ChangeLightShaderMode(int);
private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	vector<ModelClass*> m_Model; //¸ðµ¨Å¬·¡½º

	LightShaderClass* m_LightShader;
	LightClass *m_Light, *m_Light1, *m_Light2, *m_Light3, *m_Light4;

	XMVECTOR   m_Eye;           
	XMVECTOR   m_At;                
	XMVECTOR   m_Up;

	int m_screenWidth, m_screenHeight;
};

#endif