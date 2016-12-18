#include <Windows.h>
#include "Common/CommonCode.h"
#include "program.h"

HProgram *g_program;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_program) {
		switch (msg) {
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

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, INT showType) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	HWND hWnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);

	g_program = new HProgram();

	g_program->Create(hInstance, showType);

	WPARAM wParam = MsgLoop();

	g_program->Release();

	delete g_program;

	return wParam;
}