#define MAXBONES 29

cbuffer ConstantBuffer : register( b0 )
{
	matrix m_World;
	matrix m_View;
	matrix m_Projection;
	float4 m_BaseColor;
	matrix m_Bones[MAXBONES];
	float4 m_CameraRightVector;
	float4 m_CameraUpVector;
	float4 m_BillboardPosition;
	float4 m_BillboardSize;
	float m_DebugRenderScale;
}
