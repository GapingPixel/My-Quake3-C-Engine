#include "DebugRender.h"
#include "ApplicationDX.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"

CDebugRender::CDebugRender(ID3D11Device *Device)
{
	//AXIS
	m_Effect=CApplicationDX::GetApplicationDX()->GetEffectManager()->GetEffect(KG_POSITION_COLOR_VERTEX::GetVertexType());
	KG_POSITION_COLOR_VERTEX l_AxisVtxs[6]=
	{
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
			
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},

		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};
	
	m_AxisRenderableVertexs=new CLinesListRenderableVertexs<KG_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);
	
	//CUBE
	const float l_SizeCube=1.0f;
	KG_POSITION_COLOR_VERTEX l_CubeVtxs[]=
	{
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//tapa
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		//lineas laterales
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(-l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,-l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,-l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{XMFLOAT3(l_SizeCube/2.0f,l_SizeCube/2.0f,l_SizeCube/2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	m_CubeRenderableVertexs=new CLinesListRenderableVertexs<KG_POSITION_COLOR_VERTEX>(Device, l_CubeVtxs, 24, 12);

	//GRID
	float l_Size=10.0f;
	const int l_Grid=10;
	KG_POSITION_COLOR_VERTEX l_GridVtxs[(l_Grid+1)*2*2];
	for(int b=0;b<=l_Grid;++b)
	{
		l_GridVtxs[b*2].Position=XMFLOAT3(-l_Size/2.0f+((float)(b*l_Size))/(float)l_Grid,0.0f,-l_Size/2.0f);
		l_GridVtxs[b*2].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		l_GridVtxs[(b*2)+1].Position=XMFLOAT3(-l_Size/2.0f+((float)(b*l_Size))/(float)l_Grid,0.0f,l_Size/2.0f);
		l_GridVtxs[(b*2)+1].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//LINEAS EN X
	for(int b=0;b<=l_Grid;++b)
	{
		l_GridVtxs[(l_Grid+1)*2+(b*2)].Position=XMFLOAT3(-l_Size/2.0f,0.0f,-l_Size/2.0f+((float)(b*l_Size))/(float)l_Grid);
		l_GridVtxs[(l_Grid+1)*2+(b*2)].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		l_GridVtxs[(l_Grid+1)*2+(b*2)+1].Position=XMFLOAT3(l_Size/2.0f,0.0f,-l_Size/2.0f+((float)(b*l_Size))/(float)l_Grid);
		l_GridVtxs[(l_Grid+1)*2+(b*2)+1].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_GridRenderableVertexs=new CLinesListRenderableVertexs<KG_POSITION_COLOR_VERTEX>(Device, l_GridVtxs, (l_Grid+1)*2*2, (l_Grid+1)*2);
	
	//SPHERE
	const int l_Aristas=10;
	KG_POSITION_COLOR_VERTEX l_SphereVtxs[4*l_Aristas*l_Aristas];
	for(int t=0;t<l_Aristas;++t)
	{
		float l_RadiusRing=sin(DEG2RAD(180.0f*((float)t))/((float)l_Aristas));
		for(int b=0;b<l_Aristas;++b)
		{
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+0].Position=XMFLOAT3(l_RadiusRing*cos(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))),cos(DEG2RAD(180.0f*((float)t))/((float)l_Aristas)),l_RadiusRing*sin(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))));
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+0].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+1].Position=XMFLOAT3(l_RadiusRing*cos(DEG2RAD((float)(360.0f*(float)(b+1))/((float)l_Aristas))),cos(DEG2RAD(180.0f*((float)t))/((float)l_Aristas)),l_RadiusRing*sin(DEG2RAD((float)(360.0f*(float)(b+1))/((float)l_Aristas))));
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+1].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			
			float l_RadiusNextRing=sin(DEG2RAD(180.0f*((float)(t+1)))/((float)l_Aristas));
			
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+2].Position=XMFLOAT3(l_RadiusRing*cos(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))),cos(DEG2RAD(180.0f*((float)t))/((float)l_Aristas)),l_RadiusRing*sin(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))));
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+2].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+3].Position=XMFLOAT3(l_RadiusNextRing*cos(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))),cos(DEG2RAD(180.0f*((float)(t+1)))/((float)l_Aristas)),l_RadiusNextRing*sin(DEG2RAD((float)(360.0f*(float)b)/((float)l_Aristas))));
			l_SphereVtxs[(t*l_Aristas*4)+(b*4)+3].Color=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	m_SphereRenderableVertexs=new CLinesListRenderableVertexs<KG_POSITION_COLOR_VERTEX>(Device, l_SphereVtxs, 4*l_Aristas*l_Aristas, 2*l_Aristas*l_Aristas);
	
	//DRAWQUAD
	m_DrawQuadEffect=CApplicationDX::GetApplicationDX()->GetEffectManager()->GetEffect(KG_POSITION4_COLOR_TEXTURE_VERTEX::GetVertexType());

	KG_POSITION4_COLOR_TEXTURE_VERTEX l_ScreenVertexsQuad[4]=
	{
		{XMFLOAT4(-1.0f, 1.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f)},
		{XMFLOAT4(1.0f, 1.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f)},
		{XMFLOAT4(-1.0f, -1.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)},
		{XMFLOAT4(1.0f, -1.0f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f)}
	};
	m_DrawQuadRV=new CTrianglesStripRenderableVertexs<KG_POSITION4_COLOR_TEXTURE_VERTEX>(Device, l_ScreenVertexsQuad, 4, 2);

	D3D11_BLEND_DESC l_AlphablendDesc;
	ZeroMemory(&l_AlphablendDesc, sizeof(D3D11_BLEND_DESC));
	l_AlphablendDesc.RenderTarget[0].BlendEnable=true;
	l_AlphablendDesc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
	l_AlphablendDesc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
	l_AlphablendDesc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
	l_AlphablendDesc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_ONE;
	l_AlphablendDesc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ONE;
	l_AlphablendDesc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
	l_AlphablendDesc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;

	if(FAILED(Device->CreateBlendState(&l_AlphablendDesc, &m_DrawQuadBlendState)))
		return;

	//RENDER STATES
	D3D11_RASTERIZER_DESC l_WireframeDesc;
	ZeroMemory(&l_WireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_WireframeDesc.FillMode=D3D11_FILL_WIREFRAME;
	l_WireframeDesc.CullMode=D3D11_CULL_BACK;
	
	HRESULT l_HR=Device->CreateRasterizerState(&l_WireframeDesc, &m_WireframeRenderState);

	D3D11_RASTERIZER_DESC l_SolidDesc;
	ZeroMemory(&l_SolidDesc, sizeof(D3D11_RASTERIZER_DESC));
	l_SolidDesc.FillMode=D3D11_FILL_SOLID;
	l_SolidDesc.CullMode=D3D11_CULL_BACK;
	
	l_HR=Device->CreateRasterizerState(&l_SolidDesc, &m_SolidRenderState);
}

