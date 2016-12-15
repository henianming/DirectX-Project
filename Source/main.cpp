#include <Windows.h>
#include "Common/CommonCode.h"
#include "program.h"

HProgram *g_program;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_program) {
		switch (msg) {
		case WM_KEYDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_KEYDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_KEYUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_KEYUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_LBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_RBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOUSEMOVE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOUSEMOVE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_LBUTTONUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_RBUTTONUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOVE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOVE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOVING:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOVING, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_SIZE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_SIZE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_SIZING:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_SIZING, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}break;
		}
	}
	if (wParam == 304 && lParam == 17817868) {
		INT ii = 333;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

WPARAM MsgLoop() {
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			g_program->Update();
		}
	}
	return msg.wParam;
}

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

BOOL FAR PASCAL callbackFunc(DIDEVICEINSTANCEW const *deviceInstance, VOID *v) {
	static int i = 0;
	printf("----------------------------------------\n");

	int ii = i++;
	printf("%d--->dwSize:		%ld\n", ii, deviceInstance->dwSize);
	printf("%d--->dwDevType:		%ld\n", ii, deviceInstance->dwDevType);
	char *buf1 = WC2C(deviceInstance->tszInstanceName);
	char *buf2 = WC2C(deviceInstance->tszProductName);
	printf("%d--->dwDevType:		%s\n", ii, buf1);
	printf("%d--->dwDevType:		%s\n", ii, buf2);

	printf("----------------------------------------\n");

#if 1
	return DIENUM_CONTINUE; //
#else
	return DIENUM_STOP;
#endif
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, INT showType) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	HWND hWnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);

	HRESULT hr;
	IDirectInput8 *directInput;
	hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)(&directInput),
		NULL
	);

	GUID guid;
	hr = directInput->EnumDevices(
		DI8DEVCLASS_ALL,
		callbackFunc,
		(VOID*)(&guid),
		DIEDFL_ALLDEVICES
	);
	/*
	hr = directInput->CreateDevice(

	);
	*/

#if 0
	g_program = new HProgram();

	g_program->Create(hInstance, showType);

	WPARAM wParam = MsgLoop();

	g_program->Release();

	delete g_program;

	return wParam;
#else
	while (true);
	return 0;
#endif
}