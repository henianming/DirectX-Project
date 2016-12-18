#include "InputDeviceMgr.h"
#include "Common/CommonCode.h"
#include "program.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
BOOL HInputDeviceMgr::Create() {
	m_time.Reset();
	g_program->Get_m_timeMgr()->Registe(&m_time);

	RF_HR_FAILED(
		DirectInput8Create(
			g_program->Get_m_hInstance(),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(VOID**)(&m_iDirectInput),
			NULL
		)
	);

	RF_HR_FAILED(m_iDirectInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL));
	RF_HR_FAILED(m_mouse->SetDataFormat(&c_dfDIMouse2));
	RF_HR_FAILED(m_mouse->SetCooperativeLevel(g_program->Get_m_hWnd(), DISCL_FOREGROUND | DISCL_EXCLUSIVE));

	RF_HR_FAILED(m_iDirectInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL));
	RF_HR_FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard));
	RF_HR_FAILED(m_keyboard->SetCooperativeLevel(g_program->Get_m_hWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	return TRUE;
}

BOOL HInputDeviceMgr::Release() {
	if (m_keyboard) {
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	if (m_mouse) {
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_iDirectInput) {
		m_iDirectInput->Release();
		m_iDirectInput = NULL;
	}

	g_program->Get_m_timeMgr()->Unregiste(&m_time);

	return TRUE;
}

VOID HInputDeviceMgr::Update() {
	DOUBLE timeNew = m_time.Get_m_curTimeStamp();
	m_durationTime = timeNew - m_timeOld;
	m_timeOld = timeNew;

	R_HR_FAILED(m_mouse->Acquire());
	R_HR_FAILED(m_mouse->Poll());
	R_HR_FAILED(m_mouse->GetDeviceState(sizeof(m_mouseState), (VOID*)(&m_mouseState)));

	R_HR_FAILED(m_keyboard->Acquire());
	R_HR_FAILED(m_keyboard->Poll());
	R_HR_FAILED(m_keyboard->GetDeviceState(sizeof(m_keyboardState), (VOID*)(&m_keyboardState)));

	DealKeyboardStateData();
	DealMouseAxisStateData();
	DealMouseBottonStateData();
}

VOID HInputDeviceMgr::DealKeyboardStateData() {
	for (int i = 0; i < 256; i++) {
		if (m_keyboardState[i] & 0x80) {
			g_program->Get_m_InputEventMgr()->FireEvent((BYTE)i, m_durationTime, 0);
		}
	}
}

VOID HInputDeviceMgr::DealMouseAxisStateData() {

}

VOID HInputDeviceMgr::DealMouseBottonStateData() {

}
