#ifndef INC_INPUTMANAGER_H_
#define INC_INPUTMANAGER_H_

#include "MouseInput.h"
#include "KeyboardInput.h"

class CInputManager
{
private:
	CMouseInput					*m_MouseInput;
	CKeyboardInput				*m_KeyboardInput;
public:
	CInputManager(HWND hWnd);
	virtual ~CInputManager();  
	
	void OnCreateDevice(HWND hWnd);
	CMouseInput * GetMouse() {return m_MouseInput;}
	CKeyboardInput * GetKeyboard() {return m_KeyboardInput;}
	void Update();
};

#endif
