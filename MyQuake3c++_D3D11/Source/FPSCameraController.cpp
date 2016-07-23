#include "FPSCameraController.h"
#include "Camera.h"

CFPSCameraController::CFPSCameraController()
: m_YawSpeed(100.f)
, m_PitchSpeed(60.f)
, m_Speed(5.0f)
, m_FastSpeed(10.0f)
{
	m_Position=XMFLOAT3(0.0f, 2.0f, 0.0f);
}

CFPSCameraController::~CFPSCameraController()
{	
}

void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{
	XMFLOAT3 l_AddPos;
	l_AddPos.y=0.0f;
	l_AddPos.x=Forward*(cos(m_Yaw))+Strafe*(cos(m_Yaw+DEG2RAD(180.0f)*0.5f));
	l_AddPos.z=Forward*(sin(m_Yaw))+Strafe*(sin(m_Yaw+DEG2RAD(180.0f)*0.5f));
	
	float l_ConstantSpeed=ElapsedTime*m_Speed;
	if(Speed)
		l_ConstantSpeed*=m_FastSpeed;

	XMVECTOR l_Vector=XMLoadFloat3(&l_AddPos);
	l_Vector=XMVector3Normalize(l_Vector);
	l_Vector*=l_ConstantSpeed;
	l_Vector+=XMLoadFloat3(&m_Position);
	m_Position=XMFLOAT3(l_Vector.m128_f32[0], l_Vector.m128_f32[1], l_Vector.m128_f32[2]);
}

void CFPSCameraController::AddYaw(float Radians)
{
	CCameraController::AddYaw(DEG2RAD(-Radians*m_YawSpeed));
}

void CFPSCameraController::AddPitch(float Radians)
{
	CCameraController::AddPitch(DEG2RAD(Radians*m_PitchSpeed));
}

void CFPSCameraController::SetCamera(CCamera *Camera) const
{
	XMFLOAT3 l_Direction=GetDirection();
	Camera->SetFOV(DEG2RAD(50.0f));
	Camera->SetAspectRatio(16.0f/9.0f);
	Camera->SetPosition(m_Position);
	Camera->SetLookAt(XMFLOAT3(m_Position.x+l_Direction.x, m_Position.y+l_Direction.y, m_Position.z+l_Direction.z));
	Camera->SetUp(GetUp());
	Camera->SetMatrixs();
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	XMFLOAT3 l_Direction(cos(m_Yaw)*cos(m_Pitch), sin(m_Pitch), sin(m_Yaw)*cos(m_Pitch));
	return l_Direction;
}
