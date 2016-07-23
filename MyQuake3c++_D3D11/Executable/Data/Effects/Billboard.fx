#include "globals.fxh"

Texture2D DiffuseTexture : register( t0 );
SamplerState LinearSampler : register( s0 );

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT IN )
{
	float3 l_RightCameraVector=m_CameraRightVector;
	float3 l_UpCameraVector=m_CameraUpVector;
    PS_INPUT l_Output = (PS_INPUT)0;
	l_Output.Pos = float4(m_BillboardPosition.xyz+IN.Pos.x*l_RightCameraVector*m_BillboardSize.x+IN.Pos.y*l_UpCameraVector*m_BillboardSize.y, 1.0);
	l_Output.Pos = mul(l_Output.Pos, m_View);
    l_Output.Pos = mul(l_Output.Pos, m_Projection);
    l_Output.UV = IN.UV;
    
    return l_Output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT IN) : SV_Target
{
	return DiffuseTexture.Sample(LinearSampler, IN.UV);
}
