#ifndef INC_CAMERAMANAGER_H_
#define INC_CAMERAMANAGER_H_

#include <d3dx11.h>
#include <xnamath.h>

#include <map>
#include <string>
#include "XMLParser.h"
#include "defines.h"
#include "Camera.h"

class CFrustum;
class CCameraController;

class CCameraManager: public CXMLParser
{
private:
	std::string												m_CameraControllerControl;
	std::string												m_CameraControllerVision;
	CCamera													m_Camera;
	CFrustum 												*m_Frustum;
	std::map<std::string, CCameraController *>				m_CameraControllers;
	
	void		onStartElement		(const std::string &elem, MKeyValue &atts);
	void UpdateFrustumCamera();
public:
	CCameraManager();
	virtual ~CCameraManager();

	CCameraController * GetCameraController(const std::string &Name) const;
	void AddCameraController(TCameraControllerType CameraControllerType, const std::string &Name, const XMFLOAT3 &Position, float Zoom=0.0f);
	void ChangeVision();
	void ChangeControl() {m_CameraControllerControl=m_CameraControllerVision;}
	bool SphereVisible(const XMFLOAT3 &p, float radius) const;
	bool BoxVisible(const XMFLOAT3 &max, const XMFLOAT3 &min) const;
	void Load(const std::string &Filename);
	const CCamera & GetCamera() const {return m_Camera;}
	void Update(float ElapsedTime);
};

#endif
