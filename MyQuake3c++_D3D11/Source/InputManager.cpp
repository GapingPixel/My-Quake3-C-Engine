#include "InputManager.h"
#include "defines.h"
#include <string>
#include <map>

CInputManager::CInputManager(HWND hWnd)
{
	m_KeyboardInput=new CKeyboardInput(hWnd);
	m_MouseInput=new CMouseInput(hWnd);
}

CInputManager::~CInputManager()
{
	CHECKED_DELETE(m_MouseInput);
	CHECKED_DELETE(m_KeyboardInput);
}

void CInputManager::Update()
{
	m_KeyboardInput->Update();
	m_MouseInput->Update();
}
