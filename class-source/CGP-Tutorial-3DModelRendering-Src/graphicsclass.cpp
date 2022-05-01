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
	
	m_TextureShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

void GraphicsClass::changeFilter(D3D11_FILTER filter)
{
	m_TextureShader->changeFilter(m_D3D->GetDevice(), filter);
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


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
	m_Camera->SetPosition(0.0f, 0.0f, -15.0f);	// for cube model

	// Create the model object.
	// Initialize the model object.
	m_Model.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/UFO_Empty.obj", L"./data/UFO_color.dds"));
	m_Model.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/Asteroid.obj", L"./data/Asteroid.dds"));
	m_Model.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/AmongUs_Red.obj", L"./data/AmongUs_Purple.dds"));
	m_Model.push_back(new ModelClass(m_D3D->GetDevice(), L"./data/plane.obj", L"./data/tile.dds"));

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

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

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	for (auto& model : m_Model)
	{
		model->cbuffer = { worldMatrix, viewMatrix, projectionMatrix };
	}

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	m_Model[0]->cbuffer.worldMatrix = XMMatrixRotationY(rotation) * worldMatrix;
	m_Model[1]->cbuffer.worldMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f)*XMMatrixRotationY(rotation) * XMMatrixTranslation(5.0f,0.0f,0.0f) * worldMatrix;
	m_Model[2]->cbuffer.worldMatrix = XMMatrixScaling(2.0f, 2.0f, 2.0f) * XMMatrixRotationY(rotation) * XMMatrixTranslation(-5.0f,0.0f,0.0f) * worldMatrix;
	m_Model[3]->cbuffer.worldMatrix = XMMatrixScaling(50.0f, 150.0f, 150.0f) * XMMatrixTranslation(0.0f, -30.0f, 120.0f) * worldMatrix;
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	for (auto& model : m_Model)
	{
		model->Render(m_D3D->GetDeviceContext());

		// Render the model using the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
			model->cbuffer.worldMatrix, model->cbuffer.viewMatrix, model->cbuffer.projectionMatrix, model->GetTexture());

		if (!result)
		{
			return false;
		}
	}
	
	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}