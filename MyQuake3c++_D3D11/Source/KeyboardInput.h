#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <dinput.h>

class CKeyboardInput
{
private:
	char								m_PreviousDiks[256];
	char								m_Diks[256];
	LPDIRECTINPUT8						m_DI;
	LPDIRECTINPUTDEVICE8				m_Keyboard;
public:
	CKeyboardInput(HWND hWnd);
	virtual ~CKeyboardInput();

	bool Update();
	bool IsKeyPressed(int KeyCode);
	bool KeyBecomesPressed(int KeyCode);
	bool KeyBecomesReleased(int KeyCode);
};

#endif
