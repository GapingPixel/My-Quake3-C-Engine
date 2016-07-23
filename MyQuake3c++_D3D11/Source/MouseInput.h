#ifndef INC_MOUSE_H_
#define INC_MOUSE_H_

#include <dinput.h>

class CMouseInput
{
private:
	LPDIRECTINPUT8						m_DI;
	LPDIRECTINPUTDEVICE8				m_Mouse;	

	int									m_MovementX;
	int									m_MovementY;
	int									m_MovementZ;
	bool								m_ButtonRight, m_PreviousButtonRight;
	bool								m_ButtonLeft, m_PreviousButtonLeft;
	bool								m_ButtonMiddle, m_PreviousButtonMiddle;
public:
	CMouseInput(HWND hWnd);
	virtual ~CMouseInput();
	
	bool Update();
	int GetMovementX() const;
	int GetMovementY() const;
	int GetMovementZ() const;
	bool IsLeftButtonPressed() const;
	bool IsMiddleButtonPressed() const;
	bool IsRightButtonPressed() const;

	bool LeftButtonBecomesPressed() const;
	bool MiddleButtonBecomesPressed() const;
	bool RightButtonBecomesPressed() const;

	bool LeftButtonBecomesReleased() const;
	bool MiddleButtonBecomesReleased() const;
	bool RightButtonBecomesReleased() const;
};

#endif
