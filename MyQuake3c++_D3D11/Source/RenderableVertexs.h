#ifndef __RENDERABLE_VERTEXS_H
#define __RENDERABLE_VERTEXS_H

#include <assert.h>
#include "defines.h"

#ifdef KG_D3D11
#include <D3DX11.h>
#else
#include <d3dx9.h>
#endif

class CEffect;

class CRenderableVertexs
{
public:
	virtual bool Draw(ID3D11DeviceContext *Device, CEffect *Effect, void *Parameters) 
	{
		assert(!"This method mustn't be called");
		return false;
	}
	virtual bool DrawIndexed(ID3D11DeviceContext *Device, CEffect *Effect, void *Parameters, unsigned int IndexCount=-1, unsigned int StartIndexLocation=0, unsigned int BaseVertexLocation=0)
	{
		assert(!"This method mustn't be called");
		return false;
	}
};

template<class T>
class CTemplatedRenderableVertexs : public CRenderableVertexs
{
private:
	ID3D11Buffer					*m_VertexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY		m_PrimitiveTopology;
	unsigned int m_VertexsCount;
	unsigned int m_PrimitiveCount;
public:
	CTemplatedRenderableVertexs(ID3D11Device *Device, void *Vtxs, unsigned int VtxsCount, D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology, unsigned int PrimitiveCount)
	: m_VertexsCount(VtxsCount)
	, m_PrimitiveTopology(PrimitiveTopology)
	, m_PrimitiveCount(PrimitiveCount)
	{
		D3D11_BUFFER_DESC l_BufferDescription;
		ZeroMemory(&l_BufferDescription, sizeof(l_BufferDescription));
		l_BufferDescription.Usage=D3D11_USAGE_DEFAULT;
		l_BufferDescription.ByteWidth=sizeof(T)*m_VertexsCount;
		l_BufferDescription.BindFlags=D3D11_BIND_VERTEX_BUFFER;
		l_BufferDescription.CPUAccessFlags=0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = Vtxs;
		HRESULT l_HR=Device->CreateBuffer(&l_BufferDescription, &InitData, &m_VertexBuffer);
		if(FAILED(l_HR))
			return;
	}
	virtual ~CTemplatedRenderableVertexs()
	{
		CHECKED_RELEASE(m_VertexBuffer);
	}
	bool Draw(ID3D11DeviceContext *Device, CEffect *Effect, void *Parameters)
	{
		if(Effect->GetPixelShader()==NULL || Effect->GetVertexShader()==NULL)
			return false;

		UINT stride=sizeof(T);
		UINT offset=0;
		Device->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		Device->IASetPrimitiveTopology(m_PrimitiveTopology);
		Device->IASetInputLayout(Effect->GetVertexLayout());
		Device->VSSetShader(Effect->GetVertexShader(), NULL, 0);
		Device->UpdateSubresource(Effect->GetConstantBuffer(), 0, NULL, Parameters, 0, 0 );
		ID3D11Buffer *l_ConstantBuffer=Effect->GetConstantBuffer();
		Device->VSSetConstantBuffers( 0, 1, &l_ConstantBuffer);
		Device->PSSetShader(Effect->GetPixelShader(), NULL, 0);

		Device->Draw(m_VertexsCount, 0);
		return true;
	}
};


#define CRENDERABLE_VERTEX_CLASS_TYPE_CREATOR(ClassName, TopologyType) \
template<class T> \
class ClassName : public CTemplatedRenderableVertexs<T> \
{ \
public: \
	ClassName(ID3D11Device *Device, void *Vtxs, unsigned int VtxsCount, unsigned int PrimitiveCount) \
	: CTemplatedRenderableVertexs(Device, Vtxs, VtxsCount, TopologyType, PrimitiveCount) \
	{ \
	} \
};

