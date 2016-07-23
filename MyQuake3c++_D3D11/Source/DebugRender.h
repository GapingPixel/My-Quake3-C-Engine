#ifndef _DEBUGRENDER_H
#define _DEBUGRENDER_H

#include "defines.h"

class CRenderableVertexs;
class CEffect;

class CDebugRender
{
public:
	~CDebugRender();
private:
	CRenderableVertexs				*m_AxisRenderableVertexs;
	CRenderableVertexs				*m_GridRenderableVertexs;
	CRenderableVertexs				*m_CubeRenderableVertexs;
	CRenderableVertexs				*m_SphereRenderableVertexs;
	CEffect							*m_Effect;

	CEffect							*m_DrawQuadEffect;
	CRenderableVertexs				*m_DrawQuadRV;
	ID3D11BlendState				*m_DrawQuadBlendState;

	ID3D11RasterizerState			*m_WireframeRenderState;
	ID3D11RasterizerState			*m_SolidRenderState;
public:
	CDebugRender(ID3D11Device *Device);
	void DrawAxis(ID3D11DeviceContext *ImmediateContext, float Size);
	void DrawGrid(ID3D11DeviceContext *ImmediateContext, float Size, XMFLOAT4 Color);
	void DrawCube(ID3D11DeviceContext *ImmediateContext, float Size, XMFLOAT4 Color);
	void DrawSphere(ID3D11DeviceContext *ImmediateContext, float Radius, XMFLOAT4 Color);
	void SetSolidRenderState(ID3D11DeviceContext *Device);
	void SetWireframeRenderState(ID3D11DeviceContext *Device);
};

#endif
