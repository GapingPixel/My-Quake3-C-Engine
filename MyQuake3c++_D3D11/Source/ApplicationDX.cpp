#include "ApplicationDX.h"
#include <assert.h>
#include "defines.h"
#include "DebugRender.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "VertexTypes.h"
#include "Player.h"

CApplicationDX * CApplicationDX::m_ApplicationDX=NULL;

CApplicationDX::CApplicationDX()
: m_DeviceContext(NULL)
, m_SwapChain(NULL)
, m_RenderTargetView(NULL)
, m_DepthStencil(NULL)
, m_DepthStencilView(NULL)
, m_D3DDevice(NULL)
, m_PaintSolid(true)
, m_hWnd(NULL)
, m_DrawAxisGrid(true)
, m_BackgroundColor(0.0f, 0.0f, 1.0f, 1.0f)
, m_DrawAntTweakBar(false)
{
}

CApplicationDX::~CApplicationDX()
{
	TwTerminate();
	CHECKED_DELETE(m_Player);
	CHECKED_DELETE(m_InputManager);
	CHECKED_DELETE(m_CameraManager);
	//TO DO: Eliminamos el objeto m_DebugRender
	CHECKED_DELETE(m_DebugRender);
	
	CHECKED_DELETE(m_EffectManager);
	if(m_DeviceContext) 
		m_DeviceContext->ClearState();
	CHECKED_RELEASE(m_RenderTargetView);
    CHECKED_RELEASE(m_SwapChain);
    CHECKED_RELEASE(m_DeviceContext);
	CHECKED_RELEASE(m_D3DDevice);
}

CApplicationDX * CApplicationDX::GetApplicationDX()
{
	if(m_ApplicationDX==NULL)
		m_ApplicationDX=new CApplicationDX;
	return m_ApplicationDX;
}

void CApplicationDX::InitAndLoad(HWND hWnd, int Width, int Height)
{
	m_hWnd = hWnd;
	HRESULT hr = InitDX( hWnd, Width, Height);
	assert( SUCCEEDED( hr ) );

	hr = InitData();
	assert( SUCCEEDED( hr ) );
}

HRESULT CApplicationDX::InitDX( HWND hWnd , int Width, int Height)
{
	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof(sd) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = Width;
    sd.BufferDesc.Height = Height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    if(FAILED(D3D11CreateDeviceAndSwapChain( NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels,
                     D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_D3DDevice, NULL, &m_DeviceContext ) ) )
    {
        return FALSE;
    }
	ID3D11Texture2D *pBackBuffer;
    if( FAILED( m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBackBuffer ) ) )
        return FALSE;
    HRESULT hr = m_D3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_RenderTargetView );
    pBackBuffer->Release();
    if( FAILED( hr ) )
        return FALSE;

	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = Width;
    descDepth.Height = Height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = m_D3DDevice->CreateTexture2D( &descDepth, NULL, &m_DepthStencil);
    if( FAILED( hr ) )
        return hr;

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_D3DDevice->CreateDepthStencilView( m_DepthStencil, &descDSV, &m_DepthStencilView );
    if( FAILED( hr ) )
        return hr;

    m_DeviceContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );

	D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)Width;
    vp.Height = (FLOAT)Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_DeviceContext->RSSetViewports( 1, &vp );

	m_InputManager=new CInputManager(hWnd);
	m_EffectManager=new CEffectManager();
    return S_OK;
}

void TW_CALL SetPaintSolidD3D11(const void *value, void *clientData)
{
	bool l_PaintSolid=*static_cast<const bool *>(value);
	CApplicationDX::GetApplicationDX()->SetPaintSolid(l_PaintSolid);
}

void TW_CALL GetPaintSolidD3D11(void *value, void *clientData)
{
	*static_cast<bool *>(value)=CApplicationDX::GetApplicationDX()->GetPaintSolid();
}

template<class T>
void TW_CALL ReloadDebugShader(void *ClientData)
{
	ID3D11Device *l_Device=CApplicationDX::GetApplicationDX()->GetDevice();
	CApplicationDX::GetApplicationDX()->GetEffectManager()->GetEffect(T::GetVertexType())->Reload(l_Device);
}

HRESULT CApplicationDX::InitData()
{
	TwInit(TW_DIRECT3D11, m_D3DDevice);

	m_Bar = TwNewBar("TweakBar");
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar into a DirectX11 application.' ");
	int l_BarSize[2]={224, 320};
    TwSetParam(m_Bar, NULL, "size", TW_PARAM_INT32, 2, l_BarSize);
	
	//TO DO: Añadimos con la función TwAddVarCB un elemento de tipo TW_TYPE_BOOLCPP a la AntTweakBar m_Bar con nombre "PaintSolid", pasándole los métodos Set y GetPaintSolidD3D11 y definición "group=Render"
	TwAddVarCB(m_Bar, "PaintSolid", TW_TYPE_BOOLCPP, SetPaintSolidD3D11, GetPaintSolidD3D11, NULL, "group=Render");
	
	//TO DO: Añadimos con la función TwAddVarRW un elemento de tipo TW_TYPE_BOOLCPP a la AntTweakBar m_Bar con nombre "AxisGrid", pasándole la dirección de la variable m_DrawAxisGrid y definición "group=Render"
	TwAddVarRW(m_Bar, "AxisGrid", TW_TYPE_BOOLCPP, NULL, "group=Render");

	//TO DO: Añadimos con la función TwAddVarRW un elemento de tipo TW_TYPE_COLOR4F a la AntTweakBar m_Bar con nombre "BackgroundColor", pasándole la dirección de la variable m_BackgroundColor y definición "group=Render"
	TwAddVarRW(m_Bar, "BackgroundColor", TW_TYPE_COLOR4F, &m_BackgroundColor.x, "group=Render");

	//TO DO: Construímos el objeto m_DebugRender pasando el device en el constructor
	m_DebugRender=new CDebugRender(m_D3DDevice);

	m_CameraManager=new CCameraManager;
	m_CameraManager->Load( "./DATA/XML/cameras.xml" );

	m_PreviousTime=timeGetTime();

	m_Player=new CPlayer;

	return S_OK;
}