CRENDERABLE_VERTEX_CLASS_TYPE_CREATOR(CLinesListRenderableVertexs, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
CRENDERABLE_VERTEX_CLASS_TYPE_CREATOR(CTrianglesListRenderableVertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
CRENDERABLE_VERTEX_CLASS_TYPE_CREATOR(CTrianglesStripRenderableVertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

template<class T>
class CTemplatedRenderableIndexedVertexs : public CRenderableVertexs
{
private:
	ID3D11Buffer					*m_VertexBuffer;
	ID3D11Buffer					*m_IndexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY		m_PrimitiveTopology;
	DXGI_FORMAT						m_IndexType;
	unsigned int					m_VertexsCount;
	unsigned int					m_IndexsCount;
public:
	CTemplatedRenderableIndexedVertexs(ID3D11Device *Device, void *Vtxs, unsigned int VtxsCount, void *Indices, unsigned int IndexsCount, D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology, DXGI_FORMAT IndexType)
	: m_VertexsCount(VtxsCount)
	, m_IndexsCount(IndexsCount)
	, m_PrimitiveTopology(PrimitiveTopology)
	, m_VertexBuffer(0)
	, m_IndexBuffer(0)
	, m_IndexType(IndexType)
	{
		D3D11_BUFFER_DESC l_VertexBufferDesc;
		ZeroMemory(&l_VertexBufferDesc, sizeof(l_VertexBufferDesc));
		l_VertexBufferDesc.Usage=D3D11_USAGE_DEFAULT;
		l_VertexBufferDesc.ByteWidth=sizeof(T)*m_VertexsCount;
		l_VertexBufferDesc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
		l_VertexBufferDesc.CPUAccessFlags=0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem=Vtxs;
		HRESULT hr=Device->CreateBuffer(&l_VertexBufferDesc, &InitData, &m_VertexBuffer);
		if(FAILED(hr))
			return;
		
		D3D11_BUFFER_DESC l_IndexBuffer;
		ZeroMemory(&l_IndexBuffer, sizeof(l_IndexBuffer));
		l_IndexBuffer.Usage=D3D11_USAGE_DEFAULT;
		l_IndexBuffer.ByteWidth=(m_IndexType==DXGI_FORMAT_R16_UINT ? sizeof(WORD) : sizeof(unsigned int))*m_IndexsCount;
		l_IndexBuffer.BindFlags=D3D11_BIND_INDEX_BUFFER;
		l_IndexBuffer.CPUAccessFlags=0;
		InitData.pSysMem=Indices;
		hr=Device->CreateBuffer(&l_IndexBuffer, &InitData, &m_IndexBuffer);
		if(FAILED(hr))
			return;
	}
	virtual ~CTemplatedRenderableIndexedVertexs()
	{
		CHECKED_RELEASE(m_VertexBuffer);
		CHECKED_RELEASE(m_IndexBuffer);
	}
	bool DrawIndexed(ID3D11DeviceContext *Device, CEffect *Effect, void *Parameters, unsigned int IndexCount=-1, unsigned int StartIndexLocation=0, unsigned int BaseVertexLocation=0)
	{
		if(Effect->GetPixelShader()==NULL || Effect->GetVertexShader()==NULL)
			return false;

		UINT stride=sizeof(T);
		UINT offset=0;
		Device->IASetIndexBuffer(m_IndexBuffer, m_IndexType, 0);
		Device->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		Device->IASetPrimitiveTopology(m_PrimitiveTopology);
		Device->IASetInputLayout(Effect->GetVertexLayout());
		Device->VSSetShader(Effect->GetVertexShader(), NULL, 0);
		Device->UpdateSubresource(Effect->GetConstantBuffer(), 0, NULL, Parameters, 0, 0 );
		ID3D11Buffer *l_ConstantBuffer=Effect->GetConstantBuffer();
		Device->VSSetConstantBuffers( 0, 1, &l_ConstantBuffer);
		Device->PSSetShader(Effect->GetPixelShader(), NULL, 0);
		Device->DrawIndexed(IndexCount==-1 ? m_IndexsCount : IndexCount, StartIndexLocation, BaseVertexLocation);
		return true;
	}
};

#define CRENDERABLE_INDEXED_VERTEX_CLASS_TYPE_CREATOR(ClassName, TopologyType, IndexType) \
template<class T> \
class ClassName : public CTemplatedRenderableIndexedVertexs<T> \
{ \
public: \
	ClassName(ID3D11Device *Device, void *Vtxs, unsigned int VtxsCount, void *Indices, unsigned int IndexsCount) \
	: CTemplatedRenderableIndexedVertexs(Device, Vtxs, VtxsCount, Indices, IndexsCount, TopologyType, IndexType) \
	{ \
	} \
};

CRENDERABLE_INDEXED_VERTEX_CLASS_TYPE_CREATOR(CTriangleListRenderableIndexed16Vertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R16_UINT);
CRENDERABLE_INDEXED_VERTEX_CLASS_TYPE_CREATOR(CTriangleListRenderableIndexed32Vertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, DXGI_FORMAT_R32_UINT);
CRENDERABLE_INDEXED_VERTEX_CLASS_TYPE_CREATOR(CTriangleStripRenderableIndexed16Vertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, DXGI_FORMAT_R16_UINT);
CRENDERABLE_INDEXED_VERTEX_CLASS_TYPE_CREATOR(CTriangleStripRenderableIndexed32Vertexs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, DXGI_FORMAT_R32_UINT);

#endif
