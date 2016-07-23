#ifndef INC_CAMERAFPSHOOTER_H_
#define INC_CAMERAFPSHOOTER_H_

#include "CameraController.h"

class CCamera;

class CFPSCameraController : public CCameraController
{
private:
	float						m_YawSpeed;
	float						m_PitchSpeed;
	float						m_Speed;
	float						m_FastSpeed;
public:
	CFPSCameraController();
	virtual ~CFPSCameraController();
	
	void Move(float Strafe, float Forward, bool Speed, float ElapsedTime);
	void SetCamera(CCamera *Camera) const;
	void AddYaw(float Radians);
	void AddPitch(float Radians);
	XMFLOAT3 GetDirection() const;
};

#endif
