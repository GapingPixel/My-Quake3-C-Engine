#pragma once

#ifndef INC_FRUSTUM_H_
#define INC_FRUSTUM_H_

#include <d3dx11.h>
#include <xnamath.h>

class CFrustum 
{
private:
	float m_Proj[16];
	float m_Modl[16];
	float m_Clip[16];
	float m_Frustum[6][4];
public:
	void Update(const XMMATRIX &ViewProj);
	bool SphereVisible(const XMFLOAT3 &Center, float Radius) const;
	bool BoxVisible(const XMFLOAT3 &Max, const XMFLOAT3 &Min) const;
};

#endif
