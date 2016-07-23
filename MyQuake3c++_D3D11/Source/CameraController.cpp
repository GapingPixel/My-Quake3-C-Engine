#include "CameraController.h"

CCameraController::CCameraController()
: m_Yaw(0.0f)
, m_Pitch(0.0f)
{
}
CCameraController::~CCameraController()
{
}

XMFLOAT3 CCameraController::GetRight() const
{
	return XMFLOAT3(cos(m_Yaw-DEG2RAD(90.0f)), 0.0f, sin(m_Yaw-DEG2RAD(90.0f)));
}

XMFLOAT3 CCameraController::GetUp() const
{
	XMFLOAT3 l_Up(-cos(m_Yaw)*sin(m_Pitch), cos(m_Pitch), -sin(m_Yaw)*sin(m_Pitch));
	return l_Up;
}

void CCameraController::AddYaw(float Radians)
{
	m_Yaw+=Radians;
	if(m_Yaw>2*DEG2RAD(180.0f))
		m_Yaw-=2*DEG2RAD(180.0f);
	else if(m_Yaw<-2*DEG2RAD(180.0f))
		m_Yaw+=2*DEG2RAD(180.0f);
}
void CCameraController::AddPitch(float Radians)
{
	if(((m_Pitch-Radians)<(DEG2RAD(180.0f)*0.5) && (m_Pitch-Radians)>-(DEG2RAD(180.0f)*0.5)))
	{	
		m_Pitch-=Radians;
	}
}