CDebugRender::~CDebugRender()
{
	CHECKED_DELETE(m_AxisRenderableVertexs);
	CHECKED_DELETE(m_GridRenderableVertexs);
	CHECKED_DELETE(m_CubeRenderableVertexs);
	CHECKED_DELETE(m_SphereRenderableVertexs);

	CHECKED_RELEASE(m_DrawQuadBlendState);
	CHECKED_DELETE(m_DrawQuadRV);

	CHECKED_RELEASE(m_WireframeRenderState);
	CHECKED_RELEASE(m_SolidRenderState);
}


void CDebugRender::DrawAxis(ID3D11DeviceContext *ImmediateContext, float Size)
{
	CEffectManager::m_Parameters.m_BaseColor=XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	CEffectManager::m_Parameters.m_DebugRenderScale=Size;
	m_AxisRenderableVertexs->Draw(ImmediateContext, m_Effect, &CEffectManager::m_Parameters);
}

void CDebugRender::DrawGrid(ID3D11DeviceContext *ImmediateContext, float Size, XMFLOAT4 Color)
{
	CEffectManager::m_Parameters.m_DebugRenderScale=Size;
	CEffectManager::m_Parameters.m_BaseColor=Color;
	m_GridRenderableVertexs->Draw(ImmediateContext, m_Effect, &CEffectManager::m_Parameters);
}

void CDebugRender::DrawCube(ID3D11DeviceContext *ImmediateContext, float Size, XMFLOAT4 Color)
{
	CEffectManager::m_Parameters.m_DebugRenderScale=Size;
	CEffectManager::m_Parameters.m_BaseColor=Color;
	m_CubeRenderableVertexs->Draw(ImmediateContext, m_Effect, &CEffectManager::m_Parameters);
}

void CDebugRender::DrawSphere(ID3D11DeviceContext *ImmediateContext, float Radius, XMFLOAT4 Color)
{
	CEffectManager::m_Parameters.m_DebugRenderScale=Radius;
	CEffectManager::m_Parameters.m_BaseColor=Color;
	m_SphereRenderableVertexs->Draw(ImmediateContext, m_Effect, &CEffectManager::m_Parameters);
}

void CDebugRender::SetSolidRenderState(ID3D11DeviceContext *Device)
{
	Device->RSSetState(m_SolidRenderState);
}

void CDebugRender::SetWireframeRenderState(ID3D11DeviceContext *Device)
{
	Device->RSSetState(m_WireframeRenderState);
}
