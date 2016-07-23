#include "ApplicationDX.h"
#include "DebugRender.h"
#include "Player.h"
#include <assert.h>
#include <math.h>
#include "defines.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "FPSCameraController.h"
#include "EffectManager.h"

CPlayer::CPlayer(void)
: m_Speed(10.0f)
, m_FastSpeed(20.0f)
, m_Position(0.0f, 1.75f, 0.0f)
, m_VerticalSpeed(0.0f)
, m_VerticalSpeedJump(8.0f)
{
	m_FPSCameraController=(CFPSCameraController *)CApplicationDX::GetApplicationDX()->GetCameraManager()->GetCameraController("player");
}

CPlayer::~CPlayer()
{
}

void CPlayer::Move(float Strafe, float Forward, bool Fast, float ElapsedTime)
{
	XMFLOAT3 l_VectorMovement;
	float l_Yaw=m_FPSCameraController->GetYaw();
	l_VectorMovement.y=0.0f;

	l_VectorMovement.x=Forward*(cos(l_Yaw))+Strafe*(cos(l_Yaw+ DEG2RAD(180.0f)*0.5f));
	l_VectorMovement.z=Forward*(sin(l_Yaw))+Strafe*(sin(l_Yaw+ DEG2RAD(180.0f)*0.5f));
	float l_Movement=(Fast ? m_FastSpeed : m_Speed);

	m_VerticalSpeed+=(-9.81f)*ElapsedTime;
	XMVECTOR l_Vector=XMLoadFloat3(&l_VectorMovement);
	l_Vector=XMVector3Normalize(l_Vector);
	l_Vector*=l_Movement*ElapsedTime;
	
	l_VectorMovement=XMFLOAT3(l_Vector.m128_f32[0], l_Vector.m128_f32[1], l_Vector.m128_f32[2]);
	l_VectorMovement.y=m_VerticalSpeed*ElapsedTime;
	
	m_Position=XMFLOAT3(m_Position.x+l_VectorMovement.x, m_Position.y+l_VectorMovement.y, m_Position.z+l_VectorMovement.z);
	if(m_Position.y<2.0f)
	{
		m_Position.y=2.0f;
		m_VerticalSpeed=0.0f;
	}
	m_FPSCameraController->SetPosition(m_Position);
}

void CPlayer::Update(float ElapsedTime)
{
	CApplicationDX *l_ApplicationDX=CApplicationDX::GetApplicationDX();
	CKeyboardInput *l_KeyboardInput=l_ApplicationDX->GetInputManager()->GetKeyboard();
	CMouseInput *l_MouseInput=l_ApplicationDX->GetInputManager()->GetMouse();

	if(!l_ApplicationDX->IsAntTweakBarActive())
	{
		m_FPSCameraController->AddYaw(l_MouseInput->GetMovementX()*ElapsedTime);
		m_FPSCameraController->AddPitch(l_MouseInput->GetMovementY()*ElapsedTime);
	}
	float l_Forward=0.0f;
	float l_Strafe=0.0f;
	bool l_MoveFast=l_KeyboardInput->IsKeyPressed(DIK_LSHIFT);	

	if(l_KeyboardInput->IsKeyPressed(DIK_W))
		l_Forward=1.0f;
	if(l_KeyboardInput->IsKeyPressed(DIK_S))
		l_Forward=-1.0f;
	if(l_KeyboardInput->IsKeyPressed(DIK_A))
		l_Strafe=1.0f;
	if(l_KeyboardInput->IsKeyPressed(DIK_D))
		l_Strafe=-1.0f;

	if(l_KeyboardInput->IsKeyPressed(DIK_SPACE) && m_VerticalSpeed==0.0f)
		Jump();
	
	Move(l_Strafe, l_Forward, l_MoveFast, ElapsedTime);
}

void CPlayer::Jump()
{
	m_VerticalSpeed=m_VerticalSpeedJump;
}
