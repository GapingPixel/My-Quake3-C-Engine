#ifndef _APPLICATION_DX_H
#define _APPLICATION_DX_H

#include "defines.h"
#include <AntTweakBar.h>

class CDebugRender;
class CEffectManager;
class CInputManager;
class CCameraManager;
class CPlayer;

class CApplicationDX
{
private:
	unsigned int			m_IntroSound;
	ID3D11Device			*m_D3DDevice;
	ID3D11DeviceContext		*m_DeviceContext;
	IDXGISwapChain			*m_SwapChain;
	ID3D11RenderTargetView	*m_RenderTargetView;
	ID3D11Texture2D			*m_DepthStencil;
	ID3D11DepthStencilView	*m_DepthStencilView;
	XMFLOAT4				m_BackgroundColor;
	CDebugRender			*m_DebugRender;
	CEffectManager 			*m_EffectManager;
	CInputManager			*m_InputManager;
	CCameraManager			*m_CameraManager;
	CPlayer 				*m_Player;
	bool					m_PaintSolid;
	bool					m_DrawAxisGrid;
	HWND					m_hWnd;
	TwBar					*m_Bar;
	bool					m_DrawAntTweakBar;
	DWORD 					m_PreviousTime;
	float					m_ElapsedTime;

	static CApplicationDX	*m_ApplicationDX;

	CApplicationDX();
	HRESULT InitDX(HWND hWnd, int Width, int Height);
	HRESULT InitData();
	void UpdateActions();
	void SetupMatrices();
	void BeginRenderDX();
	void EndRenderDX();
public:	
	~CApplicationDX();
	
	static CApplicationDX * GetApplicationDX();
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void InitAndLoad(HWND hWnd, int Width, int Height);
	void Update();
	void Render();
	ID3D11Device * GetDevice() const {return m_D3DDevice;}
	ID3D11DeviceContext	* GetDeviceContext() const {return m_DeviceContext;}
	CDebugRender * GetDebugRender() const {return m_DebugRender;}
	CEffectManager * GetEffectManager() const {return m_EffectManager;}
	CInputManager * GetInputManager() const {return m_InputManager;}
	CCameraManager * GetCameraManager() const {return m_CameraManager;}
	CPlayer * GetPlayer() const {return m_Player;}
	bool IsAntTweakBarActive() const {return m_DrawAntTweakBar;}
	void SetPaintSolid(bool PaintSolid);
	bool GetPaintSolid() const {return m_PaintSolid;}
};

#endif
