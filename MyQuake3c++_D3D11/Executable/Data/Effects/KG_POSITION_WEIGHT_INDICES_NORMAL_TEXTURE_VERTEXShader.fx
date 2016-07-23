#include "globals.fxh"

Texture2D DiffuseTexture : register( t0 );
SamplerState LinearSampler : register( s0 );

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
	float4 Weight:BLENDWEIGHT;
	float4 Indices:BLENDINDICES;
	float3 Normal: NORMAL;
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
    PS_INPUT l_Output = (PS_INPUT)0;
	
	float4 l_TempPos=float4(IN.Pos.xyz, 1.0);
	
	float3 l_Position= 0;
	float3 normal= 0;
	
	float4 l_Indices=IN.Indices;
	
	l_Position=mul(m_Bones[l_Indices.x], l_TempPos) * IN.Weight.x;
	l_Position+=mul(m_Bones[l_Indices.y], l_TempPos) * IN.Weight.y;
	l_Position+=mul(m_Bones[l_Indices.z], l_TempPos) * IN.Weight.z;
	l_Position+=mul(m_Bones[l_Indices.w], l_TempPos) * IN.Weight.w;
	
	float3x3 m;
	
	m[0].xyz = m_Bones[l_Indices.x][0].xyz;
	m[1].xyz = m_Bones[l_Indices.x][1].xyz;
	m[2].xyz = m_Bones[l_Indices.x][2].xyz;
	   
	normal += mul(m, IN.Normal)* IN.Weight.x;
	
	m[0].xyz = m_Bones[l_Indices.y][0].xyz;
	m[1].xyz = m_Bones[l_Indices.y][1].xyz;
	m[2].xyz = m_Bones[l_Indices.y][2].xyz;
	   
	normal += normalize(mul(m, IN.Normal)* IN.Weight.y);		
	
	normal = normalize(normal);
	
	l_Output.Pos = mul(float4(l_Position, 1.0), m_World);
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
