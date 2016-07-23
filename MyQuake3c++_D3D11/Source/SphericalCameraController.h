#ifndef INC_SPHERICALCAMERA_H_
#define INC_SPHERICALCAMERA_H_

#include "CameraController.h"

class CSphericalCameraController : public CCameraController
{
private:
	float						m_Zoom;
	float						m_ZoomSpeed;
public:
	CSphericalCameraController();
	virtual ~CSphericalCameraController();

	void AddZoom(float Zoom) {m_Zoom+=Zoom;}
	void SetZoom(float Zoom) {m_Zoom=Zoom;}
	
	void SetCamera(CCamera *Camera) const;
	XMFLOAT3 GetDirection() const;
	void Update(float ElapsedTime);
};

#endif
