#include "CameraManager.h"
#include "ApplicationDX.h"
#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "CameraController.h"
#include "Frustum.h"
#include "InputManager.h"

CCameraManager::CCameraManager()
{
	m_Frustum=new CFrustum();
	m_CameraControllers.insert(std::pair<std::string, CCameraController *>("player", new CFPSCameraController()));
	m_CameraControllerControl="player";
	m_CameraControllerVision="player";
}

CCameraManager::~CCameraManager()
{
	for(std::map<std::string, CCameraController *>::iterator it=m_CameraControllers.begin();it!=m_CameraControllers.end(); ++it)
	{
		CHECKED_DELETE(it->second);
	}
	CHECKED_DELETE(m_Frustum);
}

void CCameraManager::AddCameraController(TCameraControllerType CameraControllerType, const std::string &Name, const XMFLOAT3 &Position, float Zoom)
{
	CCameraController *l_CameraController=NULL;
		
	switch(CameraControllerType)
	{
		case SPHERICAL_CAMERA_CONTROLLER:
			l_CameraController=new CSphericalCameraController();
			((CSphericalCameraController*)l_CameraController)->SetZoom(Zoom);
			break;
		case FPS_CAMERA_CONTROLLER:
			l_CameraController=new CFPSCameraController();
			break;
	}
	l_CameraController->SetPosition(Position);
	m_CameraControllers.insert(std::pair<std::string, CCameraController *>(Name, l_CameraController));
}

void CCameraManager::ChangeVision()
{
	std::map<std::string, CCameraController *>::iterator it=m_CameraControllers.find(m_CameraControllerControl);
	if(it!=m_CameraControllers.end())
	{
		++it;
		if(it!=m_CameraControllers.end())
		{
			m_CameraControllerVision=(*it).first;
		}
		else
		{
			m_CameraControllerVision=m_CameraControllers.begin()->first;
		}
	}
}

void CCameraManager::onStartElement(const std::string &elem, MKeyValue &atts)
{
	if(elem=="SphericalCameraController")
    {
		float l_Zoom;
		XMFLOAT3 l_Position;
		std::string l_Name=atts["name"];
		std::string l_PosX=atts["posx"];
		std::string l_PosY=atts["posy"];
		std::string l_PosZ=atts["posz"];
		std::string l_ZoomStr=atts["zoom"];
	  	  
		sscanf_s(l_PosX.c_str(),"%f",&l_Position.x);
		sscanf_s(l_PosY.c_str(),"%f",&l_Position.y);
		sscanf_s(l_PosZ.c_str(),"%f",&l_Position.z);
		sscanf_s(l_ZoomStr.c_str(),"%f",&l_Zoom);
	  
		AddCameraController(SPHERICAL_CAMERA_CONTROLLER, l_Name, l_Position, l_Zoom);
    }
	else if(elem=="FPSCameraController")
    {
		XMFLOAT3 l_Position;
		std::string l_Name=atts["name"];
		std::string l_PosX=atts["posx"];
		std::string l_PosY=atts["posy"];
		std::string l_PosZ=atts["posz"];
		std::string l_ZoomStr=atts["zoom"];
	  	  
		sscanf_s(l_PosX.c_str(),"%f",&l_Position.x);
		sscanf_s(l_PosY.c_str(),"%f",&l_Position.y);
		sscanf_s(l_PosZ.c_str(),"%f",&l_Position.z);
		
		AddCameraController(FPS_CAMERA_CONTROLLER, l_Name, l_Position);
    }
}

bool CCameraManager::SphereVisible(const XMFLOAT3 &Center, float Radius) const
{
	return m_Frustum->SphereVisible(Center, Radius);
}

bool CCameraManager::BoxVisible( const XMFLOAT3 &max, const XMFLOAT3 &min ) const
{
	return m_Frustum->BoxVisible( max, min);
}

CCameraController * CCameraManager::GetCameraController(const std::string &Name) const
{
	std::map<std::string, CCameraController *>::const_iterator it=m_CameraControllers.find(Name);
	if(it!=m_CameraControllers.end())
		return it->second;
	return NULL;
}

void CCameraManager::Update(float ElapsedTime)
{
	GetCameraController(m_CameraControllerControl)->Update(ElapsedTime);
	GetCameraController(m_CameraControllerVision)->SetCamera(&m_Camera);
	UpdateFrustumCamera();
}

void CCameraManager::UpdateFrustumCamera()
{
	const XMMATRIX &l_View=m_Camera.GetView();
	const XMMATRIX &l_Projection=m_Camera.GetProjection();
	m_Frustum->Update(l_View*l_Projection);
}

void CCameraManager::Load(const std::string &Filename)
{
	xmlParseFile(Filename);
}
