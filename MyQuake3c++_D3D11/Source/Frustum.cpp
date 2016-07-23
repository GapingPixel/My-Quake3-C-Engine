#include "Frustum.h"

void CFrustum::Update(const XMMATRIX &ViewProjection)
{
 	m_Frustum[0][0]=ViewProjection._14-ViewProjection._11;
	m_Frustum[0][1]=ViewProjection._24-ViewProjection._21;
	m_Frustum[0][2]=ViewProjection._34-ViewProjection._31;
	m_Frustum[0][3]=ViewProjection._44-ViewProjection._41;

	float t=1.0f/sqrtf((m_Frustum[0][0]*m_Frustum[0][0])+(m_Frustum[0][1]*m_Frustum[0][1])+(m_Frustum[0][2]*m_Frustum[0][2]));
	m_Frustum[0][0]*=t;
	m_Frustum[0][1]*=t;
	m_Frustum[0][2]*=t;
	m_Frustum[0][3]*=t;

	m_Frustum[1][0]=ViewProjection._14+ViewProjection._11;
	m_Frustum[1][1]=ViewProjection._24+ViewProjection._21;
	m_Frustum[1][2]=ViewProjection._34+ViewProjection._31;
	m_Frustum[1][3]=ViewProjection._44+ViewProjection._41;

	t=1.0f/sqrtf((m_Frustum[1][0]*m_Frustum[1][0])+(m_Frustum[1][1]*m_Frustum[1][1])+(m_Frustum[1][2]*m_Frustum[1][2]));
	m_Frustum[1][0]*=t;
	m_Frustum[1][1]*=t;
	m_Frustum[1][2]*=t;
	m_Frustum[1][3]*=t;

	m_Frustum[2][0]=ViewProjection._14+ViewProjection._12;
	m_Frustum[2][1]=ViewProjection._24+ViewProjection._22;
	m_Frustum[2][2]=ViewProjection._34+ViewProjection._32;
	m_Frustum[2][3]=ViewProjection._44+ViewProjection._42;

	t=1.0f/sqrtf((m_Frustum[2][0]*m_Frustum[2][0])+(m_Frustum[2][1]*m_Frustum[2][1])+(m_Frustum[2][2]*m_Frustum[2][2]));
	m_Frustum[2][0]*=t;
	m_Frustum[2][1]*=t;
	m_Frustum[2][2]*=t;
	m_Frustum[2][3]*=t;

	m_Frustum[3][0]=ViewProjection._14 - ViewProjection._12;
	m_Frustum[3][1]=ViewProjection._24 - ViewProjection._22;
	m_Frustum[3][2]=ViewProjection._34 - ViewProjection._32;
	m_Frustum[3][3]=ViewProjection._44 - ViewProjection._42;

	t=1.0f/sqrtf((m_Frustum[3][0]*m_Frustum[3][0])+(m_Frustum[3][1]*m_Frustum[3][1])+(m_Frustum[3][2]*m_Frustum[3][2]));
	m_Frustum[3][0]*=t;
	m_Frustum[3][1]*=t;
	m_Frustum[3][2]*=t;
	m_Frustum[3][3]*=t;

	m_Frustum[4][0]=ViewProjection._14 - ViewProjection._13;
	m_Frustum[4][1]=ViewProjection._24 - ViewProjection._23;
	m_Frustum[4][2]=ViewProjection._34 - ViewProjection._33;
	m_Frustum[4][3]=ViewProjection._44 - ViewProjection._43;

	t=1.0f/sqrtf((m_Frustum[4][0]*m_Frustum[4][0])+(m_Frustum[4][1]*m_Frustum[4][1])+(m_Frustum[4][2]*m_Frustum[4][2]));
	m_Frustum[4][0]*=t;
	m_Frustum[4][1]*=t;
	m_Frustum[4][2]*=t;
	m_Frustum[4][3]*=t;

	m_Frustum[5][0]=ViewProjection._14+ViewProjection._13;
	m_Frustum[5][1]=ViewProjection._24+ViewProjection._23;
	m_Frustum[5][2]=ViewProjection._34+ViewProjection._33;
	m_Frustum[5][3]=ViewProjection._44+ViewProjection._43;

	t=1.0f/sqrtf((m_Frustum[5][0]*m_Frustum[5][0])+(m_Frustum[5][1]*m_Frustum[5][1])+(m_Frustum[5][2]*m_Frustum[5][2]));
	m_Frustum[5][0]*=t;
	m_Frustum[5][1]*=t;
	m_Frustum[5][2]*=t;
	m_Frustum[5][3]*=t;
}

bool CFrustum::SphereVisible(const XMFLOAT3 &Center, float Radius) const 
{
	for(int i=0; i<6; ++i)	
	{
		if(((m_Frustum[i][0]*Center.x)+(m_Frustum[i][1]*Center.y)+(m_Frustum[i][2]*Center.z)+(m_Frustum[i][3]))<=-Radius)
			return false;
	}
	return true;
}

bool CFrustum::BoxVisible( const XMFLOAT3 &Max, const XMFLOAT3 &Min) const 
{
	float l_Points[24];

	l_Points[0]=Max.x;
	l_Points[1]=Max.y;
	l_Points[2]=Max.z;

	l_Points[3]=Min.x;
	l_Points[4]=Max.y;
	l_Points[5]=Max.z;

	l_Points[6]=Min.x;
	l_Points[7]=Min.y;
	l_Points[8]=Max.z;

	l_Points[9]=Max.x;
	l_Points[10]=Min.y;
	l_Points[11]=Max.z;

	l_Points[12]=Min.x;
	l_Points[13]=Min.y;
	l_Points[14]=Min.z;

	l_Points[15]=Max.x;
	l_Points[16]=Min.y;
	l_Points[17]=Min.z;

	l_Points[18]=Max.x;
	l_Points[19]=Max.y;
	l_Points[20]=Min.z;

	l_Points[21]=Min.x;
	l_Points[22]=Max.y;
	l_Points[23]=Min.z;

	int l_InCount;
	for(int p=0; p<6; p++)
	{
		l_InCount=8;
		for(int i=0; i<8; i++)
		{
			if(((m_Frustum[p][0]*l_Points[3*i])+(m_Frustum[p][1]*l_Points[3*i+1])+(m_Frustum[p][2]*l_Points[3*i+2])+(m_Frustum[p][3]))<=0.0f)
				--l_InCount;
		}
		if(l_InCount==0)
			return false;
	}
	return true;
}
