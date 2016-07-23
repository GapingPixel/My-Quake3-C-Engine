#include "Camera.h"

CCamera::CCamera()
: m_FOV(DEG2RAD(60.0f))
, m_AspectRatio(1.0f)
, m_ZNear(0.1f)
, m_ZFar(100.0f)
, m_Position(5.0f, 5.0f, 0.0f)
, m_LookAt(0.0f, 0.0f, 0.0f)
, m_Up(0.0f, 1.0f, 0.0f)
{
}

CCamera::~CCamera()
{
}

void CCamera::SetMatrixs()
{
	m_View=XMMatrixLookAtLH(XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 0.0f), XMVectorSet(m_LookAt.x, m_LookAt.y, m_LookAt.z, 0.0f), XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0.0f));
	m_Projection=XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, m_ZNear, m_ZFar);
}
