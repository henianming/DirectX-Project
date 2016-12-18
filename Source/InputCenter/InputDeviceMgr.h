#pragma once

#include <dinput.h>

#include "TimeCenter/Time.h"

//--------·Ö½çÏß-----------------------------------------------------------------
class HInputDeviceMgr {
private:
	IDirectInput8 *m_iDirectInput;
	IDirectInputDevice8 *m_mouse;
	DIMOUSESTATE2 m_mouseState;
	IDirectInputDevice8 *m_keyboard;
	BYTE m_keyboardState[256];

	HTime m_time;
	DOUBLE m_timeOld;
	DOUBLE m_durationTime;

public:
	BOOL Create();
	BOOL Release();
	VOID Update();

private:
	VOID DealKeyboardStateData();
	VOID DealMouseAxisStateData();
	VOID DealMouseBottonStateData();
};