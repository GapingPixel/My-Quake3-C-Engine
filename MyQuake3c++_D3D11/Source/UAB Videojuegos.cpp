#include <Windows.h>
#include "ApplicationDX.h"

#define WIDTH_APPLICATION 960
#define HEIGHT_APPLICATION 540

#define APPLICATION_NAME				"UAB Videojocs"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

CApplicationDX *g_ApplicationDX=NULL;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return g_ApplicationDX->MsgProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	//-----------Para detectar Memory Leaks-------------------------
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(-1);
	//--------------------------------------------------------------

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      APPLICATION_NAME, NULL };
    RegisterClassEx( &wc );

    RECT rc = { 0, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION};
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

    HWND hWnd = CreateWindow( APPLICATION_NAME, APPLICATION_NAME,
			WS_OVERLAPPEDWINDOW, 100, 100, rc.right-rc.left, rc.bottom-rc.top,
                              NULL, NULL, wc.hInstance, NULL );

	ShowWindow( hWnd, SW_SHOWDEFAULT );

	g_ApplicationDX=CApplicationDX::GetApplicationDX();

	g_ApplicationDX->InitAndLoad(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);
	
    UpdateWindow( hWnd );
	MSG msg;
    ZeroMemory( &msg, sizeof(msg) );

	while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
		{
			g_ApplicationDX->Update();
			g_ApplicationDX->Render();
		}
	}

	CHECKED_DELETE(g_ApplicationDX);
	UnregisterClass( APPLICATION_NAME, wc.hInstance );
	return 0;
}
