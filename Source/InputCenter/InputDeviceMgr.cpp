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
			g_program->Get_m_InputEventMgr()->FireEvent((InputEventType)i, m_durationTime, NULL, 0);
		}
	}
}

VOID HInputDeviceMgr::DealMouseAxisStateData() {
	if (m_mouseState.lX != 0 || m_mouseState.lY != 0 || m_mouseState.lZ != 0) {
		LONG distance[3] = { m_mouseState.lX, m_mouseState.lY, m_mouseState.lZ };
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_MA, m_durationTime, distance, 3);
	}
}

VOID HInputDeviceMgr::DealMouseBottonStateData() {
	if (m_mouseState.rgbButtons[0] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_LMB, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[1] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_RMB, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[2] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_MMB, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[3] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_CMB1, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[4] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_CMB2, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[5] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_CMB3, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[6] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_CMB4, m_durationTime, NULL, 0);
	} else if (m_mouseState.rgbButtons[7] & 0x80) {
		g_program->Get_m_InputEventMgr()->FireEvent(InputEventType_CMB5, m_durationTime, NULL, 0);
	}
}
