#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#define MAXBONES 29

#include <D3DX11.h>
#include <xnamath.h>

#include <map>
#include "defines.h"

class CEffectParameters
{
public:
	XMMATRIX				m_World;
	XMMATRIX				m_View;
	XMMATRIX				m_Projection;
	XMFLOAT4				m_BaseColor;
	XMMATRIX				m_Bones[MAXBONES];
	XMFLOAT4				m_CameraRightVector;
	XMFLOAT4				m_CameraUpVector;
	XMFLOAT4				m_BillboardPosition;
	XMFLOAT4				m_BillboardSize;
	float					m_DebugRenderScale;
};

class CEffect
{
public:
	virtual ~CEffect()
	{
	}
	virtual bool Reload(ID3D11Device *Device) = 0;
	virtual bool Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS) = 0;
	virtual ID3D11VertexShader * GetVertexShader() = 0;
	virtual ID3D11PixelShader * GetPixelShader() = 0;
	virtual ID3D11InputLayout * GetVertexLayout() = 0;
	virtual ID3D11Buffer * GetConstantBuffer() = 0;
};

template <class T>
class CEffectTemplated : CEffect
{
private:
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	ID3D11InputLayout *m_VertexLayout;
	ID3D11Buffer *m_ConstantBuffer;
	std::string m_Filename;
	std::string m_PointEntryVS;
	std::string m_ShaderModelVS;
	std::string m_PointEntryPS;
	std::string m_ShaderModelPS;

	bool LoadShader(const std::string &Filename, const std::string &EntryPoint, const std::string &ShaderModel, ID3DBlob **BlobOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile( Filename.c_str(), NULL, NULL, EntryPoint.c_str(), ShaderModel.c_str(), 
			dwShaderFlags, 0, NULL, BlobOut, &pErrorBlob, NULL );
		if( FAILED(hr) )
		{
			if( pErrorBlob != NULL )
				OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
			if( pErrorBlob ) 
				pErrorBlob->Release();
			return false;
		}
		if( pErrorBlob ) 
			pErrorBlob->Release();

		return true;
	}
public:
	CEffectTemplated()
	: m_VertexShader(NULL)
	, m_PixelShader(NULL)
	, m_VertexLayout(NULL)
	{
	}
	virtual ~CEffectTemplated()
	{
		CleanUp();
	}
	void CleanUp()
	{
		CHECKED_RELEASE(m_VertexShader);
		CHECKED_RELEASE(m_PixelShader);
		CHECKED_RELEASE(m_VertexLayout);
		CHECKED_RELEASE(m_ConstantBuffer);
	}
	bool Reload(ID3D11Device *Device)
	{
		CleanUp();
		return Load(Device, m_Filename, m_PointEntryVS, m_ShaderModelVS, m_PointEntryPS, m_ShaderModelPS);
	}
	bool Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
	{
		m_Filename=Filename;
		m_PointEntryVS=PointEntryVS;
		m_ShaderModelVS=ShaderModelVS;
		m_PointEntryPS=PointEntryPS;
		m_ShaderModelPS=ShaderModelPS;

		ID3DBlob *l_VSBlob=NULL;
		bool l_Loaded=LoadShader(Filename, PointEntryVS, ShaderModelVS, &l_VSBlob);
		if(!l_Loaded)
			return false;
		HRESULT l_HR=Device->CreateVertexShader(l_VSBlob->GetBufferPointer(), l_VSBlob->GetBufferSize(), NULL, &m_VertexShader);
		if( FAILED(l_HR) )
		{	
			l_VSBlob->Release();
			return false;
		}
		l_Loaded=T::CreateInputLayout(Device, l_VSBlob, &m_VertexLayout);
		
		l_VSBlob->Release();
		
		if(!l_Loaded)
			return false;

		ID3DBlob *l_PSBlob=NULL;
		l_Loaded=LoadShader(Filename.c_str(), PointEntryPS.c_str(), ShaderModelPS.c_str(), &l_PSBlob);
		if(!l_Loaded)
			return false;

		l_HR=Device->CreatePixelShader(l_PSBlob->GetBufferPointer(), l_PSBlob->GetBufferSize(), NULL, &m_PixelShader);
		l_PSBlob->Release();

		D3D11_BUFFER_DESC l_BufferDescription;
		ZeroMemory(&l_BufferDescription, sizeof(l_BufferDescription));

		l_BufferDescription.Usage=D3D11_USAGE_DEFAULT;
		l_BufferDescription.ByteWidth=sizeof(CEffectParameters);
		l_BufferDescription.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
		l_BufferDescription.CPUAccessFlags=0;
		if( FAILED(Device->CreateBuffer(&l_BufferDescription, NULL, &m_ConstantBuffer)))
			return false;

		return !FAILED(l_HR);
	}
	ID3D11VertexShader * GetVertexShader()
	{
		return m_VertexShader;
	}
	ID3D11PixelShader * GetPixelShader() 
	{
		return m_PixelShader;
	}
	ID3D11InputLayout * GetVertexLayout()
	{
		return m_VertexLayout;
	}
	ID3D11Buffer * GetConstantBuffer()
	{
		return m_ConstantBuffer;
	}
	bool Reload();
};

class CEffectManager 
{
private:
	std::map<unsigned int, CEffect *> m_EffectsByVertexType;
	std::map<std::string, CEffect *> m_Effects;

	template<class T>
	void AddEffect(ID3D11Device *Device, const std::string &Name, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS);
	template<class T>
	void AddEffect(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS);
public:
	static CEffectParameters m_Parameters;

	CEffectManager();
	~CEffectManager();
	CEffect * GetEffect(unsigned int VertexType);
	CEffect * GetEffect(const std::string &Name);
};

#endif
