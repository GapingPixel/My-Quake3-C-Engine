#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include <d3dx11.h>
#include <xnamath.h>
#include "defines.h"

class CCamera
{	
private:
	XMMATRIX					m_View;
	XMMATRIX					m_Projection;
	XMFLOAT3					m_Position;
	XMFLOAT3					m_LookAt;
	XMFLOAT3					m_Up;
	float						m_FOV;
	float						m_AspectRatio;
	float						m_ZNear;
	float						m_ZFar;
public:
	CCamera();
	virtual ~CCamera();

	void SetFOV(float FOV) {m_FOV=FOV;}
	float GetFOV() const {return m_FOV;}
	void SetAspectRatio(float AspectRatio) {m_AspectRatio=AspectRatio;}
	float GetAspectRatio() const {return m_AspectRatio;}
	void SetZNear(float ZNear) {m_ZNear=ZNear;}
	float GetZNear() const {return m_ZNear;}
	void SetZFar(float ZFar) {m_ZFar=ZFar;}
	float GetZFar() const {return m_ZFar;}
	void SetPosition(const XMFLOAT3 &Position)
	{
		m_Position=Position;
	}
	const XMFLOAT3 & GetPosition() const
	{
		return m_Position;
	}
	void SetLookAt(const XMFLOAT3 &LookAt)
	{
		m_LookAt=LookAt;
	}
	const XMFLOAT3 & GetLookAt() const
	{
		return m_LookAt;
	}
	void SetUp(const XMFLOAT3 &Up)
	{
		m_Up=Up;
	}
	const XMFLOAT3 & GetUp() const
	{
		return m_Up;
	}
	const XMMATRIX & GetView() const {return m_View;}
	const XMMATRIX & GetProjection() const {return m_Projection;}
	void SetMatrixs();
};

#endif
