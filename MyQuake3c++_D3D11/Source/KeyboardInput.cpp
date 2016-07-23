#include "KeyboardInput.h"
#include "defines.h"

CKeyboardInput::CKeyboardInput(HWND hWnd)
{
	ZeroMemory(m_Diks, 256);
	ZeroMemory(m_PreviousDiks, 256);

	HRESULT l_HR;
    DWORD l_CoopFlags=DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;
   
    if(FAILED(l_HR=DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL ) ) )
        return;
    
	if(FAILED(l_HR=m_DI->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL)))
        return;
    
	if(FAILED(l_HR=m_Keyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
        return;
    
    l_HR=m_Keyboard->SetCooperativeLevel(hWnd, l_CoopFlags);
 
    if(FAILED(l_HR))
        return;

    m_Keyboard->Acquire();
}

CKeyboardInput::~CKeyboardInput()
{
	if(m_Keyboard) 
        m_Keyboard->Unacquire();
    
    CHECKED_RELEASE(m_Keyboard);
    CHECKED_RELEASE(m_DI);
}

bool CKeyboardInput::Update()
{
	HRESULT l_HR;
	
    if(NULL==m_Keyboard)
        return false;
    
	memcpy(m_PreviousDiks, m_Diks, 256);
    ZeroMemory(m_Diks, 256);
    l_HR=m_Keyboard->GetDeviceState(sizeof(m_Diks), (LPVOID)&m_Diks);
    if(FAILED(l_HR)) 
    {
        l_HR=m_Keyboard->Acquire();
        while(l_HR==DIERR_INPUTLOST)
            l_HR=m_Keyboard->Acquire();

        return true;
    }
    return true;
}

bool CKeyboardInput::IsKeyPressed(int KeyCode)
{
	return (m_Diks[KeyCode]&0x80)!=0;
}

bool CKeyboardInput::KeyBecomesPressed(int KeyCode)
{
	return m_Diks[KeyCode]&0x80 && !(m_PreviousDiks[KeyCode]&0x80);
}

bool CKeyboardInput::KeyBecomesReleased(int KeyCode)
{
	return !(m_Diks[KeyCode]&0x80) && m_PreviousDiks[KeyCode]&0x80;
}
