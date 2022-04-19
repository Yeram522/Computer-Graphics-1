////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;//0은 nullptr을 의미
	m_Camera = 0;

	

	m_ColorShader = 0;

	bckColor = { 0.0f,0.0f,0.0f,1.0f };
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
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	m_Models.push_back(new ModelClass(Shape::CROSS, { -3.0f,0.0f,0.0f },Direction::X));
	m_Models.push_back(new ModelClass(Shape::PENTAGON, { 0.0f,0.0f,0.0f }, Direction::Y));
	m_Models.push_back(new ModelClass(Shape::HOUSE, { 3.0f,0.0f,0.0f }, Direction::Z));

	for (auto& model : m_Models)
	{
		if (!model)
		{
			return false;
		}
	}
	
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	// Initialize the model object.
	for (auto& model : m_Models)
	{
		result = model->Initialize(m_D3D->GetDevice());
		model->cbuffer = { worldMatrix ,viewMatrix,projectionMatrix };
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}
	

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd,true);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool GraphicsClass::changeBright(bool ver, HWND hwnd)
{
	bool result;

	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd, ver);
	
	return result;
}

void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	for (auto& model : m_Models)
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


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::chageBckColor(Color color)
{
	bckColor = color;
}

void GraphicsClass::changeFillMode(D3D11_FILL_MODE mode)
{
	
	m_D3D->changeFillMode(mode);
}

bool GraphicsClass::Render()
{	
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(bckColor.red, bckColor.green, bckColor.blue, bckColor.alpha);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	//viewMatrix = viewMatrix * XMMatrixRotationY(Time);
	//const XMMATRIX worldMatrix2 =  * viewMatrix * projectionMatrix;
	
	m_D3D->GetDeviceContext()->VSSetConstantBuffers(0, 1, &pCBuffer);
	
	//XMMATRIX worldMatrix2 = viewMatrix  * worldMatrix * projectionMatrix;
	//*  XMMatrixRotationX(Time)
	
	for (auto& model : m_Models)
	{
		CBUFFER cb = model->cbuffer;
		model->updateMatrix({ viewMatrix,worldMatrix ,projectionMatrix});

		model->Render(m_D3D->GetDeviceContext());

		// Render the model using the color shader.
		result = m_ColorShader->Render(m_D3D->GetDeviceContext(), model->GetIndexCount(),
			model->cbuffer.worldMatrix, model->cbuffer.viewMatrix, model->cbuffer.projectionMatrix);
		if (!result)
		{
			return false;
		}
	}
	

	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}