void CApplicationDX::SetupMatrices()
{
	const CCamera &l_Camera=m_CameraManager->GetCamera();
	XMMATRIX l_View=l_Camera.GetView();
	XMMATRIX l_Projection=l_Camera.GetProjection();
	CEffectManager::m_Parameters.m_View=XMMatrixTranspose(l_View);
	CEffectManager::m_Parameters.m_Projection=XMMatrixTranspose(l_Projection);
	CEffectManager::m_Parameters.m_World=XMMatrixTranspose(XMMatrixIdentity());
}

void CApplicationDX::BeginRenderDX()
{
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, &m_BackgroundColor.x);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void CApplicationDX::EndRenderDX()
{
	m_SwapChain->Present(0, 0);
}

void CApplicationDX::Render()
{
	ID3D11DeviceContext *l_Device=m_DeviceContext;
	BeginRenderDX();
	SetupMatrices();
		
	if(m_DrawAxisGrid)
	{
		CEffectManager::m_Parameters.m_World=XMMatrixTranspose(XMMatrixIdentity());
		//TO DO: Creamos un color de tipo XMFLOAT4 que utilizaremos para pintar la grid, cubo y esfera
		XMFLOAT4 l_DebugRenderColor(1.0f, 1.0f, 1.0f, 1.0f);

		//TO DO: Pintamos unos ejes usando el objeto m_DebugRender pasando el device y el tamaño de los ejes (8)
		m_DebugRender->DrawAxis(l_Device, 8.0f);		
		//TO DO: Pintamos una grid usando el objeto m_DebugRender pasando el device, el tamaño de la grid (1) y el color de la grid
		m_DebugRender->DrawGrid(l_Device, 1.0f, l_DebugRenderColor);
		
		//TO DO: Pintamos un cubo usando el objeto m_DebugRender pasando el device, el tamaño del cubo (3) y el color del cubo
		m_DebugRender->DrawCube(l_Device, 3.0f, l_DebugRenderColor);
		
		//TO DO: Pintamos una esfera usando el objeto m_DebugRender pasando el device, el radio de la esfera (0.5) y el color de la esfera
		m_DebugRender->DrawSphere(l_Device, 0.5f, l_DebugRenderColor);

		XMFLOAT4 l_RedDebugRenderColor(1.0f, 0.0f, 0.0f, 1.0f);
		XMFLOAT4 l_GreenDebugRenderColor(0.0f, 1.0f, 0.0f, 1.0f);

		CEffectManager::m_Parameters.m_World=XMMatrixTranspose(XMMatrixTranslation(10.0f, 0.0f, 0.0f));
		m_DebugRender->DrawCube(l_Device, 3.0f, l_RedDebugRenderColor);
		
		CEffectManager::m_Parameters.m_World=XMMatrixTranspose(XMMatrixTranslation(-10.0f, 0.0f, 0.0f));
		m_DebugRender->DrawCube(l_Device, 3.0f, l_GreenDebugRenderColor);
	}

	if(m_DrawAntTweakBar)
		TwDraw();

	EndRenderDX();
}

void CApplicationDX::Update()
{
	DWORD l_CurrentTime=timeGetTime();
	m_ElapsedTime=(float)(l_CurrentTime-m_PreviousTime)*0.001f;
	m_PreviousTime=l_CurrentTime;

	m_InputManager->Update();

	CCameraController *l_CameraController=m_CameraManager->GetCameraController("player");
	
	UpdateActions();

	m_Player->Update(m_ElapsedTime);
	
	if(!m_DrawAntTweakBar)
		m_CameraManager->Update(m_ElapsedTime);	
}

void CApplicationDX::UpdateActions()
{
	CKeyboardInput *l_KeyboardInput=m_InputManager->GetKeyboard();

	CCameraController *l_CameraPlayer=m_CameraManager->GetCameraController("player");
	
	if(l_KeyboardInput->KeyBecomesPressed(DIK_TAB))
		m_CameraManager->ChangeVision();

	if(l_KeyboardInput->KeyBecomesPressed(DIK_C))
		m_CameraManager->ChangeControl();
	
	if(l_KeyboardInput->KeyBecomesPressed(DIK_J))
		m_DrawAntTweakBar=!m_DrawAntTweakBar;
}

LRESULT WINAPI CApplicationDX::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(TwEventWin(hWnd, msg, wParam, lParam))
		return 0;
	switch( msg )
    {
		case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage( 0 );
					return 0;
					break;
			}
		}
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void CApplicationDX::SetPaintSolid(bool PaintSolid)
{
	m_PaintSolid=PaintSolid;
	if(PaintSolid)
		m_DebugRender->SetSolidRenderState(m_DeviceContext);
	else
		m_DebugRender->SetWireframeRenderState(m_DeviceContext);
}
