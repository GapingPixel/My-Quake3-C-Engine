#ifndef INC_CAMERACONTROLLER_H_
#define INC_CAMERACONTROLLER_H_

#include <d3dx11.h>
#include <xnamath.h>

#include "defines.h"

class CCamera;

class CCameraController
{
protected:
	XMFLOAT3 					m_Position;

	float						m_Yaw;
	float						m_Pitch;
public:
	CCameraController();
	virtual ~CCameraController();
	virtual void SetCamera(CCamera *Camera) const = 0;
	virtual void AddYaw(float Radians);
	virtual void AddPitch(float Radians);
	void SetYaw(float Yaw) {m_Yaw=Yaw;}
	float GetYaw() const {return m_Yaw;}
	void SetPitch(float Pitch) {m_Pitch=Pitch;}
	float GetPitch() const {return m_Pitch;}
	XMFLOAT3 GetUp() const;
	XMFLOAT3 GetRight() const;
	const XMFLOAT3 & GetPosition() const {return m_Position;}
	void SetPosition(const XMFLOAT3 &Position) {m_Position=Position;}
	virtual void Update(float ElapsedTime)
	{
	}
};

#endif
