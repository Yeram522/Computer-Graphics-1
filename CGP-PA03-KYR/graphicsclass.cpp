////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	for (auto& model : m_Model)
	{
		model = 0;
	}
	m_LightShader = 0;
	m_Light = 0;

	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;


	m_Eye = XMVectorSet(0.0f, 5.0f, -30.0f, 1.0f);
	m_At = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair
		
	// Create the model object.
	// Initialize the model object.


	//atlas
	m_Model.push_back(new ModelClass({ {XMFLOAT3(0.0f, -0.28f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f)}, }, m_D3D->GetDevice(), L"./data/atlas.obj", { L"./data/Altar_diffuse.dds", L"./data/Altar_ao.dds",L"./data/Altar_normal.dds",L"./data/altar_specular.dds" }));


	//mystic_rock
	m_Model.push_back(new ModelClass({ {XMFLOAT3(0.5f, 2.0f, 9.5f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f)}, }, m_D3D->GetDevice(), L"./data/MysticRock.obj", { L"./data/MysticRock_BaseColor.dds", L"./data/MysticRock_Height.dds",L"./data/MysticRock_Normal.dds",L"./data/MysticRock_Emissive.dds" }));

	//flag
	m_Model.push_back(new ModelClass({ {XMFLOAT3(-1.6f, -0.25f, -0.55f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f)}, }, m_D3D->GetDevice(), L"./data/flag.obj", { L"./data/flag_diffuse.dds",0,L"./data/flag_normal.dds",L"./data/flag_specular.dds" }));

	//platform
	m_Model.push_back(new ModelClass({ {XMFLOAT3(0.0f, -0.3f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f)}, }, m_D3D->GetDevice(), L"./data/platform.obj", { L"./data/Platform_diffuse.dds", L"./data/Platform_ao.dds" ,L"./data/Platform_normal.dds",L"./data/Platform_specular.dds" }));

	//entrance
	m_Model.push_back(new ModelClass({ {XMFLOAT3(0.0f, -0.3f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f)}, }, m_D3D->GetDevice(), L"./data/entrance.obj", { L"./data/entrance_diffuse.dds", L"./data/entrance_ao.dds" , L"./data/entrance_normal.dds",L"./data/entrance_specular.dds" }));

	//arches
	m_Model.push_back(new ModelClass({ {XMFLOAT3(0.0f, -0.3f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(5.0f, 5.0f, 5.0f)}, }, m_D3D->GetDevice(), L"./data/arches.obj", { L"./data/arches_diffuse.dds", L"./data/arches_ao.dds",L"./data/arches_normal.dds",L"./data/arches_specular.dds" }));

	//tree
	m_Model.push_back(new ModelClass({ {XMFLOAT3(-10.8f, 1.2f, 11.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(3.0f,3.0f, 3.0f)}, }, m_D3D->GetDevice(), L"./data/tree.obj", { L"./data/tree_diffuse.dds", L"./data/tree_ao.dds",L"./data/tree_normal.dds",L"./data/tree_specular.dds" }));

	//plane
	m_Model.push_back(new ModelClass({ { XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(100.0f, 100.0f, 100.0f) } }, m_D3D->GetDevice(), L"./data/plane.obj", { L"./data/Ground_Albedo.dds", L"./data/block.dds", 0 ,L"./data/Platform_specular.dds" }));
	

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(0.6f, 0.6f, 0.6f, 1.0f);
	//m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(0.5f, -1.0f, 0.5f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	//첫번째 조명->하양 큰 spotLight
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}
	m_Light1->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light1->SetPosition(0.0f, 2.0f, 10.0f);

	//두번째 조명-> 빨강
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}
	m_Light2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetPosition(0.0f, 2.0f, -10.0);

	//세번째 조명-> 파랑
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}
	m_Light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_Light3->SetPosition(0.0f, 3.0f, 0.0f);

	//네번째 조명
	m_Light4 = new LightClass;
	if (!m_Light4)
	{
		return false;
	}
	m_Light4->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetPosition(0.0f, 2.0f, 10.0f);
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	for (auto& model : m_Model)
	{
		if (model)
		{
			model->Shutdown();
			delete model;
			model = 0;
		}
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	bool isClip = true;
	static float rotation = 0.1f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	DWORD dwCurTime = GetTickCount();
	static DWORD dwOldTime = GetTickCount();
	DWORD m_dwElapsedTime = dwCurTime - dwOldTime;
	dwOldTime = dwCurTime;

	float rotSpeed = 0.08f;
	float moveSpeed = 0.02f;

	if (GetAsyncKeyState(0x57))
	{
		XMVECTOR Direction;
		Direction = XMVector3Normalize(m_At - m_Eye);
		m_Eye += m_dwElapsedTime * Direction * moveSpeed;
		m_At += m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x53))
	{
		XMVECTOR Direction;
		Direction = XMVector3Normalize(m_At - m_Eye);
		m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
		m_At -= m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x41))
	{
		XMVECTOR UpNormal, ForwardNormal, Direction;
		UpNormal = XMVector3Normalize(m_Up);
		ForwardNormal = XMVector3Normalize(m_At - m_Eye);
		Direction = XMVector3Cross(ForwardNormal, UpNormal);
		Direction = XMVector3Normalize(Direction);
		m_Eye += m_dwElapsedTime * Direction * moveSpeed;
		m_At += m_dwElapsedTime * Direction * moveSpeed;
	}

	if (GetAsyncKeyState(0x44))
	{
		XMVECTOR UpNormal, ForwardNormal, Direction;
		UpNormal = XMVector3Normalize(m_Up);
		ForwardNormal = XMVector3Normalize(m_At - m_Eye);
		Direction = XMVector3Cross(ForwardNormal, UpNormal);
		Direction = XMVector3Normalize(Direction);
		m_Eye -= m_dwElapsedTime * Direction * moveSpeed;
		m_At -= m_dwElapsedTime * Direction * moveSpeed;
	}

	POINT curPt;
	GetCursorPos(&curPt);
	DWORD _CurTime = GetTickCount();
	static DWORD _OldTime = GetTickCount();
	if (_CurTime - _OldTime > 500.f)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			if (isClip)
				isClip = false;
			else
				isClip = true;
			_OldTime = _CurTime;
		}
	}
	if (isClip) {
		SetCursorPos(m_screenWidth / 2, m_screenHeight / 2);
		if (curPt.y < m_screenHeight / 2)
		{
			XMVECTOR UpNormal;
			UpNormal = XMVector3Normalize(m_Up);
			m_At += m_dwElapsedTime * UpNormal * rotSpeed;
		}

		if (curPt.y > m_screenHeight / 2)
		{
			XMVECTOR UpNormal;
			UpNormal = XMVector3Normalize(m_Up);
			m_At -= m_dwElapsedTime * UpNormal * rotSpeed;
		}

		if (curPt.x < m_screenWidth / 2)
		{
			XMVECTOR UpNormal, ForwardNormal, Left;
			UpNormal = XMVector3Normalize(m_Up);
			ForwardNormal = XMVector3Normalize(m_At - m_Eye);
			Left = XMVector3Cross(ForwardNormal, UpNormal);
			Left = XMVector3Normalize(Left);
			m_At += m_dwElapsedTime * Left * rotSpeed;
		}

		if (curPt.x > m_screenWidth / 2)
		{
			XMVECTOR UpNormal, ForwardNormal, Right;
			UpNormal = XMVector3Normalize(m_Up);
			ForwardNormal = XMVector3Normalize(m_At - m_Eye);
			Right = XMVector3Cross(ForwardNormal, UpNormal);
			Right = XMVector3Normalize(Right);
			m_At -= m_dwElapsedTime * Right * rotSpeed;
		}
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}
	return true;
}

