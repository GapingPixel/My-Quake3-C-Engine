#include "globals.fxh"

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

VS_OUTPUT VS( float4 Pos : POSITION, float4 Color: COLOR)
{
	VS_OUTPUT l_Output = (VS_OUTPUT)0;
	float4 l_Pos=float4(Pos.xyz*m_DebugRenderScale, 1.0);
	l_Output.Pos=mul(l_Pos, m_World);
	l_Output.Pos=mul(l_Output.Pos, m_View);
	l_Output.Pos=mul(l_Output.Pos, m_Projection);
	l_Output.Color=Color*m_BaseColor;
	return l_Output;
}

float4 PS(VS_OUTPUT IN) : SV_Target
{
	return IN.Color;
}
