#include <math.h>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "ApplicationDX.h"
#include "InputManager.h"
#include "MouseInput.h"

CSphericalCameraController::CSphericalCameraController() 
: m_Zoom(50.f)
, m_ZoomSpeed(2.f)
{
}

CSphericalCameraController::~CSphericalCameraController()
{	
}

XMFLOAT3 CSphericalCameraController::GetDirection() const
{
	return XMFLOAT3(m_Zoom*cos(m_Yaw)*cos(m_Pitch), m_Zoom*sin(m_Pitch), m_Zoom*sin(m_Yaw)*cos(m_Pitch));
}

void CSphericalCameraController::SetCamera(CCamera *Camera) const
{
	XMFLOAT3 l_Direction=GetDirection();
	Camera->SetFOV(DEG2RAD(50.0f));
	Camera->SetAspectRatio(16.0f/9.0f);
	Camera->SetLookAt(m_Position);
	Camera->SetPosition(XMFLOAT3(m_Position.x-l_Direction.x, m_Position.y-l_Direction.y, m_Position.z-l_Direction.z));
	Camera->SetUp(GetUp());
	Camera->SetMatrixs();
}

void CSphericalCameraController::Update(float ElapsedTime)
{
	CMouseInput *l_MouseInput=CApplicationDX::GetApplicationDX()->GetInputManager()->GetMouse();
	AddYaw(l_MouseInput->GetMovementX()*ElapsedTime*30.0f);
	AddPitch(l_MouseInput->GetMovementY()*ElapsedTime*30.0f);
	AddZoom(-l_MouseInput->GetMovementZ()*2.0f*ElapsedTime);
}