void GraphicsClass::ChangeLightShaderMode(int mode)
{
	switch (mode)
	{
	case 1:
		if (m_LightShader->m_lightmode.x == 1.0f)
		{
			m_LightShader->m_lightmode.x = 0.0f;
		}
		else
		{
			m_LightShader->m_lightmode.x = 1.0f;
		}
		break;
	case 2:
		if (m_LightShader->m_lightmode.y == 1.0f)
		{
			m_LightShader->m_lightmode.y = 0.0f;
		}
		else
		{
			m_LightShader->m_lightmode.y = 1.0f;
		}
		break;
	case 3:
		if (m_LightShader->m_lightmode.z == 1.0f)
		{
			m_LightShader->m_lightmode.z = 0.0f;
		}
		else
		{
			m_LightShader->m_lightmode.z = 1.0f;
		}
		break;
	default:
		break;
	}
}
bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;	
	XMFLOAT4 diffuseColors[4];
	XMFLOAT4 lightPositions[4];
	bool result;

	// Create the diffuse color array from the four light colors.
	diffuseColors[0] = m_Light1->GetDiffuseColor();
	diffuseColors[1] = m_Light2->GetDiffuseColor();
	diffuseColors[2] = m_Light3->GetDiffuseColor();
	diffuseColors[3] = m_Light4->GetDiffuseColor();

	// Create the light position array from the four light positions.
	lightPositions[0] = m_Light1->GetPosition();
	lightPositions[1] = m_Light2->GetPosition();
	lightPositions[2] = m_Light3->GetPosition();
	lightPositions[3] = m_Light4->GetPosition();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.925f, 0.694f, 0.513f, 1.0f);
	//m_D3D->BeginScene(1.0f, 1.0f, 1.0f,1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	viewMatrix *= XMMatrixTranslation(0.0f, 0.0f, 10.0f) * XMMatrixLookAtLH(m_Eye, m_At, m_Up);
	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix *= XMMatrixScaling(12.0f, 12.0f,12.0f);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (auto& model : m_Model)
	{
		XMMATRIX t_worldMatrix = worldMatrix;
		model->Render(m_D3D->GetDeviceContext());
		t_worldMatrix *=
			XMMatrixScaling(model->m_instancedes[0].scale.x, model->m_instancedes[0].scale.y, model->m_instancedes[0].scale.z);
		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), model->GetVertexCount(), model->GetInstanceCount(),
			t_worldMatrix, viewMatrix, projectionMatrix, model->GetTextureArray(),m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), diffuseColors, lightPositions);

		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}