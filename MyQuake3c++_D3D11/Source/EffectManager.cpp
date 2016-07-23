#include "EffectManager.h"
#include "VertexTypes.h"
#include "ApplicationDX.h"

CEffectParameters CEffectManager::m_Parameters;

CEffectManager::~CEffectManager()
{
	std::map<unsigned int, CEffect *>::iterator l_ItByUint;
	std::map<std::string, CEffect *>::iterator l_ItByString;

	for(std::map<unsigned int, CEffect *>::iterator it=m_EffectsByVertexType.begin(); it!=m_EffectsByVertexType.end(); ++it)
	{
		CHECKED_DELETE(it->second);
	}
	for(std::map<std::string, CEffect *>::iterator it=m_Effects.begin(); it!=m_Effects.end(); ++it)
	{
		CHECKED_DELETE(it->second);
	}
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	CEffect *l_Effect=(CEffect *)new CEffectTemplated<T>();
	l_Effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_EffectsByVertexType[T::GetVertexType()]=l_Effect;
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Name, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	CEffect *l_Effect=(CEffect *)new CEffectTemplated<T>();
	l_Effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_Effects[Name]=l_Effect;
}

CEffectManager::CEffectManager()
{
	ID3D11Device *l_Device=CApplicationDX::GetApplicationDX()->GetDevice();
	AddEffect<KG_POSITION_COLOR_VERTEX>(l_Device, "./Data/Effects/DebugRender.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<KG_POSITION_TEXTURE_VERTEX>(l_Device, "./Data/Effects/KG_POSITION_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<KG_POSITION_COLOR_TEXTURE_VERTEX>(l_Device, "./Data/Effects/KG_POSITION_COLOR_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<KG_POSITION4_COLOR_TEXTURE_VERTEX>(l_Device, "./Data/Effects/GUI.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<KG_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEX>(l_Device, "./Data/Effects/KG_POSITION_WEIGHT_INDICES_NORMAL_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<KG_POSITION_TEXTURE_VERTEX>(l_Device, "Billboard", "./Data/Effects/Billboard.fx", "VS", "vs_4_0", "PS", "ps_4_0");
}

CEffect * CEffectManager::GetEffect(const std::string &Name)
{
	std::map<std::string, CEffect *>::iterator l_It=m_Effects.find(Name);
	if(l_It!=m_Effects.end())
		return l_It->second;
	return NULL;
}

CEffect * CEffectManager::GetEffect(unsigned int VertexType)
{
	std::map<unsigned int, CEffect *>::iterator l_It=m_EffectsByVertexType.find(VertexType);
	if(l_It!=m_EffectsByVertexType.end())
		return l_It->second;
	return NULL;
}
