////////////////////////////////////////////////////////////////////////////////
// Filename: light.vs
////////////////////////////////////////////////////////////////////////////////
/////////////
// DEFINE //
/////////////
#define NUM_LIGHTS 4
//HLSL은 define문으로 설정한 값으로 배열을 만드는 것이 가능하다.

/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPosition;
	float padding;
};

cbuffer LightPositionBuffer
{
    float4 lightPosition[NUM_LIGHTS];
};
//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float3 instancePosition : TEXCOORD1; //instancing

    //Bump Texture mapping
    float3 tangent : TANGENT; // 법선
    float3 binormal : BINORMAL; //종법선_ normal과 Tangent를 외적
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;

    //Bump Texture mapping
    float3 tangent : TANGENT; // 법선
    float3 binormal : BINORMAL; //종법선_ normal과 Tangent를 외적

    //Currentposition of point Light
    float3 lightPos1 : TEXCOORD2;
    float3 lightPos2 : TEXCOORD3;
    float3 lightPos3 : TEXCOORD4;
    float3 lightPos4 : TEXCOORD5;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;
	float4 worldPosition;


	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    //인스턴스의 정보를 이용해 정점의 위치를 갱신한다.
    input.position.x += input.instancePosition.x;
    input.position.y += input.instancePosition.y;
    input.position.z += input.instancePosition.z;

    // Calculate the tangent vector against the world matrix only adn then normalize the final value.
    output.tangent = mul(input.tangent, (float3x3)worldMatrix);
    output.tangent = normalize(output.tangent);

    // Calculate the binormal vector against the world matirx only and then normalize the final value.
    output.binormal = mul(input.binormal, (float3x3)worldMatrix);
    output.binormal = normalize(output.binormal);

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
    
	// Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

    // Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
    output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	
    // Normalize the viewing direction vector.
    output.viewDirection = normalize(output.viewDirection);

    // Determine the light positions based on the position of the lights and the position of the vertex in the world.
    output.lightPos1.xyz = lightPosition[0].xyz - worldPosition.xyz;
    output.lightPos2.xyz = lightPosition[1].xyz - worldPosition.xyz;
    output.lightPos3.xyz = lightPosition[2].xyz - worldPosition.xyz;
    output.lightPos4.xyz = lightPosition[3].xyz - worldPosition.xyz;

    //Normalize the light position vectors.
    output.lightPos1 = normalize(output.lightPos1);
    output.lightPos2 = normalize(output.lightPos2);
    output.lightPos3 = normalize(output.lightPos3);
    output.lightPos4 = normalize(output.lightPos4);

    return output;
}